#
# julia deploy.jl [--deploy=$platforms] [--build=$platforms]
#

const VERSION = "0.1.1"
const mousetrap_commit = "df09eb3b41eeb70ec67c969674ed775d2c0239cd"
const mousetrap_julia_binding_commit = "0fdc8c77bacd842a3f75a14b78e671e0a9515978"

deploy_linux = true
deploy_windows = false

const deploy_local = true
# if local, files will be written to ~/.julia/dev/mousetrap_[linux,windows]_jll 

println("deploy linux   : $deploy_linux")
println("deploy windows : $deploy_windows")

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

if build_linux || deploy_linux
    @info "Configuring `linux/build_tarballs.jl`"
    configure_file("./linux/build_tarballs.jl.in", "./linux/build_tarballs.jl")
end

if build_windows || deploy_windows
    @info "Configuring `windows/build_tarballs.jl`"
    configure_file("./windows/build_tarballs.jl.in", "./windows/build_tarballs.jl")
end

## Build

cd("./linux")

if build_linux
    @info "Building `mousetrap_linux_jll`"
    run(`julia build_tarballs.jl`)
end

if deploy_linux
    @info "Deploying `mousetrap_linux_jll`"
    if deploy_local
        run(`julia build_tarballs.jl --deploy=local`)
    else
        run(`julia build_tarballs.jl --deploy=Clemapfel/mousetrap_linux_jll`)
    end
end

cd("..")
cd("./windows")

if build_windows
    @info "Building `mousetrap_windows_jll`"
    run(`julia build_tarballs.jl`)
end

if deploy_windows
    @info "Deploying `mousetrap_windows_jll`"
    if deploy_local
        run(`julia build_tarballs.jl --deploy=local`)
    else
        run(`julia build_tarballs.jl --deploy=Clemapfel/mousetrap_windows_jll`)
    end
end

cd("..")
