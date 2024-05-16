const VERSION = "0.2.0"
const mousetrap_commit = "333cfbec042acb0cdd641a63ecafc9c413893a86"
const mousetrap_julia_binding_commit = "b94f573dc916af72afb8bd61e26e3ece170f8884"

const linux_repo = "mousetrap_linux_jll"
const windows_repo = "mousetrap_windows_jll"
const apple_repo = "mousetrap_apple_jll"

const deploy_linux = true
const deploy_windows = false
const deploy_apple = false

const deploy_local = true
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

    path = joinpath(homedir(),".julia/dev/$linux_repo")
    if isfile(path)
        run(`rm -r $path`)
    end
end

if deploy_windows
    @info "Configuring `windows/build_tarballs.jl`"
    configure_file("./windows/build_tarballs.jl.in", "./windows/build_tarballs.jl")

    path = joinpath(homedir(),".julia/dev/$windows_repo")
    if isfile(path)
        run(`rm -r $path`)
    end
end

if deploy_apple
    @info "Configuring `apple/build_tarballs.jl`"
    configure_file("./apple/build_tarballs.jl.in", "./apple/build_tarballs.jl")

    path = joinpath(homedir(),".julia/dev/$apple_repo")
    if isfile(path)
        run(`rm -r $path`)
    end
end

## Build

function run_deploy(repo::String)
    run(`julia -t 8 build_tarballs.jl --debug --verbose --deploy=$repo`)
end

cd("./linux")

if deploy_linux
    if deploy_local
        run_deploy("local")
    else
        run_deploy("Clemapfel/$linux_repo")
    end
end

cd("..")
cd("./windows")

if deploy_windows
    if deploy_local
        run_deploy("local")
    else
        run_deploy("Clemapfel/$windows_repo")
    end
end

cd("..")
cd("./apple")

if deploy_apple
    if deploy_local
        run_deploy("local")
    else
        run_deploy("Clemapfel/$apple_repo")
    end
end

cd("..")
