//
// Created by clem on 6/11/23.
//

#include "../mousetrap_julia_binding.hpp"

// ### LONG PRESS EVENT CONTROLLER

static void implement_long_press_event_controller(jlcxx::Module& module)
{
    auto long_press = module.add_type(LongPressEventController)
    .add_type_method(LongPressEventController, set_delay_factor)
    .add_type_method(LongPressEventController, get_delay_factor)
    ;

    add_signal_pressed<LongPressEventController>(long_press, "LongPressEventController");
    add_signal_press_cancelled<LongPressEventController>(long_press, "LongPressEventController");
}
