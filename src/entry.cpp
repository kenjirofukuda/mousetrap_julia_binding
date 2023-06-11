#include "../mousetrap_julia_binding.hpp"

// ### ENTRY

static void implement_entry(jlcxx::Module& module)
{
    auto entry = module.add_type(Entry)
    .constructor()
    .add_type_method(Entry, get_text)
    .add_type_method(Entry, set_text, !)
    .add_type_method(Entry, set_max_length, !)
    .add_type_method(Entry, get_max_length)
    .add_type_method(Entry, set_has_frame, !)
    .add_type_method(Entry, get_has_frame)
    .add_type_method(Entry, set_text_visible, !)
    .add_type_method(Entry, get_text_visible)
    .add_type_method(Entry, set_primary_icon, !)
    .add_type_method(Entry, remove_primary_icon)
    .add_type_method(Entry, set_secondary_icon, !)
    .add_type_method(Entry, remove_secondary_icon)
    ;

    add_widget_signals<Entry>(entry, "Entry");
    add_signal_activate<Entry>(entry, "Entry");
    add_signal_text_changed<Entry>(entry, "Entry");
}
