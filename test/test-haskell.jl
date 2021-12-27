################################################################################
# Define wrapped functions
module AddIntegersHaskell
using CxxInterface

const libAddIntegersHaskell = joinpath(pwd(), "libAddIntegersHaskell")

eval(haskellsetup())
eval(haskellnewfile("AddIntegersHaskell.hs", ""))

eval(haskellfunction(FnName(:add_int, "addInt", libAddIntegersHaskell), FnResult(Cint, "CInt", Int, expr -> :(convert(Int, $expr))),
                     [FnArg(:x, Cint, "x", "CInt", Integer, identity), FnArg(:y, Cint, "y", "CInt", Integer, identity)], "x + y"))

# The Haskell run-time systems needs to be initialized. This requires
# calling a C function.
eval(csetup())
eval(cnewfile("HaskellRTS.c", """
                              #include <HsFFI.h>
                              #include <stddef.h>
                              """))
eval(cfunction(FnName(:hs_init, "julia_hs_init", libAddIntegersHaskell), FnResult(Cvoid, "void"), FnArg[],
               """
               int argc = 0;
               char *argvarray[] = { NULL};
               char **argv = argvarray;
               hs_init(&argc, &argv);
               """))

eval(cfunction(FnName(:hs_exit, "julia_hs_exit", libAddIntegersHaskell), FnResult(Cvoid, "void"), FnArg[], """
                                                                                                           hs_exit();
                                                                                                           """))
end

################################################################################
# Extract Haskell code
using CxxInterface
using .AddIntegersHaskell
AddIntegersHaskell.haskell_write_code!()
AddIntegersHaskell.c_write_code!()

################################################################################
# Compile Haskell code
# (This fails if there is no Haskell compiler available)
if false
    # This works on macOS with MacPorts, but not on Github Actions
    using Libdl: dlext
    v = VersionNumber(split(read(`ghc --version`, String))[end])
    run(`ghc -fPIC -c AddIntegersHaskell.hs`)
    run(`ghc -fPIC -c HaskellRTS.c`)
    run(`ghc -shared -o libAddIntegersHaskell.$dlext AddIntegersHaskell.o HaskellRTS.o -lffi -lHSrts`)
    
    # Please, DO NOT call a Haskell compiler manually in your own Julia
    # packages. This works only in very controlled environments such as on
    # CI infrastructure. If you do, your package will be fragile, and will
    # create lots of headaches for your users in the wild. Instead, use
    # [BinaryBuilder](https://binarybuilder.org) and store your build
    # recipes on [Yggdrasil](https://github.com/JuliaPackaging/Yggdrasil).
    
    ################################################################################
    # Call the wrapped function
    # (This fails if the Haskell compiler is not compatible with the
    # currently running Julia executable)
    
    # Only test cases where the Github CI environment supports this (:i686 is not supported)
    if Sys.ARCH ≡ :x86_64
        AddIntegersHaskell.hs_init()
        @test AddIntegersHaskell.add_int(2, 3) == 5
        AddIntegersHaskell.hs_exit()
    end
end
