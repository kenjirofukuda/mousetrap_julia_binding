#include "../mousetrap_julia_binding.hpp"

// ### SPINNER

void implement_spinner(jlcxx::Module& module)
{
    auto spinner = module.add_type(Spinner)
    .add_constructor()
    .add_type_method(Spinner, set_is_spinning, !)
    .add_type_method(Spinner, get_is_spinning)
    .add_type_method(Spinner, start, !)
    .add_type_method(Spinner, stop, !)
    ;

    add_widget_signals<Spinner>(spinner, "Spinner");
}
