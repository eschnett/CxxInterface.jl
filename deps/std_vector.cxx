#include <complex>
#include <cstddef>
#include <cstdint>
#include <tuple>
#include <vector>



/*
function StdVector_new(type::Type{Int8})
    res = ccall("std_vector_int8_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{Int8}(res)::Main.StdVectors.StdVector{Int8}
end
*/
extern "C" std::vector<int8_t> * std_vector_int8_t_new(
    std::tuple<> type
) {
    return new std::vector<int8_t>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{Int8})
    res = ccall("std_vector_int8_t_delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_int8_t_delete(
    std::vector<int8_t> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{Int8})
    res = ccall("std_vector_int8_t_length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_int8_t_length(
    const std::vector<int8_t> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{Int8}, idx::Integer)
    res = ccall("std_vector_int8_t_getindex", Int8, (Ptr{Nothing}, UInt64), vec, idx)
    return res::Int8
end
*/
extern "C" int8_t std_vector_int8_t_getindex(
    const std::vector<int8_t> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{Int8}, elt::Int8, idx::Integer)
    res = ccall("std_vector_int8_t_setindex_", Nothing, (Ptr{Nothing}, Int8, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_int8_t_setindex_(
    std::vector<int8_t> * restrict vec,
    const int8_t& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{Int16})
    res = ccall("std_vector_int16_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{Int16}(res)::Main.StdVectors.StdVector{Int16}
end
*/
extern "C" std::vector<int16_t> * std_vector_int16_t_new(
    std::tuple<> type
) {
    return new std::vector<int16_t>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{Int16})
    res = ccall("std_vector_int16_t_delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_int16_t_delete(
    std::vector<int16_t> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{Int16})
    res = ccall("std_vector_int16_t_length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_int16_t_length(
    const std::vector<int16_t> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{Int16}, idx::Integer)
    res = ccall("std_vector_int16_t_getindex", Int16, (Ptr{Nothing}, UInt64), vec, idx)
    return res::Int16
end
*/
extern "C" int16_t std_vector_int16_t_getindex(
    const std::vector<int16_t> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{Int16}, elt::Int16, idx::Integer)
    res = ccall("std_vector_int16_t_setindex_", Nothing, (Ptr{Nothing}, Int16, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_int16_t_setindex_(
    std::vector<int16_t> * restrict vec,
    const int16_t& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{Int64})
    res = ccall("std_vector_int64_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{Int64}(res)::Main.StdVectors.StdVector{Int64}
end
*/
extern "C" std::vector<int64_t> * std_vector_int64_t_new(
    std::tuple<> type
) {
    return new std::vector<int64_t>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{Int64})
    res = ccall("std_vector_int64_t_delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_int64_t_delete(
    std::vector<int64_t> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{Int64})
    res = ccall("std_vector_int64_t_length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_int64_t_length(
    const std::vector<int64_t> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{Int64}, idx::Integer)
    res = ccall("std_vector_int64_t_getindex", Int64, (Ptr{Nothing}, UInt64), vec, idx)
    return res::Int64
end
*/
extern "C" int64_t std_vector_int64_t_getindex(
    const std::vector<int64_t> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{Int64}, elt::Int64, idx::Integer)
    res = ccall("std_vector_int64_t_setindex_", Nothing, (Ptr{Nothing}, Int64, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_int64_t_setindex_(
    std::vector<int64_t> * restrict vec,
    const int64_t& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{UInt32})
    res = ccall("std_vector_uint32_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{UInt32}(res)::Main.StdVectors.StdVector{UInt32}
end
*/
extern "C" std::vector<uint32_t> * std_vector_uint32_t_new(
    std::tuple<> type
) {
    return new std::vector<uint32_t>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{UInt32})
    res = ccall("std_vector_uint32_t_delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_uint32_t_delete(
    std::vector<uint32_t> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{UInt32})
    res = ccall("std_vector_uint32_t_length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_uint32_t_length(
    const std::vector<uint32_t> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{UInt32}, idx::Integer)
    res = ccall("std_vector_uint32_t_getindex", UInt32, (Ptr{Nothing}, UInt64), vec, idx)
    return res::UInt32
end
*/
extern "C" uint32_t std_vector_uint32_t_getindex(
    const std::vector<uint32_t> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{UInt32}, elt::UInt32, idx::Integer)
    res = ccall("std_vector_uint32_t_setindex_", Nothing, (Ptr{Nothing}, UInt32, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_uint32_t_setindex_(
    std::vector<uint32_t> * restrict vec,
    const uint32_t& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{Float64})
    res = ccall("std_vector_double_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{Float64}(res)::Main.StdVectors.StdVector{Float64}
end
*/
extern "C" std::vector<double> * std_vector_double_new(
    std::tuple<> type
) {
    return new std::vector<double>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{Float64})
    res = ccall("std_vector_double_delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_double_delete(
    std::vector<double> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{Float64})
    res = ccall("std_vector_double_length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_double_length(
    const std::vector<double> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{Float64}, idx::Integer)
    res = ccall("std_vector_double_getindex", Float64, (Ptr{Nothing}, UInt64), vec, idx)
    return res::Float64
end
*/
extern "C" double std_vector_double_getindex(
    const std::vector<double> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{Float64}, elt::Float64, idx::Integer)
    res = ccall("std_vector_double_setindex_", Nothing, (Ptr{Nothing}, Float64, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_double_setindex_(
    std::vector<double> * restrict vec,
    const double& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{Int32})
    res = ccall("std_vector_int32_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{Int32}(res)::Main.StdVectors.StdVector{Int32}
end
*/
extern "C" std::vector<int32_t> * std_vector_int32_t_new(
    std::tuple<> type
) {
    return new std::vector<int32_t>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{Int32})
    res = ccall("std_vector_int32_t_delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_int32_t_delete(
    std::vector<int32_t> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{Int32})
    res = ccall("std_vector_int32_t_length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_int32_t_length(
    const std::vector<int32_t> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{Int32}, idx::Integer)
    res = ccall("std_vector_int32_t_getindex", Int32, (Ptr{Nothing}, UInt64), vec, idx)
    return res::Int32
end
*/
extern "C" int32_t std_vector_int32_t_getindex(
    const std::vector<int32_t> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{Int32}, elt::Int32, idx::Integer)
    res = ccall("std_vector_int32_t_setindex_", Nothing, (Ptr{Nothing}, Int32, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_int32_t_setindex_(
    std::vector<int32_t> * restrict vec,
    const int32_t& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{ComplexF32})
    res = ccall("std_vector_std__complex_float__new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{ComplexF32}(res)::Main.StdVectors.StdVector{ComplexF32}
end
*/
extern "C" std::vector<std::complex<float>> * std_vector_std__complex_float__new(
    std::tuple<> type
) {
    return new std::vector<std::complex<float>>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{ComplexF32})
    res = ccall("std_vector_std__complex_float__delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_std__complex_float__delete(
    std::vector<std::complex<float>> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{ComplexF32})
    res = ccall("std_vector_std__complex_float__length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_std__complex_float__length(
    const std::vector<std::complex<float>> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{ComplexF32}, idx::Integer)
    res = ccall("std_vector_std__complex_float__getindex", ComplexF32, (Ptr{Nothing}, UInt64), vec, idx)
    return res::ComplexF32
end
*/
extern "C" std::complex<float> std_vector_std__complex_float__getindex(
    const std::vector<std::complex<float>> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{ComplexF32}, elt::ComplexF32, idx::Integer)
    res = ccall("std_vector_std__complex_float__setindex_", Nothing, (Ptr{Nothing}, ComplexF32, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_std__complex_float__setindex_(
    std::vector<std::complex<float>> * restrict vec,
    const std::complex<float>& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{UInt64})
    res = ccall("std_vector_uint64_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{UInt64}(res)::Main.StdVectors.StdVector{UInt64}
end
*/
extern "C" std::vector<uint64_t> * std_vector_uint64_t_new(
    std::tuple<> type
) {
    return new std::vector<uint64_t>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{UInt64})
    res = ccall("std_vector_uint64_t_delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_uint64_t_delete(
    std::vector<uint64_t> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{UInt64})
    res = ccall("std_vector_uint64_t_length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_uint64_t_length(
    const std::vector<uint64_t> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{UInt64}, idx::Integer)
    res = ccall("std_vector_uint64_t_getindex", UInt64, (Ptr{Nothing}, UInt64), vec, idx)
    return res::UInt64
end
*/
extern "C" uint64_t std_vector_uint64_t_getindex(
    const std::vector<uint64_t> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{UInt64}, elt::UInt64, idx::Integer)
    res = ccall("std_vector_uint64_t_setindex_", Nothing, (Ptr{Nothing}, UInt64, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_uint64_t_setindex_(
    std::vector<uint64_t> * restrict vec,
    const uint64_t& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{Float32})
    res = ccall("std_vector_float_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{Float32}(res)::Main.StdVectors.StdVector{Float32}
end
*/
extern "C" std::vector<float> * std_vector_float_new(
    std::tuple<> type
) {
    return new std::vector<float>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{Float32})
    res = ccall("std_vector_float_delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_float_delete(
    std::vector<float> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{Float32})
    res = ccall("std_vector_float_length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_float_length(
    const std::vector<float> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{Float32}, idx::Integer)
    res = ccall("std_vector_float_getindex", Float32, (Ptr{Nothing}, UInt64), vec, idx)
    return res::Float32
end
*/
extern "C" float std_vector_float_getindex(
    const std::vector<float> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{Float32}, elt::Float32, idx::Integer)
    res = ccall("std_vector_float_setindex_", Nothing, (Ptr{Nothing}, Float32, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_float_setindex_(
    std::vector<float> * restrict vec,
    const float& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{ComplexF64})
    res = ccall("std_vector_std__complex_double__new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{ComplexF64}(res)::Main.StdVectors.StdVector{ComplexF64}
end
*/
extern "C" std::vector<std::complex<double>> * std_vector_std__complex_double__new(
    std::tuple<> type
) {
    return new std::vector<std::complex<double>>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{ComplexF64})
    res = ccall("std_vector_std__complex_double__delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_std__complex_double__delete(
    std::vector<std::complex<double>> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{ComplexF64})
    res = ccall("std_vector_std__complex_double__length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_std__complex_double__length(
    const std::vector<std::complex<double>> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{ComplexF64}, idx::Integer)
    res = ccall("std_vector_std__complex_double__getindex", ComplexF64, (Ptr{Nothing}, UInt64), vec, idx)
    return res::ComplexF64
end
*/
extern "C" std::complex<double> std_vector_std__complex_double__getindex(
    const std::vector<std::complex<double>> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{ComplexF64}, elt::ComplexF64, idx::Integer)
    res = ccall("std_vector_std__complex_double__setindex_", Nothing, (Ptr{Nothing}, ComplexF64, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_std__complex_double__setindex_(
    std::vector<std::complex<double>> * restrict vec,
    const std::complex<double>& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{UInt8})
    res = ccall("std_vector_uint8_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{UInt8}(res)::Main.StdVectors.StdVector{UInt8}
end
*/
extern "C" std::vector<uint8_t> * std_vector_uint8_t_new(
    std::tuple<> type
) {
    return new std::vector<uint8_t>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{UInt8})
    res = ccall("std_vector_uint8_t_delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_uint8_t_delete(
    std::vector<uint8_t> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{UInt8})
    res = ccall("std_vector_uint8_t_length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_uint8_t_length(
    const std::vector<uint8_t> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{UInt8}, idx::Integer)
    res = ccall("std_vector_uint8_t_getindex", UInt8, (Ptr{Nothing}, UInt64), vec, idx)
    return res::UInt8
end
*/
extern "C" uint8_t std_vector_uint8_t_getindex(
    const std::vector<uint8_t> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{UInt8}, elt::UInt8, idx::Integer)
    res = ccall("std_vector_uint8_t_setindex_", Nothing, (Ptr{Nothing}, UInt8, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_uint8_t_setindex_(
    std::vector<uint8_t> * restrict vec,
    const uint8_t& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


/*
function StdVector_new(type::Type{UInt16})
    res = ccall("std_vector_uint16_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdVector{UInt16}(res)::Main.StdVectors.StdVector{UInt16}
end
*/
extern "C" std::vector<uint16_t> * std_vector_uint16_t_new(
    std::tuple<> type
) {
    return new std::vector<uint16_t>;
}


/*
function StdVector_delete(vec::Main.StdVectors.StdVector{UInt16})
    res = ccall("std_vector_uint16_t_delete", Nothing, (Ptr{Nothing},), vec)
    return res::Nothing
end
*/
extern "C" void std_vector_uint16_t_delete(
    std::vector<uint16_t> * restrict vec
) {
    delete vec;
}


/*
function Base.length(vec::Main.StdVectors.StdVector{UInt16})
    res = ccall("std_vector_uint16_t_length", UInt64, (Ptr{Nothing},), vec)
    return convert(Int, res)::Int64
end
*/
extern "C" std::size_t std_vector_uint16_t_length(
    const std::vector<uint16_t> * restrict vec
) {
    return vec->size();
}


/*
function Base.getindex(vec::Main.StdVectors.StdVector{UInt16}, idx::Integer)
    res = ccall("std_vector_uint16_t_getindex", UInt16, (Ptr{Nothing}, UInt64), vec, idx)
    return res::UInt16
end
*/
extern "C" uint16_t std_vector_uint16_t_getindex(
    const std::vector<uint16_t> * restrict vec,
    std::size_t idx
) {
    return (*vec)[i];
}


/*
function Base.setindex!(vec::Main.StdVectors.StdVector{UInt16}, elt::UInt16, idx::Integer)
    res = ccall("std_vector_uint16_t_setindex_", Nothing, (Ptr{Nothing}, UInt16, UInt64), vec, elt, idx)
    return res::Nothing
end
*/
extern "C" void std_vector_uint16_t_setindex_(
    std::vector<uint16_t> * restrict vec,
    const uint16_t& elt,
    std::size_t idx
) {
    (*vec)[i] = elt;
}


