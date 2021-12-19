using CxxInterface

open("std_shared_ptr.cxx", "w") do file
    CxxInterface.begin_generate_cxx()
    include("../src/StdSharedPtrs.jl")
    return println(file, CxxInterface.end_generate_cxx())
end

open("std_vector.cxx", "w") do file
    CxxInterface.begin_generate_cxx()
    include("../src/StdVectors.jl")
    return println(file, CxxInterface.end_generate_cxx())
end
