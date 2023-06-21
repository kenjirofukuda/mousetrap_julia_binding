#include "../mousetrap_julia_binding.hpp"

// ### SWIPE EVENT CONTROLLER

void implement_swipe_event_controller(jlcxx::Module& module)
{
    auto swipe = module.add_type(SwipeEventController)
    .add_constructor()
    .method("get_velocity", [](SwipeEventController& x) -> jl_value_t* {
        return box_vector2f(x.get_velocity());
    });

    add_signal_swipe<SwipeEventController>(swipe, "SwipeEventController");
}