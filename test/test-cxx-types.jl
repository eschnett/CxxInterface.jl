module TestCxxType
using Test
using CxxInterface


@testset "cxxtype" begin
    ctypesymbols = [
        :Cstring,
        :Cuchar,
        :Cuint,
        :Cchar,
        :Cdouble,                   
        :Cfloat,                  
        :Cvoid,
        :Cwchar_t,
        :Cint,                  
        :Cptrdiff_t,
        :Clong,
        :Clonglong,
        :Cssize_t,
        :Culong,
        :Csize_t,    
        :Cshort,    
        :Cwstring,
        :Culonglong,
        :Cushort,
       ]
    ctypes = Dict(sym => eval(sym) for sym in ctypesymbols)
    for T in values(ctypes)
        @test haskey(cxxtype, T)
    end

    libRoundTrip = joinpath(pwd(), "libRoundTrip")
    
    eval(cxxsetup())
    eval(cxxnewfile("RoundTrip.cxx", ""))
    
    make_arg(T::Type)    = FnArg(:x, T, "x", cxxtype[T], T, identity)
    make_body(T::Type)   = "return x;"
    # void is not a valid argument type
    make_arg(T::Type{Cvoid}) = FnArg(:x, Cint, "x", "int", Cvoid, _->1)
    make_body(::Type{Cvoid}) = "return;"
    for (sym,T) in pairs(ctypes)
        ex = cxxfunction(
                FnName(:roundtrip, "roundtrip_$sym", libRoundTrip), 
                FnResult(T, cxxtype[T], T, identity),
                [make_arg(T)],
                make_body(T),
            )
        eval(ex)
    end

    cxx_write_code!()
    using Libdl: dlext
    run(`c++ -fPIC -shared -o libRoundTrip.$dlext RoundTrip.cxx`)

    example(T) = one(T)
    example(::Type{Cvoid}) = Cvoid()
    example(T::Type{Cstring})  = Base.cconvert(Cstring, C_NULL)
    example(T::Type{Cwstring}) = Base.cconvert(Cwstring, C_NULL)
    if Sys.ARCH ≡ :x86_64
        for T in values(ctypes)
            x = example(T)::T
            @test roundtrip(x) === x
        end
    end
end


end#module
