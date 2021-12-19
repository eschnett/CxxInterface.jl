module StdVectors

using CxxInterface

const types = Type[Cchar, Cshort, Cint, Clong, Clonglong, Cuchar, Cushort, Cuint, Culong, Culonglong, Cfloat, Cdouble,
                   Complex{Cfloat}, Complex{Cdouble}]

################################################################################

eval(cxxprelude("""
    #include <complex>
    #include <cstddef>
    #include <cstdint>
    #include <tuple>
    #include <vector>
    """))

struct StdVector{T} <: AbstractVector{T}
    cxx::Ptr{Cvoid}
    StdVector{T}() where {T} = new{T}(C_NULL)
    StdVector{T}(cxx::Ptr{Cvoid}) where {T} = new{T}(cxx)
end
Base.cconvert(vec::StdVector) = vec.cxx

for T in types
    CT = cxxtype[T]
    NT = cxxname(CT)

    eval(cxxfunction(FnName(Symbol(:StdVector_new), "std_vector_$(NT)_new"),
                     FnResult(Ptr{Cvoid}, "std::vector<$CT> *", StdVector{T}, expr -> :(StdVector{$T}($expr))),
                     [FnArg(:type, Nothing, "type", "std::tuple<>", Type{T}, expr -> nothing)], "return new std::vector<$CT>;"))

    eval(cxxfunction(FnName(:StdVector_delete, "std_vector_$(NT)_delete"), FnResult(Nothing, "void"),
                     [FnArg(:vec, Ptr{Cvoid}, "vec", "std::vector<$CT> * restrict", StdVector{T}, identity)], "delete vec;"))

    eval(cxxfunction(FnName(:(Base.length), "std_vector_$(NT)_length"),
                     FnResult(Csize_t, "std::size_t", Int, expr -> :(convert(Int, $expr))),
                     [FnArg(:vec, Ptr{Cvoid}, "vec", "const std::vector<$CT> * restrict", StdVector{T}, identity)],
                     "return vec->size();"))

    eval(cxxfunction(FnName(:(Base.getindex), "std_vector_$(NT)_getindex"), FnResult(T, CT),
                     [FnArg(:vec, Ptr{Cvoid}, "vec", "const std::vector<$CT> * restrict", StdVector{T}, identity),
                      FnArg(:idx, Csize_t, "idx", "std::size_t", Integer, identity)], "return (*vec)[i];"))

    eval(cxxfunction(FnName(:(Base.setindex!), "std_vector_$(NT)_setindex_"), FnResult(Nothing, "void"),
                     [FnArg(:vec, Ptr{Cvoid}, "vec", "std::vector<$CT> * restrict", StdVector{T}, identity),
                      FnArg(:elt, T, "elt", "const $CT&"), FnArg(:idx, Csize_t, "idx", "std::size_t", Integer, identity)],
                     "(*vec)[i] = elt;"))
end

allocate(::StdVector{T}) where {T} = StdVector_new(T)
free(vec::StdVector) = StdVector_delete(vec)

Base.size(vec::StdVector) = (length(vec),)

Base.eltype(::StdVector{T}) where {T} = T

################################################################################

mutable struct GCStdVector{T} <: AbstractVector{T}
    managed::StdVector{T}
    function GCStdVector{T}() where {T}
        res = new{T}(allocate(T))
        finalizer(free, res)
        return res
    end
end
export GCStdVector
Base.cconvert(vec::GCStdVector) = cconvert(vec.managed)

Base.length(vec::GCStdVector) = length(vec.managed)
Base.getindex(vec::GCStdVector, idx) = getindex(vec.managed, idx)
Base.setindex!(vec::GCStdVector, elt, idx) = setindex!(vec.managed, elt, idx)
Base.size(vec::GCStdVector) = size(vec.managed)
Base.eltype(::GCStdVector{T}) where {T} = eltype(StdVector{T})

end
