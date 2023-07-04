# Mousetrap Julia Binding

> **If you are looking to run mousetrap using Julia, you are in the wrong place. Please visit [mousetrap.jl](https://github.com/Clemapfel/mousetrap.jl) instead.**

 Julia-interface for the [mousetrap C++ module](https://github.com/Clemapfel/mousetrap). This repo is only relevant for developers of mousetrap themself, not users of the `mousetrap.jl` Julia package.

---

## Table of Content

1. [`mousetrap_julia_binding` shared library](#mousetrapjuliabinding-shared-library)
2. [Mousetrap BinaryBuilder package](#mousetrapjll-binarybuilder-package)<br>
2.1 [Compiling for Linux](#compiling-for-linux)<br>
2.2 [Compiling for Windows](#compiling-for-windows)<br>
3. [Dormouse Executable Bundler](#dormouse-executable-bundler)<br>
3.1 [Installing the Bundler](#dormouse-installation)<br>
3.1 [Bundling for Linux](#bundling-for-linux)<br>
3.2 [Bundling for Windows](#bundling-for-windows)<br>

---

## `mousetrap_julia_binding` shared library

### Dependencies

+ Linux or Windows operating system
+ [mousetrap](https://github.com/Clemapfel/mousetrap)
+ [jlcxx](https://github.com/JuliaInterop/libcxxwrap-julia)
+ [Julia](https://julialang.org/downloads/), installed system-wide

### Installation `mousetrap_julia_binding`

```
git clone https://github.com/Clemapfel/mousetrap_julia_binding.git
cd mousetrap_julia_binding
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=<path>
make install -j 8
```

Where `<path>` is the intended install directory for the shared library. Only `libmousetrap_julia_binding.so` will be desposited.

---

## `mousetrap_jll` BinaryBuilder package

`mousetrap` and `mousetrap_julia_binding` can be compiled using Julias `BinaryBuilder`. This requires a 64-bit Linux 
operating system, though the compiled libraries work for both linux and windows. 

### Dependencies
+ Linux operating system
+ [BinaryBuilder](https://github.com/JuliaPackaging/BinaryBuilder.jl)

### Compiling for Linux

To compile `mousetrap_jll` for linux:

```
git clone https://github.com/Clemapfel/mousetrap_julia_binding.git
cd mousetrap_julia_binding/mousetrap_jll/linux
julia build_tarballs.jl
```

Which will deposit the shared libraries in `mousetrap_julia_binding/linux/products`.

### Compiling for Windows

To cross-compile `mousetrap` for window:

```
git clone https://github.com/Clemapfel/mousetrap_julia_binding.git
cd mousetrap_julia_binding/mousetrap_jll/windows
julia build_tarballs.jl
```

Which will deposit the shared library in `mousetrap_julia_binding/windows/products`.

---

## Dormouse Executable Bundler

> **Note**: This feature is not yet implemented.


