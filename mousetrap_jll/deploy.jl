const VERSION = "0.1.0"
const mousetrap_commit = "dc5a4faf9f916ba67d298e36d6d1eb8ea30d408c"
const mousetrap_julia_binding_commit = "17ed1ffcd90eb78a42373bc594eef2d9d0c1d112"

deploy_linux = false
deploy_windows = true
deploy_apple = false

const deploy_local = false
# if local, files will be written to ~/.julia/dev/mousetrap_[linux,windows,apple]_jll

println("deploy linux   : $deploy_linux")
println("deploy windows : $deploy_windows")
println("deploy apple : $deploy_apple")
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

if deploy_apple
    @info "Configuring `apple/build_tarballs.jl`"
    configure_file("./apple/build_tarballs.jl.in", "./apple/build_tarballs.jl")
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
cd("./apple")

if deploy_apple
    run(`julia build_tarballs.jl`)
        if deploy_local
            run(`julia build_tarballs.jl --deploy=local`)
        else
            run(`julia build_tarballs.jl --deploy=Clemapfel/mousetrap_apple_jll`)
        end
    end
end

cd("..")
