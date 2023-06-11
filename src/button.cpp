#include "../mousetrap_julia_binding.hpp"

// ### BUTTON

void implement_button(jlcxx::Module& module)
{
    auto button = module.add_type(Button)
    .add_constructor()
    .add_type_method(Button, set_has_frame, !)
    .add_type_method(Button, get_has_frame)
    .add_type_method(Button, set_is_circular, !)
    .add_type_method(Button, get_is_circular)
    .method("set_child!", [](Button& button, void* widget){
        button.set_child(*((Widget*) widget));
    })
    .add_type_method(Button, remove_child, !)
    .add_type_method(Button, set_action, !)
    ;

    add_widget_signals<Button>(button, "Button");
    add_signal_activate<Button>(button, "Button");
    add_signal_clicked<Button>(button, "Button");
}