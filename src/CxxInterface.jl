module CxxInterface

################################################################################

iobuffer = nothing

function begin_generate_cxx()
    global iobuffer
    @assert iobuffer ≡ nothing
    iobuffer = IOBuffer()
    return nothing
end
function end_generate_cxx()
    global iobuffer
    @assert iobuffer ≢ nothing
    str = String(take!(iobuffer))
    iobuffer = nothing
    return str
end

clean_code(expr) = expr
function clean_code(expr::Expr)
    expr = Expr(expr.head, map(clean_code, filter(arg -> !(arg isa LineNumberNode), expr.args))...)
    if expr.head ≡ :block && length(expr.args) == 1
        expr = expr.args[1]::Expr
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

const cxxtype = Dict{Type,CxxType}(Int8 => "int8_t", Int16 => "int16_t", Int32 => "int32_t", Int64 => "int64_t", UInt8 => "uint8_t",
                                   UInt16 => "uint16_t", UInt32 => "uint32_t", UInt64 => "uint64_t", Float32 => "float",
                                   Float64 => "double", Complex{Float32} => "std::complex<float>",
                                   Complex{Float64} => "std::complex<double>")
export cxxtype

################################################################################

function cxxprelude(cxx_stmts::AbstractString)
    global iobuffer
    if iobuffer ≢ nothing
        cxx_code = """
            $cxx_stmts
            """
        quote
            println($iobuffer, $cxx_code)
        end
    else
        quote end
    end
end
export cxxprelude

struct FnName
    julia_name::JuliaName
    cxx_name::CxxName
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
end
export FnArg
function FnArg(julia_name::JuliaName, julia_type::Type, cxx_name::CxxName, cxx_type::CxxType)
    return FnArg(julia_name, julia_type, cxx_name, cxx_type, julia_type, identity)
end

function cxxfunction(name::FnName, result::FnResult, arguments::AbstractVector{FnArg}, cxx_stmts::AbstractString)
    julia_code = quote
        function $(name.julia_name)($([:($(arg.julia_name)::$(arg.initial_julia_type)) for arg in arguments]...))
            res = ccall($(name.cxx_name), $(result.julia_type), ($([arg.julia_type for arg in arguments]...),),
                        $([arg.convert_from_initial(arg.julia_name) for arg in arguments]...))
            return $(result.convert_to_final(:res))::$(result.final_julia_type)
        end
    end
    julia_code = clean_code(julia_code)

    global iobuffer
    if iobuffer ≢ nothing
        cxx_code = """

            /*
            $(string(julia_code))
            */
            extern "C" $(result.cxx_type) $(name.cxx_name)(
                $(join(["$(arg.cxx_type) $(arg.cxx_name)" for arg in arguments], ",\n    "))
            ) {
                $cxx_stmts
            }
            """
        quote
            println($iobuffer, $cxx_code)
        end
    else
        julia_code
    end
end
export cxxfunction

end
