//
// Created by clem on 8/26/23.
//

#include "../mousetrap_julia_binding.hpp"

void implement_flowbox(jlcxx::Module& module)
{
    auto box = module.add_type(FlowBox)
        .add_constructor(Orientation)
        .method("push_back!", [](FlowBox& view, void* widget) -> void {
            view.push_back(*((Widget*) widget));
        })
        .method("push_front!", [](FlowBox& view, void* widget) -> void {
            view.push_front(*((Widget*) widget));
        })
        .method("insert!", [](FlowBox& view, uint64_t i, void* widget) -> void {
            view.insert(*((Widget*) widget), i);
        })
        .method("remove!", [](FlowBox& view, void* widget) -> void {
            view.remove(*((Widget*) widget));
        })
        .add_type_method(FlowBox, clear, !)
        .add_type_method(FlowBox, set_homogeneous, !)
        .add_type_method(FlowBox, get_homogeneous)
        .add_type_method(FlowBox, set_row_spacing, !)
        .add_type_method(FlowBox, get_row_spacing)
        .add_type_method(FlowBox, set_column_spacing, !)
        .add_type_method(FlowBox, get_column_spacing)
        .add_type_method(FlowBox, get_n_items)
        .add_type_method(FlowBox, set_orientation, !)
        .add_type_method(FlowBox, get_orientation)
    ;

    add_widget_signals<FlowBox>(box, "FlowBox");
}
