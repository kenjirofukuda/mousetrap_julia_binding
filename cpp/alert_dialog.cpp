//
// Created by clem on 6/26/23.
//

#include "../mousetrap_julia_binding.hpp"

void implement_alert_dialog(jlcxx::Module& module)
{
    #if ADW_MINOR_VERSION >= 2
    auto dialog = module.add_type(AlertDialog)
        .add_constructor(const std::string&, const std::string&)
        .add_type_method(AlertDialog, add_button, !)
        .add_type_method(AlertDialog, set_default_button, !)
        .add_type_method(AlertDialog, set_button_label, !)
        .add_type_method(AlertDialog, get_button_label)
        .add_type_method(AlertDialog, get_n_buttons)
        .method("set_extra_widget!", [](AlertDialog& self, void* widget){
            self.set_extra_widget(*((Widget*) widget));
        })
        .add_type_method(AlertDialog, remove_extra_widget, !)
        .add_type_method(AlertDialog, get_message)
        .add_type_method(AlertDialog, set_message, !)
        .add_type_method(AlertDialog, get_detailed_description)
        .add_type_method(AlertDialog, set_detailed_description, !)
        .add_type_method(AlertDialog, set_is_modal, !)
        .add_type_method(AlertDialog, get_is_modal)
        .add_type_method(AlertDialog, present, !)
        .add_type_method(AlertDialog, close, !)
    ;

    dialog.method("on_selection!", [](AlertDialog& self, jl_value_t* task) {
        self.on_selection([](AlertDialog& self, int index, jl_value_t* task){
            jl_safe_call("ColorChooser::on_accept", task, jlcxx::box<AlertDialog&>(self), jl_box_int32(index));
        }, gc_protect(self, task));
    });
    #endif
}
