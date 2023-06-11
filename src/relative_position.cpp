#include "../mousetrap_julia_binding.hpp

// ### RELATIVE POSITION

static void implement_relative_position(jlcxx::Module& module)
{
    define_enum_in(module, RelativePosition);
    module.add_enum_value(RelativePosition, RELATIVE_POSITION, ABOVE);
    module.add_enum_value(RelativePosition, RELATIVE_POSITION, LEFT_OF);
    module.add_enum_value(RelativePosition, RELATIVE_POSITION, RIGHT_OF);
    module.add_enum_value(RelativePosition, RELATIVE_POSITION, BELOW);
}