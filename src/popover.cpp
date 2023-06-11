#include "../mousetrap_julia_binding.hpp"

// ### POPOVER

static void implement_popover(jlcxx::Module& module)
{
    auto popover = module.add_type(Popover)
    .add_type_method(Popover, popup, !)
    .add_type_method(Popover, popdown, !)
    .add_type_method(Popover, present, !)
    .method("set_child!", [](Popover& popover, void* widget){
        popover.set_child(*((Widget*) widget));
    })
    .add_type_method(Popover, remove_child, !)
    .method("attach_to!", [](Popover& popover, void* widget){
        popover.attach_to(*((Widget*) widget));
    })
    .add_type_method(Popover, set_relative_position, !)
    .add_type_method(Popover, get_relative_position)
    .add_type_method(Popover, set_autohide, !)
    .add_type_method(Popover, get_autohide)
    .add_type_method(Popover, set_has_base_arrow, !)
    .add_type_method(Popover, get_has_base_arrow)
    ;

    add_widget_signals<Popover>(popover, "Popover");
    add_signal_closed<Popover>(popover, "Popover");
}
