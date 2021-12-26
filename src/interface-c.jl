# C

function csetup()
    quote
        const c_filename = Ref{AbstractString}("code.c")
        function set_c_filename!(filename::AbstractString)
            return c_filename[] = filename
        end

        const c_chunks = Dict{AbstractString,Vector{String}}()
        function c_add_code!(c_code::AbstractString)
            return push!(get!(c_chunks, c_filename[], String[]), c_code)
        end
        function c_get_code()
            iobuffer = IOBuffer()
            allcode = Dict{AbstractString,String}()
            for (filename, chunks) in c_chunks
                for chunk in chunks
                    println(iobuffer, chunk)
                end
                allcode[filename] = String(take!(iobuffer))
            end
            return allcode
        end
        function c_write_code!()
            println("Generating C code:")
            allcode = c_get_code()
            for (filename, content) in allcode
                println("Generating $filename...")
                write(filename, content)
            end
            println("Done.")
            return nothing
        end
    end
end
export csetup

function cnewfile(filename::AbstractString, c_stmts::AbstractString)
    c_code = """
               #include <complex.h>
               #include <stdint.h>

               $c_stmts
               """
    quote
        set_c_filename!($filename)
        c_add_code!($c_code)
    end
end
export cnewfile

function ccode(c_stmts::AbstractString)
    c_code = """
               $c_stmts
               """
    quote
        c_add_code!($c_code)
    end
end
export ccode

function cvariable(name::VarName, type::VarType, c_expr::AbstractString)
    julia_code = quote
        const $(name.julia_name) = begin
            lib = CxxInterface.dlopen($(name.cxx_library))
            sym = CxxInterface.dlsym(lib, $(name.cxx_name); throw_error=false)
            if sym ≡ nothing
                libname = $(name.cxx_library)
                symname = $(name.cxx_name)
                println("Load error (library \"$libname\", symbol \"$symname\"). You can ignore this error when generating C++ code.")
                nothing
            else
                # ptr = cglobal(($(name.cxx_name), $(name.cxx_library)), $(type.julia_type))
                ptr = cglobal(sym, $(type.julia_type))
                res = unsafe_load(ptr)
                $(type.convert_to_final(:res))::$(type.final_julia_type)
            end
        end
    end
    julia_code = clean_code(julia_code)
    simple_julia_code = simplify_code(julia_code)

    c_code = """
        /*
        $(string(simple_julia_code))
        */
        const $(type.cxx_type) $(name.cxx_name) = $c_expr;
        """
    quote
        c_add_code!($c_code)
        $julia_code
    end
end
export cvariable

function cfunction(name::FnName, result::FnResult, arguments::AbstractVector{FnArg}, c_stmts::AbstractString)
    julia_code = quote
        function $(name.julia_name)($([:($(arg.julia_name)::$(arg.initial_julia_type)) for arg in arguments]...))
            res = ccall(($(name.cxx_name), $(name.cxx_library)), $(result.julia_type),
                        ($([arg.julia_type for arg in arguments if !arg.skip]...),),
                        $([arg.convert_from_initial(arg.julia_name) for arg in arguments if !arg.skip]...))
            return $(result.convert_to_final(:res))::$(result.final_julia_type)
        end
    end
    julia_code = clean_code(julia_code)
    simple_julia_code = simplify_code(julia_code)

    c_code = """
        /*
        $(string(simple_julia_code))
        */
        $(result.cxx_type) $(name.cxx_name)(
            $(join(["$(arg.cxx_type) $(arg.cxx_name)" for arg in arguments if !arg.skip], ",\n    "))
        ) {
            $c_stmts
        }
        """
    quote
        c_add_code!($c_code)
        $julia_code
    end
end
export cfunction
