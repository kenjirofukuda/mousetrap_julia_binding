//
// Created by clem on 6/11/23.
//
#include "../mousetrap_julia_binding.hpp"

// ### NOTEBOOK

void implement_notebook(jlcxx::Module& module)
{
    auto notebook = module.add_type(Notebook)
    .constructor<>(USE_FINALIZERS)
    .method("push_front!", [](Notebook& self, void* child_widget, void* label_widget){
        return self.push_front(*((Widget*) child_widget), *((Widget*) label_widget));
    })
    .method("push_back!", [](Notebook& self, void* child_widget, void* label_widget){
        return self.push_back(*((Widget*) child_widget), *((Widget*) label_widget));
    })
    .method("insert!", [](Notebook& self, uint64_t new_position, void* child_widget, void* label_widget) {
        return self.insert(new_position, *((Widget*) child_widget), *((Widget*) label_widget));
    })
    .add_type_method(Notebook, move_page_to, !)
    .add_type_method(Notebook, remove, !)
    .add_type_method(Notebook, next_page, !)
    .add_type_method(Notebook, previous_page, !)
    .add_type_method(Notebook, goto_page, !)
    .add_type_method(Notebook, get_current_page)
    .add_type_method(Notebook, get_n_pages)
    .add_type_method(Notebook, set_is_scrollable, !)
    .add_type_method(Notebook, get_is_scrollable)
    .add_type_method(Notebook, set_has_border, !)
    .add_type_method(Notebook, get_has_border)
    .add_type_method(Notebook, set_tabs_visible, !)
    .add_type_method(Notebook, get_tabs_visible)
    .add_type_method(Notebook, set_quick_change_menu_enabled, !)
    .add_type_method(Notebook, get_quick_change_menu_enabled)
    .add_type_method(Notebook, set_tab_position, !)
    .add_type_method(Notebook, get_tab_position)
    .add_type_method(Notebook, set_tabs_reorderable, !)
    .add_type_method(Notebook, get_tabs_reorderable)
    ;

    add_widget_signals<Notebook>(notebook, "Notebook");
    add_signal_page_added<Notebook>(notebook, "Notebook");
    add_signal_page_removed<Notebook>(notebook, "Notebook");
    add_signal_page_reordered<Notebook>(notebook, "Notebook");
    add_signal_page_selection_changed<Notebook>(notebook, "Notebook");
}