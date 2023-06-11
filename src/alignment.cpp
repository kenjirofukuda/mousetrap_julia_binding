#include "../mousetrap_julia_binding.hpp"

// ### ALIGNMENT

static void implement_alignment(jlcxx::Module& module)
{
    define_enum_in(module, Alignment);
    module.add_enum_value(Alignment, ALIGNMENT, START);
    module.add_enum_value(Alignment, ALIGNMENT, CENTER);
    module.add_enum_value(Alignment, ALIGNMENT, END);
}
