#include "../mousetrap_julia_binding.hpp"

void implement_action_bar(jlcxx::Module& module)
{
    auto bar = module.add_type(ActionBar)
    .add_constructor()
    .method("push_back!", [](ActionBar& bar, void* widget){
        bar.push_back(*((Widget*) widget));
    })
    .method("push_front!", [](ActionBar& bar, void* widget){
        bar.push_front(*((Widget*) widget));
    })
    .method("remove!", [](ActionBar& bar, void* to_remove) {
        bar.remove(*((Widget*) to_remove));
    })
    .method("set_center_child!", [](ActionBar& bar, void* to_append, void* after){
        bar.set_center_child(*((Widget*) to_append));
    })
    .add_type_method(ActionBar, remove_center_child, !)
    .add_type_method(ActionBar, set_is_revealed, !)
    .add_type_method(ActionBar, get_is_revealed)
    ;

    add_widget_signals<ActionBar>(bar, "ActionBar");
}