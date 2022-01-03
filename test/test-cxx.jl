################################################################################
# Define wrapped functions
module AddIntegersCxx
using CxxInterface

const libAddIntegersCxx = joinpath(pwd(), "libAddIntegersCxx")

eval(cxxsetup())
eval(cxxnewfile("AddIntegersCxx.cxx", ""))

eval(cxxfunction(FnName(:add_int, "add_int", libAddIntegersCxx), FnResult(Cint, "int", Int, expr -> :(convert(Int, $expr))),
                 [FnArg(:x, Cint, "x", "int", Integer, identity), FnArg(:y, Cint, "y", "int", Integer, identity)], "return x + y;"))
end

################################################################################
# Extract C++ code
using CxxInterface
using .AddIntegersCxx
AddIntegersCxx.cxx_write_code!()

################################################################################
# Compile C++ code
# (This fails if there is no C++ compiler available)
using Libdl: dlext
run(`c++ -fPIC -c AddIntegersCxx.cxx`)
run(`c++ -shared -o libAddIntegersCxx.$dlext AddIntegersCxx.o`)

# Please, DO NOT call a C++ compiler manually in your own Julia
# packages. This works only in very controlled environments such as on
# CI infrastructure. If you do, your package will be fragile, and will
# create lots of headaches for your users in the wild. Instead, use
# [BinaryBuilder](https://binarybuilder.org) and store your build
# recipes on [Yggdrasil](https://github.com/JuliaPackaging/Yggdrasil).

################################################################################
# Call the wrapped function
# (This fails if the C++ compiler is not compatible with the currently
# running Julia executable)

# Only test cases where the Github CI environment supports this (:i686 is not supported)
if Sys.ARCH ≡ :x86_64
    @test AddIntegersCxx.add_int(2, 3) == 5
end

@testset "cxxtype" begin
    for T in [
        Cstring,
        Cuchar,
        Cuint,
        Cchar,
        Cdouble,                   
        Cfloat,                  
        Cvoid,
        Cwchar_t,
        Cint,                  
        Cptrdiff_t,
        Clong,
        Clonglong,
        Cssize_t,
        Culong,
        Csize_t,    
        Cshort,    
        Cwstring,
        Culonglong,
        Cushort,
       ]
        @test haskey(cxxtype, T)
    end
end

