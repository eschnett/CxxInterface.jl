# Haskell

function haskellsetup()
    quote
        const haskell_filename = Ref{AbstractString}("code.hs")
        function set_haskell_filename!(filename::AbstractString)
            return haskell_filename[] = filename
        end

        const haskell_chunks = Dict{AbstractString,Vector{String}}()
        function haskell_add_code!(haskell_code::AbstractString)
            return push!(get!(haskell_chunks, haskell_filename[], String[]), haskell_code)
        end
        function haskell_get_code()
            iobuffer = IOBuffer()
            allcode = Dict{AbstractString,String}()
            for (filename, chunks) in haskell_chunks
                for chunk in chunks
                    println(iobuffer, chunk)
                end
                allcode[filename] = String(take!(iobuffer))
            end
            return allcode
        end
        function haskell_write_code!()
            println("Generating Haskell code:")
            allcode = haskell_get_code()
            for (filename, content) in allcode
                println("Generating $filename...")
                write(filename, content)
            end
            println("Done.")
            return nothing
        end
    end
end
export haskellsetup

function haskellnewfile(filename::AbstractString, haskell_stmts::AbstractString)
    haskell_code = """
               {-# LANGUAGE ForeignFunctionInterface #-}
               module $(split(filename, ".")[1]) where
               import Foreign.C.Types

               $haskell_stmts
               """
    quote
        set_haskell_filename!($filename)
        haskell_add_code!($haskell_code)
    end
end
export haskellnewfile

function haskellcode(haskell_stmts::AbstractString)
    haskell_code = """
               $haskell_stmts
               """
    quote
        haskell_add_code!($haskell_code)
    end
end
export haskellcode

function haskellfunction(name::FnName, result::FnResult, arguments::AbstractVector{FnArg}, haskell_stmts::AbstractString)
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

    haskell_code = """
        {-
        $(string(simple_julia_code))
        -}
        $(name.cxx_name) :: $(join([arg.cxx_type for arg in arguments if !arg.skip], " -> ")) -> $(result.cxx_type)
        $(name.cxx_name) $(join([arg.cxx_name for arg in arguments if !arg.skip], " ")) =
            $(join(split(haskell_stmts, "\n"), "\n    "))
        foreign export ccall $(name.cxx_name) :: $(join([arg.cxx_type for arg in arguments if !arg.skip], " -> ")) -> $(result.cxx_type)
        """
    quote
        haskell_add_code!($haskell_code)
        $julia_code
    end
end
export haskellfunction
