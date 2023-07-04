#include "../mousetrap_julia_binding.hpp"

// ### ROTATE EVENT CONTROLLER

void implement_rotate_event_controller(jlcxx::Module& module)
{
    auto rotate = module.add_type(RotateEventController)
    .add_constructor()
    .method("get_angle_deta", [](RotateEventController& x){
        return x.get_angle_delta().as_radians();
    })
    ;

    add_signal_rotation_changed<RotateEventController>(rotate, "RotateEventController");
}