#include "../mousetrap_julia_binding.hpp"

// ### TOGGLE BUTTON

void implement_toggle_button(jlcxx::Module& module)
{
    auto toggle = module.add_type(ToggleButton)
    .add_constructor()
    .add_type_method(ToggleButton, get_is_active)
    .add_type_method(ToggleButton, set_is_active, !)
    ;

    add_signal_toggled<ToggleButton>(toggle, "ToggleButton");
    add_signal_activate<ToggleButton>(toggle, "ToggleButton");
    add_signal_clicked<ToggleButton>(toggle, "ToggleButton");
}