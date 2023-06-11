using CxxWrap, Pkg.Artifacts, Test

function __init__() @initcxx end
@wrapmodule("./libmousetrap_julia_binding.so")
@test true