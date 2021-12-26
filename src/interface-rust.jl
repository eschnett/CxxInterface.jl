# Rust

function rustsetup()
    quote
        const rust_filename = Ref{AbstractString}("code.rust")
        function set_rust_filename!(filename::AbstractString)
            return rust_filename[] = filename
        end

        const rust_chunks = Dict{AbstractString,Vector{String}}()
        function rust_add_code!(rust_code::AbstractString)
            return push!(get!(rust_chunks, rust_filename[], String[]), rust_code)
        end
        function rust_get_code()
            iobuffer = IOBuffer()
            allcode = Dict{AbstractString,String}()
            for (filename, chunks) in rust_chunks
                for chunk in chunks
                    println(iobuffer, chunk)
                end
                allcode[filename] = String(take!(iobuffer))
            end
            return allcode
        end
        function rust_write_code!()
            println("Generating Rust code:")
            allcode = rust_get_code()
            for (filename, content) in allcode
                println("Generating $filename...")
                write(filename, content)
            end
            println("Done.")
            return nothing
        end
    end
end
export rustsetup

function rustnewfile(filename::AbstractString, rust_stmts::AbstractString)
    rust_code = """
               $rust_stmts
               """
    quote
        set_rust_filename!($filename)
        rust_add_code!($rust_code)
    end
end
export rustnewfile

function rustcode(rust_stmts::AbstractString)
    rust_code = """
               $rust_stmts
               """
    quote
        rust_add_code!($rust_code)
    end
end
export rustcode

function rustfunction(name::FnName, result::FnResult, arguments::AbstractVector{FnArg}, rust_stmts::AbstractString)
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

    rust_code = """
        /*
        $(string(simple_julia_code))
        */
        #[no_mangle]
        pub extern "C" fn $(name.cxx_name)(
            $(join(["$(arg.cxx_name): $(arg.cxx_type)" for arg in arguments if !arg.skip], ",\n    "))
        ) -> $(result.cxx_type)
        {
            $rust_stmts
        }
        """
    quote
        rust_add_code!($rust_code)
        $julia_code
    end
end
export rustfunction
