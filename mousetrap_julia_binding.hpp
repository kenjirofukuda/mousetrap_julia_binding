//
// Created by clem on 4/16/23.
//

#include <julia.h>
#include <mousetrap.hpp>
#include <jlcxx/jlcxx.hpp>

using namespace mousetrap;

static inline jl_value_t* jl_box_string(const std::string& in)
{
    static auto* string = jl_get_global(jl_base_module, jl_symbol("string"));
    return jl_call1(string, (jl_value_t*) jl_symbol(in.c_str()));
}

static void jl_println(jl_value_t* value)
{
    static auto* println = jl_get_function(jl_base_module, "println");
    jl_call1(println, value);
}

template<typename... T>
static inline jl_value_t* jl_calln(jl_function_t* function, T... args)
{
    std::array<jl_value_t*, sizeof...(T)> wrapped = {args...};
    return jl_call(function, wrapped.data(), wrapped.size());
}

template<typename... T>
static inline jl_value_t* jl_safe_call(const char* scope, jl_function_t* function, T... args)
{
    static auto* safe_call = jl_eval_string("return mousetrap.safe_call");
    std::array<jl_value_t*, sizeof...(T)+2> wrapped = {jl_box_string(scope), function, args...};
    return jl_call(safe_call, wrapped.data(), wrapped.size());
}

static inline jl_value_t* jl_get_property(jl_value_t* object, const char* property_name)
{
    static auto* get_property = jl_get_function(jl_base_module, "getproperty");
    return jl_call2(get_property, object, (jl_value_t*) jl_symbol(property_name));
}

template<typename... Ts>
static inline jl_value_t* jl_wrap(Ts... args)
{
    auto* wrap = jl_eval_string("(args...) -> args");
    return jl_calln(wrap, args...);
}

static jl_value_t* box_vector2f(Vector2f in)
{
    static auto* ctor = jl_eval_string("mousetrap.Vector2f");
    return jl_calln(ctor, jl_box_float32(in.x), jl_box_float32(in.y));
}

static Vector2f unbox_vector2f(jl_value_t* in)
{
    return Vector2f {
    jl_unbox_float32(jl_get_property(in, "x")),
    jl_unbox_float32(jl_get_property(in, "y"))
    };
}

static jl_value_t* box_vector2i(Vector2i in)
{
    static auto* ctor = jl_eval_string("mousetrap.Vector2i");
    return jl_calln(ctor, jl_box_int64(in.x), jl_box_int64(in.y));
}

static Vector2f unbox_vector2i(jl_value_t* in)
{
    return Vector2i {
    jl_unbox_int64(jl_get_property(in, "x")),
    jl_unbox_int64(jl_get_property(in, "y"))
    };
}

static jl_value_t* box_vector3f(Vector3f in)
{
    static auto* ctor = jl_eval_string("mousetrap.Vector3f");
    return jl_calln(ctor, jl_box_float32(in.x), jl_box_float32(in.y), jl_box_float32(in.z));
}

static Vector3f unbox_vector3f(jl_value_t* in)
{
    return Vector3f {
    jl_unbox_float32(jl_get_property(in, "x")),
    jl_unbox_float32(jl_get_property(in, "y")),
    jl_unbox_float32(jl_get_property(in, "z"))
    };
}

static jl_value_t* box_vector4f(Vector4f in)
{
    static auto* ctor = jl_eval_string("mousetrap.Vector4f");
    return jl_calln(ctor,
                    jl_box_float32(in.x),
                    jl_box_float32(in.y),
                    jl_box_float32(in.z),
                    jl_box_float32(in.z)
    );
}

static Vector4f unbox_vector4f(jl_value_t* in)
{
    return Vector4f {
    jl_unbox_float32(jl_get_property(in, "x")),
    jl_unbox_float32(jl_get_property(in, "y")),
    jl_unbox_float32(jl_get_property(in, "z")),
    jl_unbox_float32(jl_get_property(in, "w"))
    };
}

static jl_value_t* box_rgba(RGBA in)
{
    static auto* ctor = jl_eval_string("return mousetrap.RGBA");
    return jl_calln(
    ctor,
    jl_box_float32(in.r),
    jl_box_float32(in.g),
    jl_box_float32(in.b),
    jl_box_float32(in.a)
    );
}

