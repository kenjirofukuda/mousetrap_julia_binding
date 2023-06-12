using CxxWrap, Pkg.Artifacts, Test

function __init__() @initcxx end
@wrapmodule("./cmake-build-debug/libmousetrap_julia_binding.a")
@test true