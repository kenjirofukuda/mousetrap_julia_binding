#include "../mousetrap_julia_binding.hpp"

namespace mousetrap::detail
{
    struct _GCSentinel
    {
        GObject parent;
        jl_value_t* target;
    };
    using GCSentinel = _GCSentinel;

    DECLARE_NEW_TYPE(GCSentinel, gc_sentinel, GC_SENTINEL)
    DEFINE_NEW_TYPE_TRIVIAL_INIT(GCSentinel, gc_sentinel, GC_SENTINEL)

    static void gc_sentinel_finalize(GObject* object)
    {
        auto* self = MOUSETRAP_GC_SENTINEL(object);
        G_OBJECT_CLASS(gc_sentinel_parent_class)->finalize(object);

        std::cout << "gc unprotected: " << self->target << std::endl;
        jlcxx::unprotect_from_gc(self->target);
    }

    DEFINE_NEW_TYPE_TRIVIAL_CLASS_INIT(GCSentinel, gc_sentinel, GC_SENTINEL)

    static GCSentinel* gc_sentinel_new(jl_value_t* native)
    {
        auto* self = (GCSentinel*) g_object_new(gc_sentinel_get_type(), nullptr);
        gc_sentinel_init(self);

        self->target = native;
        std::cout << "gc protecting: " << self->target << std::endl;
        jlcxx::protect_from_gc(self->target);
        return self;
    }
}

JLCXX_MODULE define_julia_module(jlcxx::Module& module)
{
    module.set_const("GTK_MAJOR_VERSION", (int) GTK_MAJOR_VERSION);
    module.set_const("GTK_MINOR_VERSION", (int) GTK_MINOR_VERSION);
    module.set_const("MOUSETRAP_ENABLE_OPENGL_COMPONENT", (bool) MOUSETRAP_ENABLE_OPENGL_COMPONENT);

    implement_orientation(module);
    implement_time(module);
    implement_theme(module);

    implement_adjustment(module);
    implement_action(module);
    implement_alignment(module);
    implement_application(module);
    implement_window(module);

    implement_file_monitor(module);
    implement_file_descriptor(module);
    implement_file_system(module);

    implement_event_controller(module);
    implement_drag_event_controller(module);
    implement_click_event_controller(module);
    implement_focus_event_controller(module);
    implement_key_event_controller(module);
    implement_long_press_event_controller(module);
    implement_motion_event_controller(module);
    implement_pinch_zoom_event_controller(module);
    implement_rotate_event_controller(module);
    implement_scroll_event_controller(module);
    implement_shortcut_event_controller(module);
    implement_stylus_event_controller(module);
    implement_swipe_event_controller(module);
    implement_pan_event_controller(module);

    implement_color(module);
    implement_icon(module);
    implement_image(module);
    implement_cursor_type(module);

    implement_relative_position(module);
    implement_menu_model(module);
    implement_menu_bar(module);
    implement_popover_menu(module);
    implement_popover(module);
    implement_popover_button(module);
    implement_progress_bar(module);

    implement_aspect_frame(module);
    implement_clamp_frame(module);
    implement_blend_mode(module);
    implement_box(module);
    implement_button(module);
    implement_center_box(module);
    implement_check_button(module);
    implement_clipboard(module);

    implement_selection_model(module);
    implement_list_view(module);
    implement_grid_view(module);
    implement_column_view(module);
    implement_grid(module);

    implement_image_display(module);
    implement_drop_down(module);
    implement_entry(module);
    implement_expander(module);
    implement_file_chooser(module);
    implement_alert_dialog(module);
    implement_color_chooser(module);

    implement_fixed(module);
    implement_frame(module);
    implement_frame_clock(module);

    implement_header_bar(module);
    implement_key_file(module);

    implement_justify_mode(module);
    implement_label(module);
    implement_text_view(module);

    implement_level_bar(module);
    implement_log(module);

    implement_notebook(module);
    implement_overlay(module);
    implement_paned(module);

    implement_revealer(module);
    implement_scale(module);
    implement_scrollbar(module);
    implement_separator(module);
    implement_spin_button(module);
    implement_spinner(module);
    implement_switch(module);
    implement_toggle_button(module);

    //implement_sound(module);
    //implement_sound_buffer(module);
    //implement_music(module);

    implement_stack(module);
    implement_viewport(module);

    implement_widget(module);

    implement_gl_transform(module);
    implement_texture(module);
    implement_shader(module);
    implement_shape(module);
    implement_render_task(module);
    implement_render_area(module);

    implement_key_codes(module);

    module.method("_ref", [](void* ptr){
        return (void*) g_object_ref(G_OBJECT(ptr));
    });

    module.method("_unref", [](void* ptr){
        g_object_unref(G_OBJECT(ptr));
    });

    module.method("initialize", [](){
       adw_init();
       detail::mark_gtk_initialized();
       detail::initialize_opengl();
    });

    mousetrap::detail::notify_if_gtk_uninitialized::message = R"(
    Attempting to construct a widget, but the GTK4 backend has not yet been initialized.

    A typical `.jl` file using mousetrap should look like this:
    ```julia
    using mousetrap
    main() do app::Application
        # all construction of widgets should happen here
    end
    ```
    You have most likely attempted to construct a widget outside of `main` while using mousetrap interactively.
    )";

    #if MOUSETRAP_ENABLE_OPENGL_COMPONENT

    mousetrap::detail::notify_if_gl_uninitialized::message = R"(
    Attempting to interact with the global OpenGL context, but it has not yet been initialized.

    A typical `.jl` file using mousetrap should look like this:
    ```julia
    using mousetrap
    main() do app::Application
        # all OpenGL-related activity should happen here
    end
    ```
    You have most likely attempted to construct an OpenGL-related object outside of `main` while using mousetrap interactively.
    )";

    #endif
}