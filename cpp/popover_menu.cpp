#include "../mousetrap_julia_binding.hpp"

// ### POPOVER MENU

void implement_popover_menu(jlcxx::Module& module)
{
    auto popover_menu = module.add_type(PopoverMenu)
    .constructor<const MenuModel&>(USE_FINALIZERS)
    ;

    add_widget_signals<PopoverMenu>(popover_menu, "PopoverMenu");
    add_signal_closed<PopoverMenu>(popover_menu, "PopoverMenu");
}