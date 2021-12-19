#include <complex>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <tuple>



/*
function StdSharedPtr_new(type::Type{Int8})
    res = ccall("std_shared_ptr_int8_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{Int8}(res)::Main.StdSharedPtrs.StdSharedPtr{Int8}
end
*/
extern "C" std::shared_ptr<int8_t> * std_shared_ptr_int8_t_new(
    std::tuple<> type
) {
    return new std::shared_ptr<int8_t>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{Int8})
    res = ccall("std_shared_ptr_int8_t_delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_int8_t_delete(
    std::shared_ptr<int8_t> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{Int8})
    res = ccall("std_shared_ptr_int8_t_isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_int8_t_isempty(
    const std::shared_ptr<int8_t> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{Int8})
    res = ccall("std_shared_ptr_int8_t_getindex", Int8, (Ptr{Nothing},), ptr)
    return res::Int8
end
*/
extern "C" int8_t std_shared_ptr_int8_t_getindex(
    const std::shared_ptr<int8_t> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{Int8}, elt::Int8)
    res = ccall("std_shared_ptr_int8_t_setindex_", Nothing, (Ptr{Nothing}, Int8), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_int8_t_setindex_(
    std::shared_ptr<int8_t> * restrict ptr,
    const int8_t& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{Int16})
    res = ccall("std_shared_ptr_int16_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{Int16}(res)::Main.StdSharedPtrs.StdSharedPtr{Int16}
end
*/
extern "C" std::shared_ptr<int16_t> * std_shared_ptr_int16_t_new(
    std::tuple<> type
) {
    return new std::shared_ptr<int16_t>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{Int16})
    res = ccall("std_shared_ptr_int16_t_delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_int16_t_delete(
    std::shared_ptr<int16_t> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{Int16})
    res = ccall("std_shared_ptr_int16_t_isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_int16_t_isempty(
    const std::shared_ptr<int16_t> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{Int16})
    res = ccall("std_shared_ptr_int16_t_getindex", Int16, (Ptr{Nothing},), ptr)
    return res::Int16
end
*/
extern "C" int16_t std_shared_ptr_int16_t_getindex(
    const std::shared_ptr<int16_t> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{Int16}, elt::Int16)
    res = ccall("std_shared_ptr_int16_t_setindex_", Nothing, (Ptr{Nothing}, Int16), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_int16_t_setindex_(
    std::shared_ptr<int16_t> * restrict ptr,
    const int16_t& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{Int64})
    res = ccall("std_shared_ptr_int64_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{Int64}(res)::Main.StdSharedPtrs.StdSharedPtr{Int64}
end
*/
extern "C" std::shared_ptr<int64_t> * std_shared_ptr_int64_t_new(
    std::tuple<> type
) {
    return new std::shared_ptr<int64_t>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{Int64})
    res = ccall("std_shared_ptr_int64_t_delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_int64_t_delete(
    std::shared_ptr<int64_t> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{Int64})
    res = ccall("std_shared_ptr_int64_t_isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_int64_t_isempty(
    const std::shared_ptr<int64_t> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{Int64})
    res = ccall("std_shared_ptr_int64_t_getindex", Int64, (Ptr{Nothing},), ptr)
    return res::Int64
end
*/
extern "C" int64_t std_shared_ptr_int64_t_getindex(
    const std::shared_ptr<int64_t> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{Int64}, elt::Int64)
    res = ccall("std_shared_ptr_int64_t_setindex_", Nothing, (Ptr{Nothing}, Int64), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_int64_t_setindex_(
    std::shared_ptr<int64_t> * restrict ptr,
    const int64_t& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{UInt32})
    res = ccall("std_shared_ptr_uint32_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{UInt32}(res)::Main.StdSharedPtrs.StdSharedPtr{UInt32}
end
*/
extern "C" std::shared_ptr<uint32_t> * std_shared_ptr_uint32_t_new(
    std::tuple<> type
) {
    return new std::shared_ptr<uint32_t>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt32})
    res = ccall("std_shared_ptr_uint32_t_delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_uint32_t_delete(
    std::shared_ptr<uint32_t> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt32})
    res = ccall("std_shared_ptr_uint32_t_isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_uint32_t_isempty(
    const std::shared_ptr<uint32_t> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt32})
    res = ccall("std_shared_ptr_uint32_t_getindex", UInt32, (Ptr{Nothing},), ptr)
    return res::UInt32
end
*/
extern "C" uint32_t std_shared_ptr_uint32_t_getindex(
    const std::shared_ptr<uint32_t> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt32}, elt::UInt32)
    res = ccall("std_shared_ptr_uint32_t_setindex_", Nothing, (Ptr{Nothing}, UInt32), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_uint32_t_setindex_(
    std::shared_ptr<uint32_t> * restrict ptr,
    const uint32_t& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{Float64})
    res = ccall("std_shared_ptr_double_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{Float64}(res)::Main.StdSharedPtrs.StdSharedPtr{Float64}
end
*/
extern "C" std::shared_ptr<double> * std_shared_ptr_double_new(
    std::tuple<> type
) {
    return new std::shared_ptr<double>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{Float64})
    res = ccall("std_shared_ptr_double_delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_double_delete(
    std::shared_ptr<double> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{Float64})
    res = ccall("std_shared_ptr_double_isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_double_isempty(
    const std::shared_ptr<double> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{Float64})
    res = ccall("std_shared_ptr_double_getindex", Float64, (Ptr{Nothing},), ptr)
    return res::Float64
end
*/
extern "C" double std_shared_ptr_double_getindex(
    const std::shared_ptr<double> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{Float64}, elt::Float64)
    res = ccall("std_shared_ptr_double_setindex_", Nothing, (Ptr{Nothing}, Float64), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_double_setindex_(
    std::shared_ptr<double> * restrict ptr,
    const double& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{Int32})
    res = ccall("std_shared_ptr_int32_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{Int32}(res)::Main.StdSharedPtrs.StdSharedPtr{Int32}
end
*/
extern "C" std::shared_ptr<int32_t> * std_shared_ptr_int32_t_new(
    std::tuple<> type
) {
    return new std::shared_ptr<int32_t>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{Int32})
    res = ccall("std_shared_ptr_int32_t_delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_int32_t_delete(
    std::shared_ptr<int32_t> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{Int32})
    res = ccall("std_shared_ptr_int32_t_isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_int32_t_isempty(
    const std::shared_ptr<int32_t> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{Int32})
    res = ccall("std_shared_ptr_int32_t_getindex", Int32, (Ptr{Nothing},), ptr)
    return res::Int32
end
*/
extern "C" int32_t std_shared_ptr_int32_t_getindex(
    const std::shared_ptr<int32_t> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{Int32}, elt::Int32)
    res = ccall("std_shared_ptr_int32_t_setindex_", Nothing, (Ptr{Nothing}, Int32), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_int32_t_setindex_(
    std::shared_ptr<int32_t> * restrict ptr,
    const int32_t& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{ComplexF32})
    res = ccall("std_shared_ptr_std__complex_float__new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{ComplexF32}(res)::Main.StdSharedPtrs.StdSharedPtr{ComplexF32}
end
*/
extern "C" std::shared_ptr<std::complex<float>> * std_shared_ptr_std__complex_float__new(
    std::tuple<> type
) {
    return new std::shared_ptr<std::complex<float>>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{ComplexF32})
    res = ccall("std_shared_ptr_std__complex_float__delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_std__complex_float__delete(
    std::shared_ptr<std::complex<float>> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{ComplexF32})
    res = ccall("std_shared_ptr_std__complex_float__isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_std__complex_float__isempty(
    const std::shared_ptr<std::complex<float>> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{ComplexF32})
    res = ccall("std_shared_ptr_std__complex_float__getindex", ComplexF32, (Ptr{Nothing},), ptr)
    return res::ComplexF32
end
*/
extern "C" std::complex<float> std_shared_ptr_std__complex_float__getindex(
    const std::shared_ptr<std::complex<float>> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{ComplexF32}, elt::ComplexF32)
    res = ccall("std_shared_ptr_std__complex_float__setindex_", Nothing, (Ptr{Nothing}, ComplexF32), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_std__complex_float__setindex_(
    std::shared_ptr<std::complex<float>> * restrict ptr,
    const std::complex<float>& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{UInt64})
    res = ccall("std_shared_ptr_uint64_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{UInt64}(res)::Main.StdSharedPtrs.StdSharedPtr{UInt64}
end
*/
extern "C" std::shared_ptr<uint64_t> * std_shared_ptr_uint64_t_new(
    std::tuple<> type
) {
    return new std::shared_ptr<uint64_t>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt64})
    res = ccall("std_shared_ptr_uint64_t_delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_uint64_t_delete(
    std::shared_ptr<uint64_t> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt64})
    res = ccall("std_shared_ptr_uint64_t_isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_uint64_t_isempty(
    const std::shared_ptr<uint64_t> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt64})
    res = ccall("std_shared_ptr_uint64_t_getindex", UInt64, (Ptr{Nothing},), ptr)
    return res::UInt64
end
*/
extern "C" uint64_t std_shared_ptr_uint64_t_getindex(
    const std::shared_ptr<uint64_t> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt64}, elt::UInt64)
    res = ccall("std_shared_ptr_uint64_t_setindex_", Nothing, (Ptr{Nothing}, UInt64), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_uint64_t_setindex_(
    std::shared_ptr<uint64_t> * restrict ptr,
    const uint64_t& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{Float32})
    res = ccall("std_shared_ptr_float_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{Float32}(res)::Main.StdSharedPtrs.StdSharedPtr{Float32}
end
*/
extern "C" std::shared_ptr<float> * std_shared_ptr_float_new(
    std::tuple<> type
) {
    return new std::shared_ptr<float>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{Float32})
    res = ccall("std_shared_ptr_float_delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_float_delete(
    std::shared_ptr<float> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{Float32})
    res = ccall("std_shared_ptr_float_isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_float_isempty(
    const std::shared_ptr<float> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{Float32})
    res = ccall("std_shared_ptr_float_getindex", Float32, (Ptr{Nothing},), ptr)
    return res::Float32
end
*/
extern "C" float std_shared_ptr_float_getindex(
    const std::shared_ptr<float> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{Float32}, elt::Float32)
    res = ccall("std_shared_ptr_float_setindex_", Nothing, (Ptr{Nothing}, Float32), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_float_setindex_(
    std::shared_ptr<float> * restrict ptr,
    const float& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{ComplexF64})
    res = ccall("std_shared_ptr_std__complex_double__new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{ComplexF64}(res)::Main.StdSharedPtrs.StdSharedPtr{ComplexF64}
end
*/
extern "C" std::shared_ptr<std::complex<double>> * std_shared_ptr_std__complex_double__new(
    std::tuple<> type
) {
    return new std::shared_ptr<std::complex<double>>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{ComplexF64})
    res = ccall("std_shared_ptr_std__complex_double__delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_std__complex_double__delete(
    std::shared_ptr<std::complex<double>> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{ComplexF64})
    res = ccall("std_shared_ptr_std__complex_double__isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_std__complex_double__isempty(
    const std::shared_ptr<std::complex<double>> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{ComplexF64})
    res = ccall("std_shared_ptr_std__complex_double__getindex", ComplexF64, (Ptr{Nothing},), ptr)
    return res::ComplexF64
end
*/
extern "C" std::complex<double> std_shared_ptr_std__complex_double__getindex(
    const std::shared_ptr<std::complex<double>> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{ComplexF64}, elt::ComplexF64)
    res = ccall("std_shared_ptr_std__complex_double__setindex_", Nothing, (Ptr{Nothing}, ComplexF64), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_std__complex_double__setindex_(
    std::shared_ptr<std::complex<double>> * restrict ptr,
    const std::complex<double>& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{UInt8})
    res = ccall("std_shared_ptr_uint8_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{UInt8}(res)::Main.StdSharedPtrs.StdSharedPtr{UInt8}
end
*/
extern "C" std::shared_ptr<uint8_t> * std_shared_ptr_uint8_t_new(
    std::tuple<> type
) {
    return new std::shared_ptr<uint8_t>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt8})
    res = ccall("std_shared_ptr_uint8_t_delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_uint8_t_delete(
    std::shared_ptr<uint8_t> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt8})
    res = ccall("std_shared_ptr_uint8_t_isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_uint8_t_isempty(
    const std::shared_ptr<uint8_t> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt8})
    res = ccall("std_shared_ptr_uint8_t_getindex", UInt8, (Ptr{Nothing},), ptr)
    return res::UInt8
end
*/
extern "C" uint8_t std_shared_ptr_uint8_t_getindex(
    const std::shared_ptr<uint8_t> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt8}, elt::UInt8)
    res = ccall("std_shared_ptr_uint8_t_setindex_", Nothing, (Ptr{Nothing}, UInt8), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_uint8_t_setindex_(
    std::shared_ptr<uint8_t> * restrict ptr,
    const uint8_t& elt
) {
    **ptr = elt;
}


/*
function StdSharedPtr_new(type::Type{UInt16})
    res = ccall("std_shared_ptr_uint16_t_new", Ptr{Nothing}, (Nothing,), nothing)
    return StdSharedPtr{UInt16}(res)::Main.StdSharedPtrs.StdSharedPtr{UInt16}
end
*/
extern "C" std::shared_ptr<uint16_t> * std_shared_ptr_uint16_t_new(
    std::tuple<> type
) {
    return new std::shared_ptr<uint16_t>;
}


/*
function StdSharedPtr_delete(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt16})
    res = ccall("std_shared_ptr_uint16_t_delete", Nothing, (Ptr{Nothing},), ptr)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_uint16_t_delete(
    std::shared_ptr<uint16_t> * restrict ptr
) {
    delete ptr;
}


/*
function Base.isempty(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt16})
    res = ccall("std_shared_ptr_uint16_t_isempty", Int32, (Ptr{Nothing},), ptr)
    return convert(Bool, res)::Bool
end
*/
extern "C" int std_shared_ptr_uint16_t_isempty(
    const std::shared_ptr<uint16_t> * restrict ptr
) {
    return bool(*ptr);
}


/*
function Base.getindex(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt16})
    res = ccall("std_shared_ptr_uint16_t_getindex", UInt16, (Ptr{Nothing},), ptr)
    return res::UInt16
end
*/
extern "C" uint16_t std_shared_ptr_uint16_t_getindex(
    const std::shared_ptr<uint16_t> * restrict ptr
) {
    return **ptr;
}


/*
function Base.setindex!(ptr::Main.StdSharedPtrs.StdSharedPtr{UInt16}, elt::UInt16)
    res = ccall("std_shared_ptr_uint16_t_setindex_", Nothing, (Ptr{Nothing}, UInt16), ptr, elt)
    return res::Nothing
end
*/
extern "C" void std_shared_ptr_uint16_t_setindex_(
    std::shared_ptr<uint16_t> * restrict ptr,
    const uint16_t& elt
) {
    **ptr = elt;
}


