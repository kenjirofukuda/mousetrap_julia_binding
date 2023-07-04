#include "../mousetrap_julia_binding.hpp"

// ### SWITCH

void implement_switch(jlcxx::Module& module)
{
    auto widget = module.add_type(Switch)
    .add_constructor()
    .add_type_method(Switch, get_is_active)
    .add_type_method(Switch, set_is_active, !n)
    ;

    add_widget_signals<Switch>(widget, "Switch");
    add_signal_activate<Switch>(widget, "Switch");
}