static RGBA unbox_rgba(jl_value_t* in)
{
    return RGBA {
    jl_unbox_float32(jl_get_property(in, "r")),
    jl_unbox_float32(jl_get_property(in, "g")),
    jl_unbox_float32(jl_get_property(in, "b")),
    jl_unbox_float32(jl_get_property(in, "a"))
    };
}

static jl_value_t* box_hsva(HSVA in)
{
    static auto* ctor = jl_eval_string("return mousetrap.RGBA");
    return jl_calln(
    ctor,
    jl_box_float32(in.h),
    jl_box_float32(in.s),
    jl_box_float32(in.v),
    jl_box_float32(in.a)
    );
}

static HSVA unbox_hsva(jl_value_t* in)
{
    return HSVA {
    jl_unbox_float32(jl_get_property(in, "h")),
    jl_unbox_float32(jl_get_property(in, "s")),
    jl_unbox_float32(jl_get_property(in, "v")),
    jl_unbox_float32(jl_get_property(in, "a"))
    };
}

#define USE_FINALIZERS true

#define declare_is_subtype_of(A, B) template<> struct jlcxx::SuperType<A> { typedef B type; };
#define make_not_mirrored(Name) template<> struct jlcxx::IsMirroredType<Name> : std::false_type {};

#define add_type(Type) add_type<Type>(std::string("_") + #Type)
#define add_type_method(Type, id, ...) method(#id + std::string(#__VA_ARGS__), &Type::id)
#define add_constructor(...) constructor<__VA_ARGS__>(USE_FINALIZERS)

