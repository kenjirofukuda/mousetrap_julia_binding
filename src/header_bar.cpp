#include "../mousetrap_julia_binding.hpp"

// ### HEADER BAR

static void implement_header_bar(jlcxx::Module& module)
{
    auto bar = module.add_type(HeaderBar)
    .add_constructor()
    .add_constructor(const std::string&)
    .add_type_method(HeaderBar, set_layout, !)
    .add_type_method(HeaderBar, get_layout)
    .add_type_method(HeaderBar, set_show_title_buttons, !)
    .add_type_method(HeaderBar, get_show_title_buttons)
    .method("set_title_widget!", [](HeaderBar& bar, void* widget){
        bar.set_title_widget(*((Widget*) widget));
    })
    .add_type_method(HeaderBar, remove_title_widget)
    .method("push_front!", [](HeaderBar& bar, void* widget){
        bar.push_front(*((Widget*) widget));
    })
    .method("push_back!", [](HeaderBar& bar, void* widget){
        bar.push_back(*((Widget*) widget));
    })
    .method("remove!", [](HeaderBar& bar, void* widget){
        bar.remove(*((Widget*) widget));
    })
    ;

    add_widget_signals<HeaderBar>(bar, "HeaderBar");
}