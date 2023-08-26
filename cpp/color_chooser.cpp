//
// Created by clem on 6/25/23.
//

#include "../mousetrap_julia_binding.hpp"

void implement_color_chooser(jlcxx::Module& module)
{
    #if GTK_MINOR_VERSION >= 10

    auto chooser = module.add_type(ColorChooser)
        .add_constructor(const std::string&)
        .add_type_method(ColorChooser, present, !)
        .method("get_color", [](ColorChooser& self){
            return box_rgba(RGBA(0, 0, 0, 0)); //self.get_color());
        })
        .add_type_method(ColorChooser, set_is_modal,!)
        .add_type_method(ColorChooser, get_is_modal)
        .add_type_method(ColorChooser, set_title, !)
        .add_type_method(ColorChooser, get_title)
    ;

    chooser.method("on_accept!", [](ColorChooser& self, jl_value_t* task) {
        self.on_accept([](ColorChooser& self, RGBA color, jl_value_t* task){
            jl_safe_call("ColorChooser::on_accept", task, jlcxx::box<ColorChooser&>(self), box_rgba(color));
        }, gc_protect(self, task));
    });

    chooser.method("on_cancel!", [](ColorChooser& self, jl_value_t* task) {
        self.on_cancel([](ColorChooser& self, jl_value_t* task){
            jl_safe_call("ColorChooser::on_accept", task, jlcxx::box<ColorChooser&>(self));
        }, gc_protect(self, task));
    });
    
    #endif
}
