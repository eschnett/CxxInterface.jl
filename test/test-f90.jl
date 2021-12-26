module AddIntegersF90
using CxxInterface

const libAddIntegersF90 = joinpath(pwd(), "libAddIntegersF90")

eval(f90setup())
eval(f90newfile("AddIntegersF90.f90", ""))

eval(f90function(FnName(:add_int, "add_int", libAddIntegersF90), FnResult(Cint, "integer", Int, expr -> :(convert(Int, $expr))),
                 [FnArg(:x, Ref{Cint}, "x", "integer", Integer, identity), FnArg(:y, Ref{Cint}, "y", "integer", Integer, identity)],
                 "add_int = x + y"))
end

################################################################################
# Extract Fortran code
using CxxInterface
using .AddIntegersF90
AddIntegersF90.f90_write_code!()

################################################################################
# Compile Fortran code
# (This fails if there is no Fortran compiler available)
# macOS does not have a Fortran compiler installed by default
if !Sys.isapple()
    using Libdl: dlext
    run(`gfortran -fPIC -c AddIntegersF90.f90`)
    run(`gfortran -shared -o libAddIntegersF90.$dlext AddIntegersF90.o`)

    # Please, DO NOT call a Fortran compiler manually in your own Julia
    # packages. This works only in very controlled environments such as on
    # CI infrastructure. If you do, your package will be fragile, and will
    # create lots of headaches for your users in the wild. Instead, use
    # [BinaryBuilder](https://binarybuilder.org) and store your build
    # recipes on [Yggdrasil](https://github.com/JuliaPackaging/Yggdrasil).

    ################################################################################
    # Call the wrapped function
    # (This fails if the Fortran compiler is not compatible with the
    # currently running Julia executable)

    # Only test cases where the Github CI environment supports this (:i686 is not supported)
    if Sys.ARCH ≡ :x86_64
        @test AddIntegersF90.add_int(2, 3) == 5
    end
end
