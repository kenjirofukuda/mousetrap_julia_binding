#include "../mousetrap_julia_binding.hpp"

// ### SCROLL EVENT CONTROLLER

void implement_scroll_event_controller(jlcxx::Module& module)
{
    auto scroll = module.add_type(ScrollEventController)
    .constructor<bool>(USE_FINALIZERS)
    .add_type_method(ScrollEventController, get_kinetic_scrolling_enabled)
    .add_type_method(ScrollEventController, set_kinetic_scrolling_enabled, !)
    ;

    add_signal_kinetic_scroll_decelerate<ScrollEventController>(scroll, "ScrollEventController");
    add_signal_scroll_begin<ScrollEventController>(scroll, "ScrollEventController");
    add_signal_scroll<ScrollEventController>(scroll, "ScrollEventController");
    add_signal_scroll_end<ScrollEventController>(scroll, "ScrollEventController");
}
