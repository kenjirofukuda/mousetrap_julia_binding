const VERSION = "0.1.1"
const mousetrap_commit = "0e67215e7abdbf111ed46ff3f8df310c6e2147ba"
const mousetrap_julia_binding_commit = "73ad67bbd6a2582b0b534e2ea684dc36843ce0ef"

deploy_linux = true
deploy_windows = true

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
