using Test

################################################################################
# Define wrapped functions
module AddIntegers
using CxxInterface

eval(cxxprelude("""
    #include <cmath>
    """))

eval(cxxfunction(FnName(:add_int, "add_int", "$(pwd())/libAddIntegers"), FnResult(Cint, "int", Int, expr -> :(convert(Int, $expr))),
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

################################################################################
# Call the wrapped function
# (This fails if the C++ compiler is not compatible with the currently
# running Julia executable)
@test AddIntegers.add_int(2, 3) == 5
