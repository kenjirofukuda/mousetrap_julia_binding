
#include "../mousetrap_julia_binding.hpp"

// ### JUSTIFY MODE

void implement_justify_mode(jlcxx::Module& module)
{
    define_enum_in(module, JustifyMode);
    module.add_enum_value(JustifyMode, JUSTIFY_MODE, LEFT);
    module.add_enum_value(JustifyMode, JUSTIFY_MODE, RIGHT);
    module.add_enum_value(JustifyMode, JUSTIFY_MODE, CENTER);
    module.add_enum_value(JustifyMode, JUSTIFY_MODE, FILL);
}