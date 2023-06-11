#include "../mousetrap_julia_binding.hpp"

// ### EXPANDER

static void implement_expander(jlcxx::Module& module)
{
    auto expander = module.add_type(Expander)
    .method("set_child!", [](Expander& x, void* widget) {
        x.set_child(*((Widget*) widget));
    })
    .add_type_method(Expander, remove_child, !)
    .method("set_label_widget!", [](Expander& x, void* widget) {
        x.set_label_widget(*((Widget*) widget));
    })
    .add_type_method(Expander, remove_label_widget, !)
    .add_type_method(Expander, get_expanded)
    .add_type_method(Expander, set_expanded)
    ;

    add_widget_signals<Expander>(expander, "Expander");
    add_signal_activate<Expander>(expander, "Expander");
}
