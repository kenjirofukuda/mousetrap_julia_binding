//
// Created by clem on 7/27/23.
//

#include "../mousetrap_julia_binding.hpp"

void implement_clamp_frame(jlcxx::Module& module)
{
    auto frame = module.add_type(ClampFrame)
        .constructor(Orientation)
        .add_type_method(ClampFrame, set_orientation, !)
        .add_type_method(ClampFrame, get_orientation)
        .add_type_method(ClampFrame, set_maximum_size, !)
        .add_type_method(ClampFrame, get_maximum_size)
        .add_type_method(ClampFrame, remove_child, !)
        .method("set_child!", [](ClampFrame& instance, void* widget){
            instance.set_child(*((Widget*) widget));
        });

    add_widget_signals<AspectFrame>(clamp_frame, "AspectFrame");
}
