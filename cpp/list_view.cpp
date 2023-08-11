#include "../mousetrap_julia_binding.hpp"

// ### LIST VIEW

void implement_list_view(jlcxx::Module& module)
{
    auto list_view = module.add_type(ListView)
    .add_constructor(Orientation, SelectionMode)
    .method("push_back!", [](ListView& view, void* widget, void* iterator) -> void* {
        return (void*) view.push_back(*((Widget*) widget), (ListView::Iterator) iterator);
    })
    .method("push_front!", [](ListView& view, void* widget, void* iterator) -> void* {
        return (void*) view.push_front(*((Widget*) widget), (ListView::Iterator) iterator);
    })
    .method("insert!", [](ListView& view, uint64_t i, void* widget, void* iterator) -> void* {
        return (void*) view.insert(*((Widget*) widget), i, (ListView::Iterator) iterator);
    })
    .method("remove!", [](ListView& view, uint64_t index, void* iterator) -> void {
        view.remove(index, (ListView::Iterator) iterator);
    })
    .method("clear!", [](ListView& view, void* iterator) -> void {
        view.clear((ListView::Iterator) iterator);
    })
    .method("set_widget_at!", [](ListView& view, uint64_t index, void* widget, void* iterator) -> void {
        view.set_widget_at(index, *((Widget*) widget), (ListView::Iterator) iterator);
    })
    .method("get_selection_model", [](ListView& view) -> void* {
        return view.get_selection_model()->get_internal();
    })
    .method("find", [](ListView& view, void* widget, void* iterator) -> int {
        return view.find(*((Widget*) widget), (ListView::Iterator) iterator);
    })
    .add_type_method(ListView, set_enable_rubberband_selection, !)
    .add_type_method(ListView, get_enable_rubberband_selection)
    .add_type_method(ListView, set_show_separators, !)
    .add_type_method(ListView, get_show_separators)
    .add_type_method(ListView, set_single_click_activate, !)
    .add_type_method(ListView, get_single_click_activate)
    .add_type_method(ListView, get_n_items)
    .add_type_method(ListView, get_orientation)
    .add_type_method(ListView, set_orientation, !)
    ;

    add_widget_signals<ListView>(list_view, "ListView");
    add_signal_activate_item<ListView>(list_view, "ListView");
}