# CxxInterface.jl

Successor of [Cxx.jl](https://github.com/JuliaInterop/Cxx.jl) and
[CxxWrap.jl](https://github.com/JuliaInterop/CxxWrap.jl). Both are
great libraries. Cxx.jl lets people write C++ code in Julia, whereas
CxxWrap.jl lets people write Julia code in C++.

Unfortunately, it seems that their architecture requires a significant
amount of maintenance to keep up with changes in Julia. Neither
currently (December 2021) support Julia 1.7.

The design of CxxInterface.jl is much simpler than either Cxx.jl or
CxxWrap.jl. Wrapper functions are written in Julia, and they generate
respective C++ wrapper functions via string manipulation that are
called via
[`ccall`](https://docs.julialang.org/en/v1/manual/calling-c-and-fortran-code/).
String manipulation is somewhat tedious, but its large advantage is
that it is a well-supported standard that works independent of C++
compiler and Julia version. The current version of CxxInterface.jl
should continue to work for later versions of Julia without undue
maintenance overhead.

## Example

Let's assume that there is a C++ library `AddIntegers` that provides a
function
```C++
namespace AI {
    int add_int(int x, int y);
}
```
that we want to wrap in Julia. This would look as follows:
```Julia
using CxxInterface
using AddIntegers_jll

cxxprelude("""
    #include <add_integers.hxx>
    """)

eval(cxxfunction(FnName(:add_int, "add_int", libAddIntegers),
                 FnResult(Cint, "int"),
                 [FnArg(:x, Cint, "x", "int"),
                  FnArg(:y, Cint, "y", "int")],
                 "return AI::add_int(x, y);"))
```
Most arguments to `cxxfunction` come in pairs, defining what happens
on the Julia side (using symbols and Julia types) as well as what
happens on the C++ side (using strings). In detail:
- The wrapper function has the name `add_int` both in Julia and C++
- The first function argument is called `x` in both Julia and C++, and
  has the type `Cint` in Julia and `int` in C++
- Similarly for the second function argument `y`
- The C++ wrapper code is given as a string.

When this module is loaded, it will generate the Julia function
```Julia
function add_int(x::Cint, y::Cint)
    return ccall(("add_int", libAddIntegers), Cint, (Cint, Cint), x, y)
end
```

It will also generate the respective C++ code as a string:
```C++
#include <add_integers.hxx>

extern "C" int add_int(int x, int y) {
    return AI::add_int(x, y);
}
```
This C++ code can be written to a file and compiled with a C++
compiler. Ideally, this will happen within a
[BinaryBuilder](https://binarybuilder.org) build script that then also
compiles the generated code for multiple architecture into a [JLL
package](https://docs.binarybuilder.org/stable/jll/). Presumably, that
package would here be called `AddIntegers_jll`.

## Generating C++ Code

This code fragment can be used in a Julia script to generate the C++
code:
```Julia
using CxxInterface

using AddIntegers

println("Generating add_int.cxx...")
open("add_int.cxx", "w") do file
    println(file, AddIntegers.cxx_code())
end
```

For convenience, the generated C++ code also contains the generated
Julia code as comments. This code is not used anywhere, but helps
understand the generated code.

See the package [STL.jl](https://github.com/eschnett/STL.jl), where
such a script is used in `deps/build.jl`.

## Modifying Input and Output types

In many cases, either the input types of a wrapper function or the
result should be processed on the Julia side before being passed to
the C++ wrapper function. For example, the Julia `add_int` function
above expects arguments of type `Cint`, and that might be inconvenient
-- we might prefer it to accept arguments of type `Integer` that are
automatically converted to `Cint`. Similarly, it might be convenient
to convert the result type `Cint` to `Int`.

Such code can also be generated automatically:
```Julia
eval(cxxfunction(FnName(:add_int, "AI_add_int", libAddIntegers),
                 FnResult(Cint, "int", Int, expr -> :(convert(Int, $expr))),
                 [FnArg(:x, Cint, "x", "int", Integer, identity),
                  FnArg(:y, Cint, "y", "int", Integer, identity)],
                 "return add_int(x, y);"))
```
The two extra arguments to `FnResult` and `FnArg` describe the final
output type and initial input type, respectively, as well as a
conversion function. This conversion function acts on Julia
expressions while the Julia code is generated; it is not a function
that is applied at run time. The generated Julia function is then
```Julia
function add_int(x::Integer, y::Integer)
    res = ccall(("add_int", libAddIntegers), Cint, (Cint, Cint),
                convert(Cint, x), convert(Cint, y))
    return convert(Int, res)
end
```
The generated C++ code is unaffected.

## Generic Functions

It is not possible to generate C++ functions at run time. This means
that all types need to be known at compile time; it is not possible to
define a generic (parameterized) wrapper function. However, it is
possible to generate a series of wrapper functions in a loop, as in:
```Julia
types = Set([Int8, Int16, Int32, Int64])
for T in types
    CT = cxxtype[T]    # Find C++ type for T
    NT = cxxname(CT)   # Generate C++ identifier for CT
    eval(cxxfunction(FnName(:add, "add_$CT", libAddIntegers),
                     FnResult(T, CT),
                     [FnArg(:x, T, "x", CT),
                      FnArg(:y, T, "y", CT)],
                     "return x + y;"))
end
```
This generates a Julia function `add` with four methods, one for each
integer type. Note that a single Julia function can have multiple
methods (if the argument types differ), while the generated wrapper
functions use C linkage and thus cannot use overloading. We thus use
the type as prefix to the C++ wrapper function name.

## Real-World Examples

The package [STL.jl](https://github.com/eschnett/STL.jl) wraps the C++
STL types `std::map`, `std::shared_ptr`, and `std::vector` via
CxxInterface.jl.
