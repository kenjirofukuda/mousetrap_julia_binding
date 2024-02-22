#include "../mousetrap_julia_binding.hpp"

// ### SWITCH

void implement_switch(jlcxx::Module& module)
{
    auto widget = module.add_type(Switch)
    .constructor<>(USE_FINALIZERS)
    .add_type_method(Switch, get_is_active)
    .add_type_method(Switch, set_is_active, !)
    ;

    add_widget_signals<Switch>(widget, "Switch");
    add_signal_switched<Switch>(widget, "Switch");
}