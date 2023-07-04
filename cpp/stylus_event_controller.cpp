#include "../mousetrap_julia_binding.hpp"

// ### STYLUS EVENT CONTROLLER

void implement_stylus_event_controller(jlcxx::Module& module)
{
    define_enum_in(module, ToolType);
    module.add_enum_value(ToolType, TOOL_TYPE, UNKNOWN);
    module.add_enum_value(ToolType, TOOL_TYPE, PEN);
    module.add_enum_value(ToolType, TOOL_TYPE, ERASER);
    module.add_enum_value(ToolType, TOOL_TYPE, BRUSH);
    module.add_enum_value(ToolType, TOOL_TYPE, PENCIL);
    module.add_enum_value(ToolType, TOOL_TYPE, AIRBRUSH);
    module.add_enum_value(ToolType, TOOL_TYPE, LENS);
    module.add_enum_value(ToolType, TOOL_TYPE, MOUSE);

    define_enum_in(module, DeviceAxis);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, X);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, Y);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, DELTA_X);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, DELTA_Y);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, PRESSURE);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, X_TILT);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, Y_TILT);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, WHEEL);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, DISTANCE);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, ROTATION);
    module.add_enum_value(DeviceAxis, DEVICE_AXIS, SLIDER);

    module.method("device_axis_to_string", [](DeviceAxis axis) -> std::string {
        return device_axis_to_string(axis);
    });

    auto stylus = module.add_type(StylusEventController)
    .add_constructor()
    .add_type_method(StylusEventController, get_hardware_id)
    .add_type_method(StylusEventController, get_tool_type)
    .add_type_method(StylusEventController, has_axis)
    .add_type_method(StylusEventController, get_axis_value)
    ;

    add_signal_stylus_down<StylusEventController>(stylus, "StylusEventController");
    add_signal_stylus_up<StylusEventController>(stylus, "StylusEventController");
    add_signal_proximity<StylusEventController>(stylus, "StylusEventController");
    add_signal_motion<StylusEventController>(stylus, "StylusEventController");
}