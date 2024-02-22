#include "../mousetrap_julia_binding.hpp"

// ### CLICK EVENT CONTROLLER

void implement_click_event_controller(jlcxx::Module& module)
{
    auto click = module.add_type(ClickEventController)
    .constructor<>(USE_FINALIZERS)
    ;

    add_signal_click_pressed<ClickEventController>(click, "ClickEventController");
    add_signal_click_released<ClickEventController>(click, "ClickEventController");
    add_signal_click_stopped<ClickEventController>(click, "ClickEventController");
}
//
// Created by clem on 6/11/23.
//
