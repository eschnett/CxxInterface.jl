module GCs

using ComputedFieldTypes

mutable struct GC{T,ST} <: ST
    managed::T
    function GC{T,ST}() where {T,ST}
        res = new{T,ST}(allocate(T))
        finalizer(free, res)
        return res
    end
    GC{T}() where {T} = fulltype(GC{T})()
end
export GC
Base.cconvert(obj::GC) = cconvert(obj.managed)

ComputedFieldTypes.fulltype(::Type{<:GC{T}}) where {T} = GC{T,supertype(T)}

function allocate end
export allocate
function free end
export free

end
