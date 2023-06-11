#include "../mousetrap_julia_binding.hpp"

// ### TEXT VIEW

void implement_text_view(jlcxx::Module& module)
{
    auto text_view = module.add_type(TextView)
    .add_constructor()
    .add_type_method(TextView, get_text)
    .add_type_method(TextView, set_text, !)
    .add_type_method(TextView, set_cursor_visible, !)
    .add_type_method(TextView, get_cursor_visible)
    .add_type_method(TextView, undo, !)
    .add_type_method(TextView, redo, !)
    .add_type_method(TextView, set_was_modified, !)
    .add_type_method(TextView, get_was_modified)
    .add_type_method(TextView, set_editable, !)
    .add_type_method(TextView, get_editable)
    .add_type_method(TextView, set_justify_mode, !)
    .add_type_method(TextView, get_justify_mode)
    .add_type_method(TextView, set_left_margin, !)
    .add_type_method(TextView, get_left_margin)
    .add_type_method(TextView, set_right_margin, !)
    .add_type_method(TextView, get_right_margin)
    .add_type_method(TextView, set_top_margin, !)
    .add_type_method(TextView, get_top_margin)
    .add_type_method(TextView, set_bottom_margin, !)
    .add_type_method(TextView, get_bottom_margin)
    ;

    add_widget_signals<TextView>(text_view, "TextView");
    add_signal_text_changed<TextView>(text_view, "TextView");
    add_signal_undo<TextView>(text_view, "TextView");
    add_signal_redo<TextView>(text_view, "TextView");
}