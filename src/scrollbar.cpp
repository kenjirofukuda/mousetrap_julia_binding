#include "../mousetrap_julia_binding.hpp"

// ### SCROLLBAR

static void implement_scrollbar(jlcxx::Module& module)
{
    auto scrollbar = module.add_type(Scrollbar)
    .add_constructor(Orientation)
    .method("get_adjustment", [](Scrollbar& self) -> void* {
        return self.get_adjustment().get_internal();
    })
    .add_type_method(Scrollbar, set_orientation, !)
    .add_type_method(Scrollbar, get_orientation)
    ;

    add_widget_signals<Scrollbar>(scrollbar, "Scrollbar");
}
