#include "../mousetrap_julia_binding.hpp"

// ### OVERLAY

void implement_overlay(jlcxx::Module& module)
{
    auto overlay = module.add_type(Overlay)
    .add_constructor()
    .method("set_child!", [](Overlay& overlay, void* child){
        overlay.set_child(*((Widget*) child));
    })
    .add_type_method(Overlay, remove_child)
    .method("add_overlay!", [](Overlay& overlay, void* widget, bool include_in_measurement, bool clip){
        overlay.add_overlay(*((Widget*) widget), include_in_measurement, clip);
    })
    .method("remove_overlay!", [](Overlay& overlay, void* child){
        overlay.remove_overlay(*((Widget*) child));
    })
    ;

    add_widget_signals<Overlay>(overlay, "Overlay");
}