#include "../mousetrap_julia_binding.hpp"

// ### FRAME

void implement_frame(jlcxx::Module& module)
{
    auto frame = module.add_type(Frame)
    .add_constructor()
    .method("set_child!", [](Frame& x, void* child) {
        x.set_child(*((Widget*) child));
    })
    .add_type_method(Frame, remove_child)
    .method("set_label_widget!", [](Frame& x, void* label){
        x.set_label_widget(*((Widget*) label));
    })
    .add_type_method(Frame, remove_label_widget, !)
    .add_type_method(Frame, set_label_x_alignment, !)
    .add_type_method(Frame, get_label_x_alignment)
    ;

    add_widget_signals<Frame>(frame, "Frame");
}