################################################################################
# Create Rust crate
mkpath(joinpath("AddIntegersRust", "add-integers"))
write(joinpath("AddIntegersRust", "add-integers", "Cargo.toml"), """
                                                   [package]
                                                   name = "add-integers"
                                                   version = "1.0.0"
                                                   edition = "2021"

                                                   [lib]
                                                   # The library name cannot be camel case
                                                   name = "add_integers_rust"
                                                   crate-type = ["cdylib"]

                                                   [dependencies]
                                                   # serde_dhall = "0.10.1"
                                                   half = "1.8.2"
                                                   """)
mkpath(joinpath("AddIntegersRust", "add-integers", "src"))

################################################################################
# Define wrapped functions
module AddIntegersRust
using CxxInterface

const libAddIntegersRust = joinpath(pwd(), "libadd_integers_rust")

eval(rustsetup())
eval(rustnewfile(joinpath("AddIntegersRust", "add-integers", "src", "lib.rs"), ""))
eval(rustcode("""
              use half::prelude::*;
              """))

eval(rustfunction(FnName(:add_int, "add_int", libAddIntegersRust), FnResult(Int32, "i32", Int, expr -> :(convert(Int, $expr))),
                  [FnArg(:x, Int32, "x", "i32", Integer, identity), FnArg(:y, Int32, "y", "i32", Integer, identity)],
                  "x + y + f16::from_bits(0).to_f32() as i32"))
end

################################################################################
# Extract Rust code
using CxxInterface
using .AddIntegersRust
AddIntegersRust.rust_write_code!()

################################################################################
# Compile Rust code
# (This fails if there is no Rust compiler available)
using Libdl: dlext
run(Cmd(`cargo build --release`; dir=joinpath("AddIntegersRust", "add-integers")))
cp(joinpath("AddIntegersRust", "add-integers", "target", "release", "libadd_integers_rust.$dlext"), "libadd_integers_rust.$dlext";
   force=true)

# Please, DO NOT call a Rust compiler manually in your own Julia
# packages. This works only in very controlled environments such as on
# CI infrastructure. If you do, your package will be fragile, and will
# create lots of headaches for your users in the wild. Instead, use
# [BinaryBuilder](https://binarybuilder.org) and store your build
# recipes on [Yggdrasil](https://github.com/JuliaPackaging/Yggdrasil).

################################################################################
# Call the wrapped function
# (This fails if the Rust compiler is not compatible with the
# currently running Julia executable)

# Only test cases where the Github CI environment supports this (:i686 is not supported)
if Sys.ARCH ≡ :x86_64
    @test AddIntegersRust.add_int(2, 3) == 5
end
