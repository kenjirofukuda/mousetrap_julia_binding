#include "../mousetrap_julia_binding.hpp"

// ### FOCUS EVENT CONTROLLER

void implement_focus_event_controller(jlcxx::Module& module)
{
    auto focus = module.add_type(FocusEventController)
    .add_constructor()
    .add_type_method(FocusEventController, self_or_child_is_focused)
    .add_type_method(FocusEventController, self_is_focused)
    ;

    add_signal_focus_gained<FocusEventController>(focus, "FocusEventController");
    add_signal_focus_lost<FocusEventController>(focus, "FocusEventController");
}//
// Created by clem on 6/11/23.
//
