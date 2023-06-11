#include "../mousetrap_julia_binding.hpp"


// ### SCALE

void implement_scale(jlcxx::Module& module)
{
    auto scale = module.add_type(Scale)
    .add_constructor(float, float, float, Orientation)
    .method("get_adjustment", [](Scale& self) -> void* {
        return self.get_adjustment().get_internal();
    })
    .add_type_method(Scale, get_lower)
    .add_type_method(Scale, get_upper)
    .add_type_method(Scale, get_value)
    .add_type_method(Scale, get_increment)
    .add_type_method(Scale, set_lower, !)
    .add_type_method(Scale, set_upper, !)
    .add_type_method(Scale, set_value, !)
    .add_type_method(Scale, set_increment, !)
    ;

    add_widget_signals<Scale>(scale, "Scale");
    add_signal_value_changed<Scale>(scale, "Scale");
}