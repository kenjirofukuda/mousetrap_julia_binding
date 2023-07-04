#include "../mousetrap_julia_binding.hpp"

// ### TOGGLE BUTTON

void implement_toggle_button(jlcxx::Module& module)
{
    auto toggle = module.add_type(ToggleButton)
        .add_constructor()
        .add_type_method(ToggleButton, get_is_active)
        .add_type_method(ToggleButton, set_is_active, !)
        .method("set_child!", [](ToggleButton& self, void* widget){
            self.set_child(*((Widget*) widget));
        })
        .method("set_icon!", [](ToggleButton& self, Icon& icon){
            self.set_icon(icon);
        })
        .add_type_method(ToggleButton, remove_child)
        .add_type_method(ToggleButton, set_has_frame)
        .add_type_method(ToggleButton, get_has_frame)
        .add_type_method(ToggleButton, set_is_circular)
        .add_type_method(ToggleButton, get_is_circular)
    ;

    add_signal_toggled<ToggleButton>(toggle, "ToggleButton");
    add_signal_activate<ToggleButton>(toggle, "ToggleButton");
    add_signal_clicked<ToggleButton>(toggle, "ToggleButton");
}