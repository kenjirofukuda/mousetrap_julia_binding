#include "../mousetrap_julia_binding.hpp"

void implement_motion_event_controller(jlcxx::Module& module)
{
    auto motion = module.add_type(MotionEventController)
    .constructor<>(USE_FINALIZERS)
    ;

    add_signal_motion_enter<MotionEventController>(motion, "MotionEventController");
    add_signal_motion<MotionEventController>(motion, "MotionEventController");
    add_signal_motion_leave<MotionEventController>(motion, "MotionEventController");
}