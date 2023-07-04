// ### PAN EVENT CONTROLLER

#include "../mousetrap_julia_binding.hpp"

void implement_pan_event_controller(jlcxx::Module& module)
{
    define_enum_in(module, PanDirection);
    module.add_enum_value(PanDirection, PAN_DIRECTION, LEFT);
    module.add_enum_value(PanDirection, PAN_DIRECTION, RIGHT);
    module.add_enum_value(PanDirection, PAN_DIRECTION, UP);
    module.add_enum_value(PanDirection, PAN_DIRECTION, DOWN);

    auto pan = module.add_type(PanEventController)
    .add_constructor(Orientation)
    .add_type_method(PanEventController, set_orientation, !)
    .add_type_method(PanEventController, get_orientation)
    ;

    add_signal_pan<PanEventController>(pan, "PanEventController");
}