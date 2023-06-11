using Tar, Inflate, SHA

filename = "mousetrap_julia_binding.tar.gz"

run(`cp libmousetrap_julia_binding.so mousetrap_julia_binding`)
run(`tar -czvf $filename ./mousetrap_julia_binding`)
run(`rm mousetrap_julia_binding`)
run(`scp $filename cords@kudu.in-berlin.de:/home/user/cords/websites/public_html/`)

git_hash = Tar.tree_hash(IOBuffer(inflate_gzip(filename)));
sha_hash = bytes2hex(open(sha256, filename));

println("""
[mousetrap_julia_binding]
git-tree-sha1 = "$git_hash"

    [[mousetrap_julia_binding.download]]
    url = "http://cords.in-berlin.de/mousetrap_julia_binding.tar.gz"
    sha256 = "$sha_hash"
""")

run(`rm $filename`)
