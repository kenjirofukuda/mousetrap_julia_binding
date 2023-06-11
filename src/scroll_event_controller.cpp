#include "../mousetrap_julia_binding.hpp"

// ### SCROLL EVENT CONTROLLER

void implement_scroll_event_controller(jlcxx::Module& module)
{
    auto scroll = module.add_type(ScrollEventController)
    .add_constructor(bool, bool)
    ;

    add_signal_kinetic_scroll_decelerate<ScrollEventController>(scroll, "ScrollEventController");
    add_signal_scroll_begin<ScrollEventController>(scroll, "ScrollEventController");
    add_signal_scroll<ScrollEventController>(scroll, "ScrollEventController");
    add_signal_scroll_end<ScrollEventController>(scroll, "ScrollEventController");
}
