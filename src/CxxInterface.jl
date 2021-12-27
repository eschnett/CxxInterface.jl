module CxxInterface

using Libdl

################################################################################

if VERSION < v"1.1"
    # Taken from Julia Base, version 1.7

    if Sys.isunix()
        const path_dir_splitter = r"^(.*?)(/+)([^/]*)$"

        splitdrive(path::String) = ("", path)
    elseif Sys.iswindows()
        const path_dir_splitter = r"^(.*?)([/\\]+)([^/\\]*)$"

        function splitdrive(path::String)
            m = match(r"^([^\\]+:|\\\\[^\\]+\\[^\\]+|\\\\\?\\UNC\\[^\\]+\\[^\\]+|\\\\\?\\[^\\]+:|)(.*)$"s, path)
            return String(m.captures[1]), String(m.captures[2])
        end
    else
        error("path primitives for this OS need to be defined")
    end

    splitpath(p::AbstractString) = splitpath(String(p))
    function splitpath(p::String)
        drive, p = splitdrive(p)
        out = String[]
        isempty(p) && (pushfirst!(out, p))  # "" means the current directory.
        while !isempty(p)
            dir, base = _splitdir_nodrive(p)
            dir == p && (pushfirst!(out, dir); break)  # Reached root node.
            if !isempty(base)  # Skip trailing '/' in basename
                pushfirst!(out, base)
            end
            p = dir
        end
        if !isempty(drive)  # Tack the drive back on to the first element.
            out[1] = drive * out[1]  # Note that length(out) is always >= 1.
        end
        return out
    end

    _splitdir_nodrive(path::String) = _splitdir_nodrive("", path)
    function _splitdir_nodrive(a::String, b::String)
        m = match(path_dir_splitter, b)
        m === nothing && return (a, b)
        cs = m.captures
        getcapture(cs, i) = cs[i]::AbstractString
        c1, c2, c3 = getcapture(cs, 1), getcapture(cs, 2), getcapture(cs, 3)
        a = string(a, isempty(c1) ? c2[1] : c1)
        return a, String(c3)
    end
end

################################################################################

clean_code(expr) = expr
function clean_code(expr::Expr)
    expr = Expr(expr.head, map(clean_code, filter(arg -> !(arg isa LineNumberNode), expr.args))...)
    # Remove line numbers.
    # Line numbers are usually wrong because they point to this file,
    # instead of the file where the code originates.
    if expr.head ≡ :block && length(expr.args) == 1
        expr = expr.args[1]
    end
    return expr
end

simplify_code(expr) = expr
function simplify_code(expr::Expr)
    expr = Expr(expr.head, map(simplify_code, expr.args)...)
    # Remove the path from the library name in `ccall` expressions.
    # This makes the Julia code look nicer, and it avoids spurious
    # changes when generating the code multiple times, but it won't
    # run correctly any more.
    if expr.head ≡ :call && length(expr.args) ≥ 2 && expr.args[1] ≡ :ccall
        arg1 = expr.args[2]
        if arg1 isa Expr && arg1.head ≡ :tuple && length(arg1.args) ≥ 2
            arg2 = arg1.args[2]
            if arg2 isa String
                arg1.args[2] = splitpath(arg2)[end]
            end
        end
    end
    return expr
end

################################################################################

"Julia identifier"
const JuliaName = Union{Expr,Symbol}
export JuliaName

"C++ identifier"
const CxxName = AbstractString
export CxxName

"C++ type"
const CxxType = AbstractString
export CxxType

function cxxname(str::AbstractString)
    return String([cxxname(ch) for ch in str])
end
function cxxname(ch::Char)
    if Base.Unicode.isletter(ch) || Base.Unicode.isdigit(ch) || ch == '_'
        return ch
    else
        return '_'
    end
end
export cxxname

# Julia's complex numbers need to be mapped to C complex numbers, not
# C++ complex numbers, because C and C++ behave differently under
# certain circumstances (e.g. when returned from a function on a
# 32-bit Intel system).
const cxxtype = Dict{Type,CxxType}(Bool => "uint8_t", Int8 => "int8_t", Int16 => "int16_t", Int32 => "int32_t", Int64 => "int64_t",
                                   UInt8 => "uint8_t", UInt16 => "uint16_t", UInt32 => "uint32_t", UInt64 => "uint64_t",
                                   Float32 => "float", Float64 => "double", Complex{Float32} => "float _Complex",
                                   Complex{Float64} => "double _Complex", Ptr{Cvoid} => "void *")
export cxxtype

################################################################################

struct FnName
    julia_name::JuliaName
    cxx_name::CxxName
    cxx_library::Union{CxxName,Ptr}
end
export FnName

struct FnResult
    julia_type::Type
    cxx_type::CxxType
    final_julia_type::Type
    convert_to_final::Any
end
export FnResult
FnResult(julia_type::Type, cxx_type::CxxType) = FnResult(julia_type, cxx_type, julia_type, identity)

struct FnArg
    julia_name::JuliaName
    julia_type::Type
    cxx_name::CxxName
    cxx_type::CxxType
    initial_julia_type::Type
    convert_from_initial::Any
    skip::Bool
    function FnArg(julia_name::JuliaName, julia_type::Type, cxx_name::CxxName, cxx_type::CxxType, initial_julia_type::Type,
                   convert_from_initial::Any; skip::Bool=false)
        return new(julia_name, julia_type, cxx_name, cxx_type, initial_julia_type, convert_from_initial, skip)
    end
end
export FnArg
function FnArg(julia_name::JuliaName, julia_type::Type, cxx_name::CxxName, cxx_type::CxxType; skip::Bool=false)
    return FnArg(julia_name, julia_type, cxx_name, cxx_type, julia_type, identity; skip=skip)
end

const VarName = FnName
export VarName
const VarType = FnResult
export VarType

################################################################################

include("interface-c.jl")
include("interface-cxx.jl")
include("interface-f90.jl")
include("interface-haskell.jl")
include("interface-rust.jl")

end
