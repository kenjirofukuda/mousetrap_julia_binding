//
// Created by clem on 6/11/23.
//
#include "../mousetrap_julia_binding.hpp"

// ### DRAG EVENT CONTROLLER

static void implement_drag_event_controller(jlcxx::Module& module)
{
    auto drag = module.add_type(DragEventController)
    .constructor()
    .method("get_start_position", [](DragEventController& controller) -> jl_value_t* {
        return box_vector2f(controller.get_start_position());
    })
    .method("get_current_offset", [](DragEventController& controller) -> jl_value_t* {
        return box_vector2f(controller.get_current_offset());
    })
    ;

    add_signal_drag_begin<DragEventController>(drag, "DragEventController");
    add_signal_drag<DragEventController>(drag, "DragEventController");
    add_signal_drag_end<DragEventController>(drag, "DragEventController");
}