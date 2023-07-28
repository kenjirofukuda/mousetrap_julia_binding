const VERSION = "0.1.1"
const mousetrap_commit = "90eb7de30e76a55f73b3a80dcf3691268d8bad0d"
const mousetrap_julia_binding_commit = "14ceea46611cac67f9afdd668f0ef7a3568a0287"

deploy_linux = true
deploy_windows = false

const deploy_local = true
# if local, files will be written to ~/.julia/dev/mousetrap_[linux,windows]_jll 

println("deploy linux   : $deploy_linux")
println("deploy windows : $deploy_windows")
println("local : $deploy_local")

## Configure

function configure_file(path_in::String, path_out::String)
    file_in = open(path_in, "r")
    file_out = open(path_out, "w+")
    
    for line in eachline(file_in)
        write(file_out, replace(line,
            "@MOUSETRAP_COMMIT@" => mousetrap_commit,
            "@MOUSETRAP_JULIA_BINDING_COMMIT@" => mousetrap_julia_binding_commit,
            "@VERSION@" => VERSION
        ) * "\n")
    end
    
    close(file_in)
    close(file_out)
end

if deploy_linux
    @info "Configuring `linux/build_tarballs.jl`"
    configure_file("./linux/build_tarballs.jl.in", "./linux/build_tarballs.jl")
end

if deploy_windows
    @info "Configuring `windows/build_tarballs.jl`"
    configure_file("./windows/build_tarballs.jl.in", "./windows/build_tarballs.jl")
end

## Build

cd("./linux")

if deploy_linux
    run(`julia build_tarballs.jl`)
    if deploy_local
        run(`julia build_tarballs.jl --deploy=local`)
    else
        run(`julia build_tarballs.jl --deploy=Clemapfel/mousetrap_linux_jll`)
    end
end

cd("..")
cd("./windows")

if deploy_windows
    run(`julia build_tarballs.jl`)
    if deploy_local
        run(`julia build_tarballs.jl --deploy=local`)
    else
        run(`julia build_tarballs.jl --deploy=Clemapfel/mousetrap_windows_jll`)
    end
end

cd("..")
