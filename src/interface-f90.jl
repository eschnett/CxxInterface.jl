# Fortran 90

function f90setup()
    quote
        const f90_filename = Ref{AbstractString}("code.f90")
        function set_f90_filename!(filename::AbstractString)
            return f90_filename[] = filename
        end

        const f90_chunks = Dict{AbstractString,Vector{String}}()
        function f90_add_code!(f90_code::AbstractString)
            return push!(get!(f90_chunks, f90_filename[], String[]), f90_code)
        end
        function f90_get_code()
            iobuffer = IOBuffer()
            allcode = Dict{AbstractString,String}()
            for (filename, chunks) in f90_chunks
                for chunk in chunks
                    println(iobuffer, chunk)
                end
                allcode[filename] = String(take!(iobuffer))
            end
            return allcode
        end
        function f90_write_code!()
            println("Generating Fortran code:")
            allcode = f90_get_code()
            for (filename, content) in allcode
                println("Generating $filename...")
                write(filename, content)
            end
            println("Done.")
            return nothing
        end
    end
end
export f90setup

function f90newfile(filename::AbstractString, f90_stmts::AbstractString)
    f90_code = """
               $f90_stmts
               """
    quote
        set_f90_filename!($filename)
        f90_add_code!($f90_code)
    end
end
export f90newfile

function f90code(f90_stmts::AbstractString)
    f90_code = """
               $f90_stmts
               """
    quote
        f90_add_code!($f90_code)
    end
end
export f90code

function f90function(name::FnName, result::FnResult, arguments::AbstractVector{FnArg}, f90_stmts::AbstractString)
    julia_code = quote
        function $(name.julia_name)($([:($(arg.julia_name)::$(arg.initial_julia_type)) for arg in arguments]...))
            res = ccall(($(QuoteNode(Symbol(name.cxx_name, "_"))), $(name.cxx_library)), $(result.julia_type),
                        ($([arg.julia_type for arg in arguments if !arg.skip]...),),
                        $([arg.convert_from_initial(arg.julia_name) for arg in arguments if !arg.skip]...))
            return $(result.convert_to_final(:res))::$(result.final_julia_type)
        end
    end
    julia_code = clean_code(julia_code)
    simple_julia_code = simplify_code(julia_code)

    f90_code = """
        ! $(join(split(string(simple_julia_code), "\n"), "\n! "))
        $(result.cxx_type == "void" ? "subroutine" : "$(result.cxx_type) function") $(name.cxx_name)($(join(["$(arg.cxx_name)" for arg in arguments if !arg.skip], ", ")))
            implicit none
            $(join(["$(arg.cxx_type) :: $(arg.cxx_name)" for arg in arguments if !arg.skip], "\n    "))
            $f90_stmts
        end $(result.cxx_type == "void" ? "subroutine" : "function") $(name.cxx_name)
        """
    quote
        f90_add_code!($f90_code)
        $julia_code
    end
end
export f90function
