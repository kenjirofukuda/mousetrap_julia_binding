#include "../mousetrap_julia_binding.hpp"

void implement_theme(jlcxx::Module& module)
{
    define_enum_in(module, Theme);
    module.add_enum_value(Theme, THEME, DEFAULT_LIGHT);
    module.add_enum_value(Theme, THEME, DEFAULT_LIGHT);
    module.add_enum_value(Theme, THEME, HIGH_CONTRAST_LIGHT);
    module.add_enum_value(Theme, THEME, HIGH_CONTRAST_DARK);
}