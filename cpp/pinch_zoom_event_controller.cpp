#include "../mousetrap_julia_binding.hpp"

void implement_pinch_zoom_event_controller(jlcxx::Module& module)
{
    auto pinch = module.add_type(PinchZoomEventController)
    .constructor<>(USE_FINALIZERS)
    .add_type_method(PinchZoomEventController, get_scale_delta)
    ;

    add_signal_scale_changed<PinchZoomEventController>(pinch, "PinchZoomEventController");
}