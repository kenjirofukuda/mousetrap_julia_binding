#include "../mousetrap_julia_binding.hpp"

// ### FIXED

void implement_fixed(jlcxx::Module& module)
{
    auto fixed = module.add_type(Fixed)
    .add_constructor()
    .method("add_child!", [](Fixed& x, void* widget, jl_value_t* vector2f){
        x.add_child(*((Widget*) widget), unbox_vector2f(vector2f));
    })
    .method("remove_child!", [](Fixed& x, void* widget){
        x.remove_child(*((Widget*) widget));
    })
    .method("set_child_position!", [](Fixed& x, void* widget, jl_value_t* vector2f){
        x.set_child_position(*((Widget*) widget), unbox_vector2f(vector2f));
    })
    ;

    add_widget_signals<Fixed>(fixed, "Fixed");
}
