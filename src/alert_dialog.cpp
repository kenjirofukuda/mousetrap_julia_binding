//
// Created by clem on 6/26/23.
//

#include "../mousetrap_julia_binding.hpp"

void implement_alert_dialog(jlcxx::Module& module)
{
    auto dialog = module.add_type(AlertDialog)
        .constructor([](jl_value_t* buttons, const std::string& message, const std::string& detailed_message){
            auto vec = std::vector<std::string>();
            for (size_t i = 0; i < jl_array_len(buttons); ++i)
            {
                auto* ptr = jl_string_ptr(jl_arrayref((jl_array_t*) buttons, i));
                if (ptr != nullptr)
                    vec.emplace_back(ptr);
            }
            return new AlertDialog(vec, message, detailed_message);
        }, USE_FINALIZERS)
        .add_type_method(AlertDialog, add_button, !)
        .add_type_method(AlertDialog, remove_button, !)
        .add_type_method(AlertDialog, set_button_label, !)
        .add_type_method(AlertDialog, get_button_label)
        .add_type_method(AlertDialog, get_n_buttons)
        .add_type_method(AlertDialog, get_message)
        .add_type_method(AlertDialog, set_message, !)
        .add_type_method(AlertDialog, get_detailed_description)
        .add_type_method(AlertDialog, set_detailed_description, !)
        .add_type_method(AlertDialog, set_is_modal, !)
        .add_type_method(AlertDialog, get_is_modal)
        .add_type_method(AlertDialog, present, !)
    ;

    dialog.method("on_selection!", [](AlertDialog& self, jl_value_t* task) {
        self.on_selection([](AlertDialog& self, int index, jl_value_t* task){
            jl_safe_call("ColorChooser::on_accept", task, jlcxx::box<AlertDialog&>(self), jl_box_int32(index));
        }, gc_protect(self, task));
    });
}
