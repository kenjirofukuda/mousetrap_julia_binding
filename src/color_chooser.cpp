//
// Created by clem on 6/25/23.
//

#include "../mousetrap_julia_binding.hpp"

void implement_color_chooser(jlcxx::Module& module)
{
    #if GTK_MINOR_VERSION >= 10

    auto chooser = module.add_type(ColorChooser)
        .add_constructor(const std::string&, bool)
        .add_type_method(ColorChooser, present, !)
        .method("get_color", [](ColorChooser& self){
            return box_rgba(self.get_color());
        })
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
