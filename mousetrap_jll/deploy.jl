const linux_repo = ""
const windows_repo = "Clemapfel/mousetrap_windows_jll"

const mousetrap_commit = "9943035d0a8f9cda54322bbfd818e3b7629fd785"
const mousetrap_julia_binding_commit = "bdcf6442410fe30a68a2b074bc42ca4352481614"

function configure_file(path_in::String, path_out::String)
    file_in = open(path_in, "r")
    file_out = open(path_out, "w+")
    
    for line in eachline(file_in)
        write(file_out, replace(line,
            "@MOUSETRAP_COMMIT@" => mousetrap_commit,
            "@MOUSETRAP_JULIA_BINDING_COMMINT@" => mousetrap_julia_binding_commit
        ) * "\n")
    end
    
    close(file_in)
    close(file_out)
end

configure_file("./linux/build_tarballs.jl.in", "./linux/build_tarballs.jl")
configure_file("./windows/build_tarballs.jl.in", "./windows/build_tarballs.jl")

const build_linux = false
const deploy_linux = false

const build_windows = false
const deploy_windows = true

if build_linux
    @info "Building `mousetrap_linux_jll`..."
    run(`julia ./linux/build_tarballs.jl`)
    @info "Done."
end

if deploy_linux
    @info "Deploying `mousetrap_linux_jll`..."
    run(`julia ./linux/build_tarballs.jl --deploy=Clemapfel/mousetrap_linux_jll`)
    @info "Done."
end

if build_windows
    @info "Building `mousetrap_windows_jll`..."
    run(`julia ./windows/build_tarballs.jl`)
    @info "Done."
end

if deploy_windows
    @info "Deploying `mousetrap_windows_jll`..."
    run(`julia ./windows/build_tarballs.jl --deploy=Clemapfel/mousetrap_windows_jll`)
    @info "Done."
end
