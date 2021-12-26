# C++

function cxxsetup()
    quote
        const cxx_filename = Ref{AbstractString}("code.cxx")
        function set_cxx_filename!(filename::AbstractString)
            return cxx_filename[] = filename
        end

        const cxx_chunks = Dict{AbstractString,Vector{String}}()
        function cxx_add_code!(cxx_code::AbstractString)
            return push!(get!(cxx_chunks, cxx_filename[], String[]), cxx_code)
        end
        function cxx_get_code()
            iobuffer = IOBuffer()
            allcode = Dict{AbstractString,String}()
            for (filename, chunks) in cxx_chunks
                for chunk in chunks
                    println(iobuffer, chunk)
                end
                allcode[filename] = String(take!(iobuffer))
            end
            return allcode
        end
        function cxx_write_code!()
            println("Generating C++ code:")
            allcode = cxx_get_code()
            for (filename, content) in allcode
                println("Generating $filename...")
                write(filename, content)
            end
            println("Done.")
            return nothing
        end
    end
end
export cxxsetup

function cxxnewfile(filename::AbstractString, cxx_stmts::AbstractString)
    cxx_code = """
               #include <ccomplex>
               #include <cstdint>

               $cxx_stmts
               """
    quote
        set_cxx_filename!($filename)
        cxx_add_code!($cxx_code)
    end
end
export cxxnewfile

function cxxcode(cxx_stmts::AbstractString)
    cxx_code = """
               $cxx_stmts
               """
    quote
        cxx_add_code!($cxx_code)
    end
end
export cxxcode

function cxxvariable(name::VarName, type::VarType, cxx_stmts::AbstractString)
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

    cxx_code = """
        /*
        $(string(simple_julia_code))
        */
        extern "C" const $(type.cxx_type) $(name.cxx_name) = [] { $cxx_stmts }();
        """
    quote
        cxx_add_code!($cxx_code)
        $julia_code
    end
end
export cxxvariable

function cxxfunction(name::FnName, result::FnResult, arguments::AbstractVector{FnArg}, cxx_stmts::AbstractString)
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

    cxx_code = """
        /*
        $(string(simple_julia_code))
        */
        extern "C" $(result.cxx_type) $(name.cxx_name)(
            $(join(["$(arg.cxx_type) $(arg.cxx_name)" for arg in arguments if !arg.skip], ",\n    "))
        ) {
            $cxx_stmts
        }
        """
    quote
        cxx_add_code!($cxx_code)
        $julia_code
    end
end
export cxxfunction
