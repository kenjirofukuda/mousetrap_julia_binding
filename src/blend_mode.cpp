#include "../mousetrap_julia_binding.hpp"

// ### BLEND MODE

static void implement_blend_mode(jlcxx::Module& module)
{
    define_enum_in(module, BlendMode);
    module.add_enum_value(BlendMode, BLEND_MODE, NONE);
    module.add_enum_value(BlendMode, BLEND_MODE, NORMAL);
    module.add_enum_value(BlendMode, BLEND_MODE, ADD);
    module.add_enum_value(BlendMode, BLEND_MODE, SUBTRACT);
    module.add_enum_value(BlendMode, BLEND_MODE, REVERSE_SUBTRACT);
    module.add_enum_value(BlendMode, BLEND_MODE, MULTIPLY);
    module.add_enum_value(BlendMode, BLEND_MODE, MIN);
    module.add_enum_value(BlendMode, BLEND_MODE, MAX);

    module.method("set_current_blend_mode", [](BlendMode mode, bool allow_alpha_blend){
        set_current_blend_mode(mode, allow_alpha_blend);
    });
}