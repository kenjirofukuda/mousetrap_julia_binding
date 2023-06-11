#include "../mousetrap_julia_binding.hpp"

// ### WINDOW

static void implement_window(jlcxx::Module& module)
{
    define_enum_in(module, WindowCloseRequestResult);
    module.add_enum_value(WindowCloseRequestResult, WINDOW_CLOSE_REQUEST_RESULT, ALLOW_CLOSE);
    module.add_enum_value(WindowCloseRequestResult, WINDOW_CLOSE_REQUEST_RESULT, PREVENT_CLOSE);

    auto window = module.add_type(Window)
    .add_constructor(Application&)
    .add_type_method(Window, set_application, !)
    .add_type_method(Window, set_maximized, !)
    .add_type_method(Window, set_fullscreen, !)
    .add_type_method(Window, present, !)
    .add_type_method(Window, set_hide_on_close, !)
    .add_type_method(Window, close, !)
    .method("set_child!", [](Window& window, void* widget){
        window.set_child(*((Widget*) widget));
    })
    .add_type_method(Window, remove_child, !)
    .add_type_method(Window, set_destroy_with_parent, !)
    .add_type_method(Window, get_destroy_with_parent)
    .add_type_method(Window, set_title, !)
    .add_type_method(Window, get_title)
    .method("set_titlebar_widget!", [](Window& window, void* widget){
        window.set_titlebar_widget(*((Widget*) widget));
    })
    .add_type_method(Window, remove_titlebar_widget, !)
    .add_type_method(Window, set_is_modal, !)
    .add_type_method(Window, get_is_modal)
    .add_type_method(Window, set_transient_for, !)
    .add_type_method(Window, set_is_decorated, !)
    .add_type_method(Window, get_is_decorated)
    .add_type_method(Window, set_has_close_button, !)
    .add_type_method(Window, get_has_close_button)
    .add_type_method(Window, set_startup_notification_identifier, !)
    .add_type_method(Window, set_focus_visible, !)
    .add_type_method(Window, get_focus_visible)
    .method("set_default_widget!", [](Window& window, void* widget) {
        window.set_default_widget(*((Widget*) widget));
    })
    ;

    add_widget_signals<Window>(window, "Window");
    add_signal_close_request<Window>(window, "Window");
    add_signal_activate_default_widget<Window>(window, "Window");
    add_signal_activate_focused_widget<Window>(window, "Window");
}