#define define_enum_in(module, Enum) \
    module.add_bits<Enum>(std::string("_") + #Enum, jl_int64_type); \
    module.method(std::string(#Enum) + "_to_int", [](Enum x) -> int64_t { return (int64_t) x; });

#define add_enum_value(Enum, PREFIX, VALUE) set_const(std::string(#PREFIX) + "_" + std::string(#VALUE), Enum::VALUE)

#define _DEFINE_ADD_SIGNAL_INVARIANT(snake_case) \
    method("disconnect_signal_" + std::string(#snake_case) + "!", [](T& instance) { \
        instance.disconnect_signal_##snake_case(); \
    }) \
    .method("set_signal_" + std::string(#snake_case) + "_blocked!", [](T& instance, bool b){ \
        instance.set_signal_##snake_case##_blocked(b); \
    }) \
    .method("get_signal_" + std::string(#snake_case) + "_blocked", [](T& instance) -> bool { \
        return instance.get_signal_##snake_case##_blocked(); \
    });

#define DEFINE_ADD_SIGNAL_ARG0(snake_case, return_t) \
template<typename T, typename Arg_t> \
void add_signal_##snake_case(Arg_t type, const std::string& name) \
{ \
    type.method("connect_signal_" + std::string(#snake_case) + "!", [name](T& instance, jl_function_t* task) \
    { \
        instance.connect_signal_##snake_case([name](T& instance, jl_function_t* task) -> return_t { \
            return jlcxx::unbox<return_t>( \
                jl_safe_call( \
                    (name + "::emit_signal_" + std::string(#snake_case)).c_str(), \
                    task,                                   \
                    jl_wrap(jlcxx::box<T&>(instance))\
                ) \
            ); \
        }, task); \
    }) \
    .method("emit_signal_" + std::string(#snake_case), [](T& instance) -> return_t { \
        return instance.emit_signal_##snake_case(); \
    }); \
    type._DEFINE_ADD_SIGNAL_INVARIANT(snake_case)      \
}

#define DEFINE_ADD_SIGNAL_ARG1(snake_case, return_t, arg1_t, arg1_name) \
template<typename T, typename Arg_t> \
void add_signal_##snake_case(Arg_t type, const std::string& name) \
{ \
    type.method("connect_signal_" + std::string(#snake_case) + "!", [name](T& instance, jl_function_t* task) \
    { \
        instance.connect_signal_##snake_case([name](T& instance, arg1_t arg1_name, jl_function_t* task) -> return_t { \
            return jlcxx::unbox<return_t>( \
                jl_safe_call( \
                    (name + "::emit_signal_" + std::string(#snake_case)).c_str(), \
                    task, \
                    jl_wrap(jlcxx::box<T&>(instance), jlcxx::box<arg1_t>(arg1_name)) \
                ) \
            ); \
        }, task); \
    }) \
    .method("emit_signal_" + std::string(#snake_case), [](T& instance, arg1_t arg1_name) -> return_t { \
        return instance.emit_signal_##snake_case(arg1_name); \
    }); \
    type._DEFINE_ADD_SIGNAL_INVARIANT(snake_case)      \
}

#define DEFINE_ADD_SIGNAL_ARG2(snake_case, return_t, arg1_t, arg1_name, arg2_t, arg2_name) \
template<typename T, typename Arg_t> \
void add_signal_##snake_case(Arg_t type, const std::string& name) \
{ \
    type.method("connect_signal_" + std::string(#snake_case) + "!", [name](T& instance, jl_function_t* task) \
    { \
        instance.connect_signal_##snake_case([name](T& instance, arg1_t arg1_name, arg2_t arg2_name, jl_function_t* task) -> return_t { \
            return jlcxx::unbox<return_t>( \
                jl_safe_call( \
                    (name + "::emit_signal_" + std::string(#snake_case)).c_str(), \
                    task, \
                    jl_wrap(jlcxx::box<T&>(instance), jlcxx::box<arg1_t>(arg1_name), jlcxx::box<arg2_t>(arg2_name)) \
                ) \
            ); \
        }, task); \
    }) \
    .method("emit_signal_" + std::string(#snake_case), [](T& instance, arg1_t arg1_name, arg2_t arg2_name) -> return_t { \
        return instance.emit_signal_##snake_case(arg1_name, arg2_name); \
    }); \
    type._DEFINE_ADD_SIGNAL_INVARIANT(snake_case)      \
}

#define DEFINE_ADD_SIGNAL_ARG3(snake_case, return_t, arg1_t, arg1_name, arg2_t, arg2_name, arg3_t, arg3_name) \
template<typename T, typename Arg_t> \
void add_signal_##snake_case(Arg_t type, const std::string& name) \
{ \
    type.method("connect_signal_" + std::string(#snake_case) + "!", [name](T& instance, jl_function_t* task) \
    { \
        instance.connect_signal_##snake_case([name](T& instance, arg1_t arg1_name, arg2_t arg2_name, arg3_t arg3_name, jl_function_t* task) -> return_t { \
            return jlcxx::unbox<return_t>( \
                jl_safe_call( \
                    (name + "::emit_signal_" + std::string(#snake_case)).c_str(), \
                    task, \
                    jl_wrap(jlcxx::box<T&>(instance), jlcxx::box<arg1_t>(arg1_name), jlcxx::box<arg2_t>(arg2_name), jlcxx::box<arg3_t>(arg3_name)) \
                ) \
            ); \
        }, task); \
    }) \
    .method("emit_signal_" + std::string(#snake_case), [](T& instance, arg1_t arg1_name, arg2_t arg2_name, arg3_t arg3_name) -> return_t { \
        return instance.emit_signal_##snake_case(arg1_name, arg2_name, arg3_name); \
    }); \
    type._DEFINE_ADD_SIGNAL_INVARIANT(snake_case)      \
}

#define DEFINE_ADD_SIGNAL_ARG4(snake_case, return_t, arg1_t, arg1_name, arg2_t, arg2_name, arg3_t, arg3_name, arg4_t, arg4_name) \
template<typename T, typename Arg_t> \
void add_signal_##snake_case(Arg_t type, const std::string& name) \
{ \
    type.method("connect_signal_" + std::string(#snake_case) + "!", [name](T& instance, jl_function_t* task) \
    { \
        instance.connect_signal_##snake_case([name](T& instance, arg1_t arg1_name, arg2_t arg2_name, arg3_t arg3_name, arg4_t arg4_name, jl_function_t* task) -> return_t { \
            return jlcxx::unbox<return_t>( \
                jl_safe_call( \
                    (name + "::emit_signal_" + std::string(#snake_case)).c_str(), \
                    task, \
                    jl_wrap(jlcxx::box<T&>(instance), jlcxx::box<arg1_t>(arg1_name), jlcxx::box<arg2_t>(arg2_name), jlcxx::box<arg3_t>(arg3_name), jlcxx::box<arg4_t>(arg4_name)) \
                ) \
            ); \
        }, task); \
    }) \
    .method("emit_signal_" + std::string(#snake_case), [](T& instance, arg1_t arg1_name, arg2_t arg2_name, arg3_t arg3_name, arg4_t arg4_name) -> return_t { \
        return instance.emit_signal_##snake_case(arg1_name, arg2_name, arg3_name, arg4_name); \
    }); \
    type._DEFINE_ADD_SIGNAL_INVARIANT(snake_case)      \
}

#define DEFINE_ADD_WIDGET_SIGNAL(snake_case) \
template<typename T, typename Arg_t>                               \
void add_signal_##snake_case(Arg_t type, const std::string& name) {\
    type.method("connect_signal_" + std::string(#snake_case) + "!", [name](T& instance, jl_function_t* task) \
    { \
        instance.connect_signal_##snake_case([name](Widget& instance, jl_function_t* task) -> void { \
            jl_safe_call((name + "::emit_signal_" + std::string(#snake_case)).c_str(), task, jlcxx::box<T&>(dynamic_cast<T&>(instance))); \
        }, task); \
    }) \
    .method("emit_signal_" + std::string(#snake_case), [](T& instance) { \
        instance.emit_signal_##snake_case(); \
    }); \
    type._DEFINE_ADD_SIGNAL_INVARIANT(snake_case); \
}

DEFINE_ADD_WIDGET_SIGNAL(realize)
DEFINE_ADD_WIDGET_SIGNAL(unrealize)
DEFINE_ADD_WIDGET_SIGNAL(destroy)
DEFINE_ADD_WIDGET_SIGNAL(hide)
DEFINE_ADD_WIDGET_SIGNAL(show)
DEFINE_ADD_WIDGET_SIGNAL(map)
DEFINE_ADD_WIDGET_SIGNAL(unmap)

template<typename T, typename Arg_t>
void add_widget_signals(Arg_t& type, const std::string& name)
{
    add_signal_realize<T>(type, name);
    add_signal_unrealize<T>(type, name);
    add_signal_destroy<T>(type, name);
    add_signal_hide<T>(type, name);
    add_signal_show<T>(type, name);
    add_signal_map<T>(type, name);
    add_signal_unmap<T>(type, name);
}

DEFINE_ADD_SIGNAL_ARG0(activate, void)
DEFINE_ADD_SIGNAL_ARG0(startup, void)
DEFINE_ADD_SIGNAL_ARG0(shutdown, void)
DEFINE_ADD_SIGNAL_ARG0(update, void)
DEFINE_ADD_SIGNAL_ARG0(paint, void)
DEFINE_ADD_SIGNAL_ARG0(close_request, WindowCloseRequestResult)
DEFINE_ADD_SIGNAL_ARG0(activate_default_widget, void)
DEFINE_ADD_SIGNAL_ARG0(activate_focused_widget, void)
DEFINE_ADD_SIGNAL_ARG0(clicked, void)
DEFINE_ADD_SIGNAL_ARG0(toggled, void)
DEFINE_ADD_SIGNAL_ARG0(text_changed, void)
DEFINE_ADD_SIGNAL_ARG0(undo, void)
DEFINE_ADD_SIGNAL_ARG0(redo, void)
DEFINE_ADD_SIGNAL_ARG2(selection_changed, void, gint, position, gint, n_items)
DEFINE_ADD_SIGNAL_ARG3(key_pressed, bool, guint, keyval, guint, keycode, ModifierState, modifier)
DEFINE_ADD_SIGNAL_ARG3(key_released, void, guint, keyval, guint, keycode, ModifierState, modifier)
DEFINE_ADD_SIGNAL_ARG3(modifiers_changed, bool, guint, keyval, guint, keycode, ModifierState, modifier)
DEFINE_ADD_SIGNAL_ARG2(motion_enter, void, double, x, double, y)
DEFINE_ADD_SIGNAL_ARG2(motion, void, double, x, double, y)
DEFINE_ADD_SIGNAL_ARG0(motion_leave, void)
DEFINE_ADD_SIGNAL_ARG3(click_pressed, void, gint, n_press, double, x, double, y)
DEFINE_ADD_SIGNAL_ARG3(click_released, void, gint, n_press, double, x, double, y)
DEFINE_ADD_SIGNAL_ARG0(click_stopped, void)
DEFINE_ADD_SIGNAL_ARG2(kinetic_scroll_decelerate, void, double, x_velocity, double, y_velocity)
DEFINE_ADD_SIGNAL_ARG0(scroll_begin, void)
DEFINE_ADD_SIGNAL_ARG2(scroll, bool, double, delta_x, double, delta_y)
DEFINE_ADD_SIGNAL_ARG0(scroll_end, void)
DEFINE_ADD_SIGNAL_ARG0(focus_gained, void)
DEFINE_ADD_SIGNAL_ARG0(focus_lost, void)
DEFINE_ADD_SIGNAL_ARG2(drag_begin, void, double, start_x, double, start_y)
DEFINE_ADD_SIGNAL_ARG2(drag, void, double, offset_x, double, offset_y)
DEFINE_ADD_SIGNAL_ARG2(drag_end, void, double, offset_x, double, offset_y)
DEFINE_ADD_SIGNAL_ARG1(scale_changed, void, double, scale)
DEFINE_ADD_SIGNAL_ARG2(rotation_changed, void, double, angle_absolute_radians, double, angle_delta_radians)
DEFINE_ADD_SIGNAL_ARG0(properties_changed, void)
DEFINE_ADD_SIGNAL_ARG0(value_changed, void)
DEFINE_ADD_SIGNAL_ARG2(resize, void, gint, width, gint, height)
DEFINE_ADD_SIGNAL_ARG2(page_added, void, void*, _, guint, page_index)
DEFINE_ADD_SIGNAL_ARG2(page_removed, void, void*, _, guint, page_index)
DEFINE_ADD_SIGNAL_ARG2(page_reordered, void, void*, _, guint, page_index)
DEFINE_ADD_SIGNAL_ARG2(page_selection_changed, void, void*, _, guint, page_index)
DEFINE_ADD_SIGNAL_ARG0(wrapped, void)
DEFINE_ADD_SIGNAL_ARG2(pressed, void, double, x, double, y)
DEFINE_ADD_SIGNAL_ARG0(press_cancelled, void)
DEFINE_ADD_SIGNAL_ARG2(pan, void, PanDirection, direction, double, offset)
DEFINE_ADD_SIGNAL_ARG2(swipe, void, double, x_velocity, double, y_velocity)
DEFINE_ADD_SIGNAL_ARG2(stylus_down, void, double, x, double, y)
DEFINE_ADD_SIGNAL_ARG2(stylus_up, void, double, x, double, y)
DEFINE_ADD_SIGNAL_ARG2(proximity, void, double, x, double, y)
DEFINE_ADD_SIGNAL_ARG2(scroll_child, void, ScrollType, scroll_type, bool, is_horizontal)
DEFINE_ADD_SIGNAL_ARG0(closed, void)
DEFINE_ADD_SIGNAL_ARG0(play, void)
DEFINE_ADD_SIGNAL_ARG0(stop, void)
DEFINE_ADD_SIGNAL_ARG3(items_changed, void, gint, position, gint, n_removed, gint, n_added)
DEFINE_ADD_SIGNAL_ARG1(revealed, void, void*, _)
DEFINE_ADD_SIGNAL_ARG1(activated, void, void*, _)

template<typename T, typename Arg_t>
void add_signal_render(Arg_t type, const std::string& name)
{
    type.method("connect_signal_render!", [name](T& instance, jl_function_t* task)
    {
        instance.connect_signal_render([name](T& instance, GdkGLContext* context, jl_function_t* task) -> bool {
            return jlcxx::unbox<bool>(
            jl_safe_call(
            (name + "::emit_signal_render").c_str(),
            task,
            jl_wrap(jlcxx::box<T&>(instance), jlcxx::box<void*>((void*) context))
            )
            );
        }, task);
    })
    .method("emit_signal_render", [](T& instance) {
        instance.emit_signal_render((GdkGLContext*) nullptr);
    });
    type._DEFINE_ADD_SIGNAL_INVARIANT(render)
}

static void implement_adjustment(jlcxx::Module& module);

static void implement_action(jlcxx::Module& module);

static void implement_alignment(jlcxx::Module& module);

static void implement_application(jlcxx::Module& module);

static void implement_aspect_frame(jlcxx::Module& module);

static void implement_blend_mode(jlcxx::Module& module);

static void implement_box(jlcxx::Module& module);

static void implement_button(jlcxx::Module& module);

static void implement_center_box(jlcxx::Module& module);

static void implement_check_button(jlcxx::Module& module);

static void implement_click_event_controller(jlcxx::Module& module);

static void implement_clipboard(jlcxx::Module& module);

static void implement_color(jlcxx::Module& module);

static void implement_column_view(jlcxx::Module& module);

static void implement_cursor_type(jlcxx::Module& module);

static void implement_drag_event_controller(jlcxx::Module& module);

static void implement_drop_down(jlcxx::Module& module);

static void implement_entry(jlcxx::Module& module);

static void implement_event_controller(jlcxx::Module& module);

static void implement_expander(jlcxx::Module& module);

static void implement_file_monitor(jlcxx::Module& module);

static void implement_file_descriptor(jlcxx::Module& module);

static void implement_file_system(jlcxx::Module& module);

static void implement_file_chooser(jlcxx::Module& module);

static void implement_fixed(jlcxx::Module& module);

static void implement_focus_event_controller(jlcxx::Module& module);

static void implement_frame(jlcxx::Module& module);

static void implement_frame_clock(jlcxx::Module& module);

static void implement_gl_transform(jlcxx::Module& module);

static void implement_grid(jlcxx::Module& module);

static void implement_grid_view(jlcxx::Module& module);

static void implement_header_bar(jlcxx::Module& module);

static void implement_icon(jlcxx::Module& module);

static void implement_image(jlcxx::Module& module);

static void implement_image_display(jlcxx::Module& module);

static void implement_justify_mode(jlcxx::Module& module);

static void implement_key_codes(jlcxx::Module& module);

static void implement_key_event_controller(jlcxx::Module& module);

static void implement_key_file(jlcxx::Module& module);

static void implement_label(jlcxx::Module& module);

static void implement_level_bar(jlcxx::Module& module);

static void implement_list_view(jlcxx::Module& module);

static void implement_log(jlcxx::Module& module);

static void implement_long_press_event_controller(jlcxx::Module& module);

static void implement_menu_model(jlcxx::Module& module);

static void implement_menu_bar(jlcxx::Module& module);

static void implement_motion_event_controller(jlcxx::Module& module);

static void implement_music(jlcxx::Module& module);

static void implement_notebook(jlcxx::Module& module);

static void implement_orientation(jlcxx::Module& module);

static void implement_overlay(jlcxx::Module& module);

static void implement_pan_event_controller(jlcxx::Module& module);

static void implement_paned(jlcxx::Module& module);

static void implement_pinch_zoom_event_controller(jlcxx::Module& module);

static void implement_popover(jlcxx::Module& module);

static void implement_popover_button(jlcxx::Module& module);

static void implement_popover_menu(jlcxx::Module& module);

static void implement_progress_bar(jlcxx::Module& module);

static void implement_relative_position(jlcxx::Module& module);

static void implement_render_area(jlcxx::Module& module);

static void implement_render_task(jlcxx::Module& module);

static void implement_revealer(jlcxx::Module& module);

static void implement_rotate_event_controller(jlcxx::Module& module);

static void implement_scale(jlcxx::Module& module);

static void implement_scroll_event_controller(jlcxx::Module& module);

static void implement_scrollbar(jlcxx::Module& module);

static void implement_selection_model(jlcxx::Module& module);

static void implement_separator(jlcxx::Module& module);

static void implement_shader(jlcxx::Module& module);

static void implement_shape(jlcxx::Module& module);

static void implement_shortcut_event_controller(jlcxx::Module& module);

static void implement_sound(jlcxx::Module& module);

static void implement_sound_buffer(jlcxx::Module& module);

static void implement_spin_button(jlcxx::Module& module);

static void implement_spinner(jlcxx::Module& module);

static void implement_stack(jlcxx::Module& module);

static void implement_stylus_event_controller(jlcxx::Module& module);

static void implement_swipe_event_controller(jlcxx::Module& module);

static void implement_switch(jlcxx::Module& module);

static void implement_text_view(jlcxx::Module& module);

static void implement_time(jlcxx::Module& module);

static void implement_texture(jlcxx::Module& module);

static void implement_toggle_button(jlcxx::Module& module);

static void implement_viewport(jlcxx::Module& module);

static void implement_widget(jlcxx::Module& module);

static void implement_window(jlcxx::Module& module);

JLCXX_MODULE define_julia_module(jlcxx::Module& module)
{
    module.set_const("GTK_MAJOR_VERSION", (int) GTK_MAJOR_VERSION);
    module.set_const("GTK_MINOR_VERSION", (int) GTK_MINOR_VERSION);

    implement_orientation(module);
    implement_time(module);

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
    implement_sound(module);
    implement_sound_buffer(module);
    implement_music(module);

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
}

