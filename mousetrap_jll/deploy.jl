#
# julia deploy.jl [--deploy=$platforms] [--build=$platforms]
#

const mousetrap_commit = "9943035d0a8f9cda54322bbfd818e3b7629fd785"
const mousetrap_julia_binding_commit = "45980829c4481d0c981c28b71007b060a57c2332"

build_linux = false
deploy_linux = false
build_windows = false
deploy_windows = false

for arg in ARGS
    if occursin("build", arg)
        if occursin("windows", arg) || occursin("Windows", arg) || occursin("all", arg)
            global build_windows = true
        elseif occursin("linux", arg) || occursin("Linux", arg) || occursin("all", arg)
            global build_linux = true
        end
    end

    if occursin("deploy", arg)
        if occursin("windows", arg) || occursin("Windows", arg) || occursin("all", arg)
            global deploy_windows = true
        elseif occursin("linux", arg) || occursn("Linux", arg) || occursin("all", arg)
            global deploy_linux = true
        end
    end
end

println("build linux    : $build_linux")
println("build windows  : $build_windows")
println("deploy linux   : $deploy_linux")
println("deploy windows : $deploy_windows")

## Configure

function configure_file(path_in::String, path_out::String)
    file_in = open(path_in, "r")
    file_out = open(path_out, "w+")
    
    for line in eachline(file_in)
        write(file_out, replace(line,
            "@MOUSETRAP_COMMIT@" => mousetrap_commit,
            "@MOUSETRAP_JULIA_BINDING_COMMIT@" => mousetrap_julia_binding_commit
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
    run(`julia build_tarballs.jl --deploy=Clemapfel/mousetrap_linux_jll`)
end

cd("..")
cd("./windows")

if build_windows
    @info "Building `mousetrap_windows_jll`"
    run(`julia build_tarballs.jl`)
end

if deploy_windows
    @info "Deploying `mousetrap_windows_jll`"
    run(` julia build_tarballs.jl --deploy=Clemapfel/mousetrap_windows_jll`)
end

cd("..")