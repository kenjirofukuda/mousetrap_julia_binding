#include "../mousetrap_julia_binding.hpp"

// ### BOX

static void implement_box(jlcxx::Module& module)
{
    auto box = module.add_type(Box)
    .add_constructor(Orientation)
    .method("push_back!", [](Box& box, void* widget){
        box.push_back(*((Widget*) widget));
    })
    .method("push_front!", [](Box& box, void* widget){
        box.push_front(*((Widget*) widget));
    })
    .method("insert_after!", [](Box& box, void* to_append, void* after){
        box.insert_after(*((Widget*) to_append), *((Widget*) after));
    })
    .method("remove!", [](Box& box, void* to_remove) {
        box.remove(*((Widget*) to_remove));
    })
    .add_type_method(Box, clear)
    .add_type_method(Box, set_homogeneous, !)
    .add_type_method(Box, get_homogeneous)
    .add_type_method(Box, set_spacing, !)
    .add_type_method(Box, get_spacing)
    .add_type_method(Box, get_n_items)
    .add_type_method(Box, get_orientation)
    .add_type_method(Box, set_orientation, !)
    ;

    add_widget_signals<Box>(box, "Box");
}