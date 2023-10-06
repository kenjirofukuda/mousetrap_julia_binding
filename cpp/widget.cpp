#include "../mousetrap_julia_binding.hpp"

// ### WIDGET

void implement_widget(jlcxx::Module& module)
{
    define_enum_in(module, TickCallbackResult);
    module.add_enum_value(TickCallbackResult, TICK_CALLBACK_RESULT, CONTINUE);
    module.add_enum_value(TickCallbackResult, TICK_CALLBACK_RESULT, DISCONTINUE);
    module.method("as_native_widget", [](void* widget) -> void*{
        return ((Widget*) widget)->operator GtkWidget*();
    });
    module.method("activate!", [](void* widget) {
        ((Widget*) widget)->activate();
    });
    module.method("set_size_request!", [](void* widget, jl_value_t* vector2f){
        ((Widget*) widget)->set_size_request(unbox_vector2f(vector2f));
    });
    module.method("get_size_request", [](void* widget) {
        return box_vector2f(((Widget*) widget)->get_size_request());
    });
    module.method("set_margin_top!", [](void* widget, float x){
        ((Widget*) widget)->set_margin_top(x);
    });
    module.method("get_margin_top", [](void* widget) -> float {
        return ((Widget*) widget)->get_margin_top();
    });
    module.method("set_margin_bottom!", [](void* widget, float x){
        ((Widget*) widget)->set_margin_bottom(x);
    });
    module.method("get_margin_bottom", [](void* widget) -> float {
        return ((Widget*) widget)->get_margin_bottom();
    });
    module.method("set_margin_start!", [](void* widget, float x){
        ((Widget*) widget)->set_margin_start(x);
    });
    module.method("get_margin_start", [](void* widget) -> float {
        return ((Widget*) widget)->get_margin_start();
    });
    module.method("set_margin_end!", [](void* widget, float x){
        ((Widget*) widget)->set_margin_end(x);
    });
    module.method("get_margin_end", [](void* widget) -> float {
        return ((Widget*) widget)->get_margin_end();
    });
    module.method("set_margin_horizontal!", [](void* widget, float x){
        ((Widget*) widget)->set_margin_horizontal(x);
    });
    module.method("set_margin_vertical!", [](void* widget, float x){
        ((Widget*) widget)->set_margin_vertical(x);
    });
    module.method("set_margin!", [](void* widget, float x){
        ((Widget*) widget)->set_margin(x);
    });
    module.method("set_expand_horizontally!", [](void* widget, bool x){
        ((Widget*) widget)->set_expand_horizontally(x);
    });
    module.method("get_expand_horizontally", [](void* widget) -> bool {
        return ((Widget*) widget)->get_expand_horizontally();
    });
    module.method("set_expand_vertically!", [](void* widget, bool x){
        ((Widget*) widget)->set_expand_vertically(x);
    });
    module.method("get_expand_vertically", [](void* widget) -> bool {
        return ((Widget*) widget)->get_expand_vertically();
    });
    module.method("set_expand!", [](void* widget, bool x){
        ((Widget*) widget)->set_expand(x);
    });
    module.method("set_horizontal_alignment!", [](void* widget, Alignment x) {
        ((Widget*) widget)->set_horizontal_alignment(x);
    });
    module.method("get_horizontal_alignment", [](void* widget) -> Alignment {
        return ((Widget*) widget)->get_horizontal_alignment();
    });
    module.method("set_vertical_alignment!", [](void* widget, Alignment x) {
        ((Widget*) widget)->set_vertical_alignment(x);
    });
    module.method("get_vertical_alignment", [](void* widget) -> Alignment {
        return ((Widget*) widget)->get_vertical_alignment();
    });
    module.method("set_alignment!", [](void* widget, Alignment x) {
        ((Widget*) widget)->set_alignment(x);
    });
    module.method("set_opacity!", [](void* widget, float x){
        ((Widget*) widget)->set_opacity(x);
    });
    module.method("get_opacity", [](void* widget) -> float {
        return ((Widget*) widget)->get_opacity();
    });
    module.method("set_is_visible!", [](void* widget, bool x){
        ((Widget*) widget)->set_is_visible(x);
    });
    module.method("get_is_visible", [](void* widget) -> bool {
        return ((Widget*) widget)->get_is_visible();
    });
    module.method("set_tooltip_text!", [](void* widget, const std::string& text){
        ((Widget*) widget)->set_tooltip_text(text);
    });
    module.method("set_tooltip_widget!", [](void* self, void* tooltip) {
        ((Widget*) self)->set_tooltip_widget(*((Widget*) tooltip));
    });
    module.method("remove_tooltip_widget!", [](void* widget){
        ((Widget*) widget)->remove_tooltip_widget();
    });
    module.method("set_cursor!", [](void* self, CursorType cursor) {
        ((Widget*) self)->set_cursor(cursor);
    });
    module.method("set_cursor_from_image!", [](void* self, Image& image, int offset_x, int offset_y){
        ((Widget*) self)->set_cursor_from_image(image, Vector2i(offset_x, offset_y));
    });
    module.method("hide!", [](void* widget){
        ((Widget*) widget)->hide();
    });
    module.method("show!", [](void* widget){
        ((Widget*) widget)->hide();
    });
    module.method("add_controller!", [](void* widget, void* controller){
        ((Widget*) widget)->add_controller(*((EventController*) controller));
    });
    module.method("remove_controller!", [](void* widget, void* controller){
        ((Widget*) widget)->remove_controller(*((EventController*) controller));
    });
    module.method("set_is_focusable!", [](void* widget, bool x){
        ((Widget*) widget)->set_is_focusable(x);
    });
    module.method("get_is_focusable", [](void* widget) -> bool {
        return ((Widget*) widget)->get_is_focusable();
    });
    module.method("grab_focus!", [](void* widget){
        ((Widget*) widget)->grab_focus();
    });
    module.method("get_has_focus", [](void* widget) -> bool {
        return ((Widget*) widget)->get_has_focus();
    });
    module.method("set_focus_on_click!", [](void* widget, bool x){
        ((Widget*) widget)->set_focus_on_click(x);
    });
    module.method("get_focus_on_click", [](void* widget) -> bool {
        return ((Widget*) widget)->get_focus_on_click();
    });
    module.method("get_is_realized", [](void* widget) -> bool {
        return ((Widget*) widget)->get_is_realized();
    });
    module.method("get_minimum_size", [](void* widget) -> jl_value_t* {
        return box_vector2f(((Widget*) widget)->get_minimum_size());
    });
    module.method("get_natural_size", [](void* widget) -> jl_value_t* {
        return box_vector2f(((Widget*) widget)->get_natural_size());
    });
    module.method("get_position", [](void* widget) -> jl_value_t* {
        return box_vector2f(((Widget*) widget)->get_position());
    });
    module.method("get_allocated_size", [](void* widget) -> jl_value_t* {
        return box_vector2f(((Widget*) widget)->get_allocated_size());
    });
    module.method("unparent!", [](void* widget){
        ((Widget*) widget)->unparent();
    });
    module.method("set_can_respond_to_input!", [](void* widget, bool x){
        ((Widget*) widget)->set_can_respond_to_input(x);
    });
    module.method("get_can_respond_to_input", [](void* widget) -> bool {
        return ((Widget*) widget)->get_can_respond_to_input();
    });
    module.method("get_clipboard", [](void* widget) -> void* {
        auto clipboard = ((Widget*) widget)->get_clipboard();
        g_object_ref(clipboard.get_internal());
        mousetrap::detail::attach_ref_to(((Widget*) widget)->get_internal(), clipboard.get_internal());
        return clipboard.get_internal();
    });
    module.method("set_hide_on_overflow!", [](void* widget, bool x){
        ((Widget*) widget)->set_hide_on_overflow(x);
    });
    module.method("get_hide_on_overflow", [](void* widget) -> bool {
        return ((Widget*) widget)->get_hide_on_overflow();
    });
    module.method("set_tick_callback!", [](void* widget, jl_value_t* task){
        ((Widget*) widget)->set_tick_callback([](FrameClock clock, jl_value_t* task){
            auto* res = jl_safe_call("Widget::tick_callback", task,jlcxx::box<FrameClock&>(clock));
            if (res != nullptr)
                return jlcxx::unbox<TickCallbackResult>(res);
            else
                return TickCallbackResult::DISCONTINUE;
        }, gc_protect(*((Widget*) widget), task));
    });
    module.method("remove_tick_callback!", [](void* widget) {
        ((Widget*) widget)->remove_tick_callback();
    });
    module.method("set_listens_for_shortcut_action!", [](void* widget, Action& action){
        ((Widget*) widget)->set_listens_for_shortcut_actions(action);
    });
    module.method("add_css_class!", [](void* widget, const std::string& str){
        ((Widget*) widget)->add_css_class(str);
    });
    module.method("remove_css_class!", [](void* widget, const std::string& str){
        ((Widget*) widget)->remove_css_class(str);
    });
    module.method("get_css_classes", [](void* widget) -> std::vector<std::string> {
        return ((Widget*) widget)->get_css_classes();
    });
    module.method("calculate_monitor_dpi", [](void* widget){
        auto* display = gtk_widget_get_display(((Widget*) widget)->operator NativeWidget());
        auto* monitors = gdk_display_get_monitors(display);
        GdkMonitor* monitor = GDK_MONITOR(g_list_model_get_item(monitors, 0));
        auto* geometry = new GdkRectangle();
        gdk_monitor_get_geometry(monitor, geometry);
        float wdpi = geometry->width / (gdk_monitor_get_width_mm(monitor) / 25.4);
        float hdpi = geometry->height / (gdk_monitor_get_height_mm(monitor) / 25.4);
        delete geometry;
        return std::min(wdpi, hdpi);
    });
    module.method("calculate_scale_factor", [](void* widget){
       return ((Widget*) widget)->get_scale_factor();
    });
}
