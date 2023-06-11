//
// Created by clem on 6/11/23.
#include "../mousetrap_julia_binding.hpp"

// ### ORIENTATION

void implement_orientation(jlcxx::Module& module)
{
    define_enum_in(module, Orientation);
    module.add_enum_value(Orientation, ORIENTATION, HORIZONTAL);
    module.add_enum_value(Orientation, ORIENTATION, VERTICAL);
}