################################################################################
# Define wrapped functions
module AddIntegersC
using CxxInterface

const libAddIntegersC = joinpath(pwd(), "libAddIntegersC")

eval(csetup())
eval(cnewfile("AddIntegersC.c", ""))

eval(cfunction(FnName(:add_int, "add_int", libAddIntegersC), FnResult(Cint, "int", Int, expr -> :(convert(Int, $expr))),
               [FnArg(:x, Cint, "x", "int", Integer, identity), FnArg(:y, Cint, "y", "int", Integer, identity)], "return x + y;"))
end

################################################################################
# Extract C++ code
using CxxInterface
using .AddIntegersC
AddIntegersC.c_write_code!()

################################################################################
# Compile C++ code
# (This fails if there is no C++ compiler available)
using Libdl: dlext
run(`cc -fPIC -c AddIntegersC.c`)
run(`cc -shared -o libAddIntegersC.$dlext AddIntegersC.o`)

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
    @test AddIntegersC.add_int(2, 3) == 5
end
