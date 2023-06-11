#include "../mousetrap_julia_binding.hpp"

// ### CENTER BOX

static void implement_center_box(jlcxx::Module& module)
{
    auto center_box = module.add_type(CenterBox)
    .add_constructor(Orientation)
    .method("set_start_child!", [](CenterBox& box, void* widget) {
        box.set_start_child(*((Widget*) widget));
    })
    .method("set_center_child!", [](CenterBox& box, void* widget) {
        box.set_center_child(*((Widget*) widget));
    })
    .method("set_end_child!", [](CenterBox& box, void* widget) {
        box.set_end_child(*((Widget*) widget));
    })
    .add_type_method(CenterBox, remove_start_widget, !)
    .add_type_method(CenterBox, remove_center_widget, !)
    .add_type_method(CenterBox, remove_end_widget, !)
    .add_type_method(CenterBox, get_orientation)
    .add_type_method(CenterBox, set_orientation, !)
    ;

    add_widget_signals<CenterBox>(center_box, "CenterBox");
}