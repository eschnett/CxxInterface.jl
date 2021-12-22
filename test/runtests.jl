using Test

################################################################################
# Define wrapped functions
module AddIntegers
using CxxInterface

const libAddIntegers = joinpath(pwd(), "libAddIntegers")

eval(cxxprelude("""
    #include <cmath>
    """))

eval(cxxfunction(FnName(:add_int, "add_int", libAddIntegers), FnResult(Cint, "int", Int, expr -> :(convert(Int, $expr))),
                 [FnArg(:x, Cint, "x", "int", Integer, identity), FnArg(:y, Cint, "y", "int", Integer, identity)], "return x + y;"))
end

################################################################################
# Extract C++ code
using CxxInterface
using .AddIntegers
code = AddIntegers.cxx_code()
@test code isa AbstractString
open("AddIntegers.cxx", "w") do file
    println(file, code)
    return nothing
end

################################################################################
# Compile C++ code
# (This fails if there is no C++ compiler available)
run(`c++ -fPIC -c AddIntegers.cxx`)
dlext = Sys.isapple() ? "dylib" : "so"
run(`c++ -shared -o libAddIntegers.$dlext AddIntegers.o`)
run(`pwd`)
run(`ls -l`)

# DO NOT call a C++ compiler manually in your own Julia packages. This
# works only in very controlled environments such as on CI
# infrastructure. If you do, your package will be fragile, and will
# create lots of headaches for your users in the wild. Instead, use
# [BinaryBuilder](https://binarybuilder.org) and store your build
# recipes on [Yggdrasil](https://github.com/JuliaPackaging/Yggdrasil).

################################################################################
# Call the wrapped function
# (This fails if the C++ compiler is not compatible with the currently
# running Julia executable)

# Only test cases where the Github CI environment supports this
if Sys.ARCH ≡ :x86_64
    @test AddIntegers.add_int(2, 3) == 5
end
