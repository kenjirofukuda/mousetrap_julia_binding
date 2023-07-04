#include "../mousetrap_julia_binding.hpp"

void implement_popover_button(jlcxx::Module& module)
{
    auto popover_button = module.add_type(PopoverButton)
    .add_constructor()
    .method("set_child!", [](PopoverButton& x, void* widget){
        x.set_child(*((Widget*) widget));
    })
    .add_type_method(PopoverButton, remove_child, !)
    .add_type_method(PopoverButton, set_popover, !)
    .add_type_method(PopoverButton, set_popover_menu, !)
    .add_type_method(PopoverButton, set_relative_position, !)
    .add_type_method(PopoverButton, get_relative_position)
    .add_type_method(PopoverButton, remove_popover, !)
    .add_type_method(PopoverButton, set_always_show_arrow, !)
    .add_type_method(PopoverButton, get_always_show_arrow)
    .add_type_method(PopoverButton, set_has_frame, !)
    .add_type_method(PopoverButton, get_has_frame)
    .add_type_method(PopoverButton, popup, !)
    .add_type_method(PopoverButton, popdown, !)
    .add_type_method(PopoverButton, set_is_circular, !)
    .add_type_method(PopoverButton, get_is_circular)
    ;

    add_widget_signals<PopoverButton>(popover_button, "PopoverButton");
    add_signal_activate<PopoverButton>(popover_button, "PopoverButton");
}
