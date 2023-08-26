//
// Created by clem on 8/26/23.
//

#include "../mousetrap_julia_binding.hpp"

namespace mousetrap
{
    void implement_popup_message(jlcxx::Module& module)
    {
        auto message = module.add_type(PopupMessage)
            .add_constructor(const std::string&, const std::string&)
            .add_type_method(PopupMessage, set_title, !)
            .add_type_method(PopupMessage, get_title)
            .add_type_method(PopupMessage, set_button_label, !)
            .add_type_method(PopupMessage, get_button_label)
            .add_type_method(PopupMessage, set_button_action, !)
            .add_type_method(PopupMessage, get_button_action_id)
            ;

        add_signal_dismissed<PopupMessage>(message, "PopupMessage");
        add_signal_button_clicked<PopupMessage>(message, "PopupMessage");

        auto overlay = module.add_type(PopupMessageOverlay)
            .add_constructor()
            .method("set_child!", [](PopupMessageOverlay& self, void* widget) -> void {
                self.set_child(*((Widget*) widget));
            })
            .add_type_method(PopupMessageOverlay, remove_child, !)
            .add_type_method(PopupMessageOverlay, show_message, !)
        ;

        add_widget_signals<PopupMessageOverlay>(overlay, "PopupMessageOverlay");
    }

}
