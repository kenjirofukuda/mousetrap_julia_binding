#include "../mousetrap_julia_binding.hpp"

void implement_paned(jlcxx::Module& module)
{
    auto paned = module.add_type(Paned)
    .add_constructor(Orientation)
    .add_type_method(Paned, get_position)
    .add_type_method(Paned, set_position, !)
    .method("set_start_child!", [](Paned& paned, void* widget){
        paned.set_start_child(*((Widget*) widget));
    })
    .add_type_method(Paned, remove_start_child, !)
    .add_type_method(Paned, set_start_child_resizable, !)
    .add_type_method(Paned, get_start_child_resizable)
    .add_type_method(Paned, set_start_child_shrinkable, !)
    .add_type_method(Paned, get_start_child_shrinkable)
    .method("set_end_child!", [](Paned& paned, void* widget){
        paned.set_end_child(*((Widget*) widget));
    })
    .add_type_method(Paned, remove_end_child, !)
    .add_type_method(Paned, set_end_child_resizable, !)
    .add_type_method(Paned, get_end_child_resizable)
    .add_type_method(Paned, set_end_child_shrinkable, !)
    .add_type_method(Paned, get_end_child_shrinkable)

    .add_type_method(Paned, set_has_wide_handle, !)
    .add_type_method(Paned, get_has_wide_handle)
    .add_type_method(Paned, set_orientation, !)
    .add_type_method(Paned, get_orientation)
    ;

    add_widget_signals<Paned>(paned, "Paned");
}
