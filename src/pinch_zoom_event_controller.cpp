#include "../mousetrap_julia_binding.hpp"

static void implement_pinch_zoom_event_controller(jlcxx::Module& module)
{
    auto pinch = module.add_type(PinchZoomEventController)
    .add_constructor()
    .add_type_method(PinchZoomEventController, get_scale_delta)
    ;

    add_signal_scale_changed<PinchZoomEventController>(pinch, "PinchZoomEventController");
}