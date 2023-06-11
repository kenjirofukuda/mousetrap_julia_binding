#include "../mousetrap_julia_binding.hpp"

// ### CHECK BUTTON

void implement_check_button(jlcxx::Module& module)
{
    define_enum_in(module, CheckButtonState);
    module.add_enum_value(CheckButtonState, CHECK_BUTTON_STATE, ACTIVE);
    module.add_enum_value(CheckButtonState, CHECK_BUTTON_STATE, INCONSISTENT);
    module.add_enum_value(CheckButtonState, CHECK_BUTTON_STATE, INACTIVE);

    auto check_button = module.add_type(CheckButton)
    .add_constructor()
    .add_type_method(CheckButton, set_state, !)
    .add_type_method(CheckButton, get_state)
    .add_type_method(CheckButton, get_is_active)
    ;

    #if GTK_MINOR_VERSION >= 8
    check_button.method("set_child!", [](CheckButton& check_button, void* widget) {
            check_button.set_child(*((Widget*) widget));
        })
        .add_type_method(CheckButton, remove_child);
    #endif

    add_widget_signals<CheckButton>(check_button, "CheckButton");
    add_signal_toggled<CheckButton>(check_button, "CheckButton");
    add_signal_activate<CheckButton>(check_button, "CheckButton");
}