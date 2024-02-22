#include "../mousetrap_julia_binding.hpp"

// ### LEVEL BAR

void implement_level_bar(jlcxx::Module& module)
{
    define_enum_in(module, LevelBarMode);
    module.add_enum_value(LevelBarMode, LEVEL_BAR_MODE, CONTINUOUS);
    module.add_enum_value(LevelBarMode, LEVEL_BAR_MODE, DISCRETE);

    auto level_bar = module.add_type(LevelBar)
    .constructor<float, float>(USE_FINALIZERS)
    .add_type_method(LevelBar, add_marker, !)
    .add_type_method(LevelBar, remove_marker, !)
    .add_type_method(LevelBar, set_inverted, !)
    .add_type_method(LevelBar, get_inverted)
    .add_type_method(LevelBar, set_mode, !)
    .add_type_method(LevelBar, get_mode)
    .add_type_method(LevelBar, set_min_value, !)
    .add_type_method(LevelBar, get_min_value)
    .add_type_method(LevelBar, set_max_value, !)
    .add_type_method(LevelBar, get_max_value)
    .add_type_method(LevelBar, set_value, !)
    .add_type_method(LevelBar, get_value)
    .add_type_method(LevelBar, set_orientation, !)
    .add_type_method(LevelBar, get_orientation)
    ;

    add_widget_signals<LevelBar>(level_bar, "LevelBar");
}