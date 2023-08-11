# Mousetrap Julia Binding

> **If you are looking to run mousetrap using Julia, you are in the wrong place. Please visit [mousetrap.jl](https://github.com/Clemapfel/mousetrap.jl) instead.**

 Julia-interface for the [mousetrap C++ component](https://github.com/Clemapfel/mousetrap). Imports most C++ classes such 
that they can be wrapped by the macros defined in [`src/mousetrap.jl`](https://github.com/Clemapfel/mousetrap.jl/blob/main/src/mousetrap.jl).

This project contains the code for the Julia interface, as well as all relevant files to cross-compile both the Julia interface and the stand-alone C++ component.

---

## Installation

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
cmake .. -DMOUSETRAP_ENABLE_OPENGL_COMPONENT=ON
make install -j 8
```
Where `make install` may require `sudo` depending on your default install location.

On MacOS, it may be necessary to set `-DMOUSETRAP_ENABLE_OPENGL_COMPONENT=OFF` instead.

---

## `mousetrap_jll` BinaryBuilder package

`mousetrap` and `mousetrap_julia_binding` can be compiled using Julias `BinaryBuilder`. To be able to cross-compile, a 64-bit Linux operating system is required, though the compiled library product work for both linux, windows, and mac. 

### Dependencies

+ Linux operating system
+ [BinaryBuilder](https://github.com/JuliaPackaging/BinaryBuilder.jl)

### Compiling for Linux

For linux, enter `mousetrap_julia_binding/mousetrap_jll`, then enter `/linux`, `/windows`, or `/apple`, depending on which OS you want to cross-compile for, not your actual operating system (which has to linux anyway).

Then, execute (in one of the above listed directories):

```
# in mousetrap_julia_binding/mousetrap_jll/linux (or /windows, /apple)
julia build_tarballs.jl
```

Which will deposit the shared libraries in `mousetrap_julia_binding/mousetrap_jll/*/products`, where `*` is one of `linux`, `windows`, or `apple`.

If you want to instead install a `_jll` package locally, run `julia build_tarballs.jl --deploy=local` instead, which will create a package `mousetrap_*_jll` in your `.julia/dev`, where `*` is one of `linux`, `windows`, or `apple`.

---

