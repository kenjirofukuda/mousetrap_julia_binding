// ### MENU BAR

#include "../mousetrap_julia_binding.hpp"

void implement_menu_bar(jlcxx::Module& module)
{
    auto menubar = module.add_type(MenuBar)
    .constructor<const MenuModel&>(USE_FINALIZERS)
    ;

    add_widget_signals<MenuBar>(menubar, "MenuBar");
}