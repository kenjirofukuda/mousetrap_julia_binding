// ### MENU BAR

#include "../mousetrap_julia_binding.hpp"

static void implement_menu_bar(jlcxx::Module& module)
{
    auto menubar = module.add_type(MenuBar)
    .add_constructor(const MenuModel&)
    ;

    add_widget_signals<MenuBar>(menubar, "MenuBar");
}