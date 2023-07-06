# Note that this script can accept some limited command-line arguments, run
# `julia build_tarballs.jl --help` to see a usage message.
using BinaryBuilder, Pkg

name = "mousetrap_linux"
version = v"0.1.0"

# Collection of sources required to complete build
sources = [
    GitSource("https://github.com/Clemapfel/mousetrap.git", "35c4aafec5471a0279d033d6640717ca53b014f8"),
    GitSource("https://github.com/Clemapfel/mousetrap_julia_binding.git", "bdcf6442410fe30a68a2b074bc42ca4352481614")
]

# Bash recipe for building across all platforms
script = raw"""
cd $WORKSPACE/srcdir
cd mousetrap
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$prefix -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TARGET_TOOLCHAIN} -DGTK_INCLUDE_DIRS="$prefix/include/gtk-4.0;$prefix/include/glib-2.0;$prefix/include/glib-2.0/glib;$prefix/lib/glib-2.0/include;$prefix/include/cairo;$prefix/include/pango-1.0;$prefix/include/harfbuzz;$prefix/include/gdk-pixbuf-2.0;$prefix/include/graphene-1.0;$prefix/lib/graphene-1.0/include"
make install -j 8
cd ..
mkdir ${prefix}/share/licenses/mousetrap_linux
cp LICENSE ${prefix}/share/licenses/mousetrap_linux/LICENSE
cd ..
cd mousetrap_julia_binding/
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$prefix -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TARGET_TOOLCHAIN} -DJulia_INCLUDE_DIRS=$prefix/include/julia
make install -j 8
exit
"""

# These are the platforms we will build for by default, unless further
# platforms are passed in on the command line
platforms = [
    Platform("i686", "linux"; libc = "glibc"),
    Platform("x86_64", "linux"; libc = "glibc"),
    Platform("aarch64", "linux"; libc = "glibc"),
    Platform("powerpc64le", "linux"; libc = "glibc"),
    Platform("x86_64", "linux"; libc = "musl"),
    Platform("aarch64", "linux"; libc = "musl"),
    Platform("x86_64", "freebsd"; ),
]

# The products that we will ensure are always built
products = [
    LibraryProduct("libmousetrap", :mousetrap_linux),
    LibraryProduct("libmousetrap_julia_binding", :mousetrap_julia_binding_linux)
]

# Dependencies that must be installed before this package can be built
dependencies = [
    Dependency(PackageSpec(name="GLEW_jll", uuid="bde7f898-03f7-559e-8810-194d950ce600"))
    Dependency(PackageSpec(name="GTK4_jll", uuid="6ebb71f1-8434-552f-b6b1-dc18babcca63"))
    Dependency(PackageSpec(name="OpenGLMathematics_jll", uuid="cc7be9be-d298-5888-8f50-b85d5f9d6d73"))
    Dependency(PackageSpec(name="GLU_jll", uuid="bd17208b-e95e-5925-bf81-e2f59b3e5c61"))
    Dependency(PackageSpec(name="libcxxwrap_julia_jll", uuid="3eaa8342-bff7-56a5-9981-c04077f7cee7"))
    Dependency(PackageSpec(name="libjulia_jll", uuid="5ad3ddd2-0711-543a-b040-befd59781bbf"))
]

# Build the tarballs, and possibly a `build.jl` as well.
build_tarballs(ARGS, name, version, sources, script, platforms, products, dependencies; julia_compat="1.7", preferred_gcc_version = v"12.1.0")
