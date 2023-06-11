using Tar, Inflate, SHA

filename = "mousetrap_julia_binding.tar.gz"

run(`cp libmousetrap_julia_binding.so mousetrap_julia_binding`)
run(`rm mousetrap_julia_binding`)
run(`tar -czvf $filename ./libmousetrap_julia_binding.so`)
run(`scp $filename cords@kudu.in-berlin.de:/home/user/cords/websites/public_html/`)

println("sha256: ", bytes2hex(open(sha256, filename)))
println("git-tree-sha1: ", Tar.tree_hash(IOBuffer(inflate_gzip(filename))))