#include "../mousetrap_julia_binding.hpp"

// ### SPIN BUTTON

static void implement_spin_button(jlcxx::Module& module)
{
    auto spin = module.add_type(SpinButton)
    .add_constructor(float, float, float, Orientation)
    .method("get_adjustment", [](SpinButton& self) -> void* {
        return self.get_adjustment()->get_internal();
    })
    .add_type_method(SpinButton, get_lower)
    .add_type_method(SpinButton, get_upper)
    .add_type_method(SpinButton, get_value)
    .add_type_method(SpinButton, get_increment)
    .add_type_method(SpinButton, set_lower, !)
    .add_type_method(SpinButton, set_upper, !)
    .add_type_method(SpinButton, set_value, !)
    .add_type_method(SpinButton, set_increment, !)
    .add_type_method(SpinButton, set_n_digits, !)
    .add_type_method(SpinButton, get_n_digits)
    .add_type_method(SpinButton, set_should_wrap, !)
    .add_type_method(SpinButton, get_should_wrap)
    .add_type_method(SpinButton, set_acceleration_rate, !)
    .add_type_method(SpinButton, get_acceleration_rate)
    .add_type_method(SpinButton, set_should_snap_to_ticks, !)
    .add_type_method(SpinButton, get_should_snap_to_ticks)
    .add_type_method(SpinButton, set_allow_only_numeric, !)
    .add_type_method(SpinButton, get_allow_only_numeric)
    .method("set_text_to_value_function!", [](SpinButton& button, jl_value_t* task) {
        button.set_text_to_value_function([](const SpinButton& button, const std::string& text, jl_value_t* task) -> float {
            auto* res = jl_safe_call("SpinButton::text_to_value", task, jlcxx::box<const SpinButton&>(button), jl_box_string(text));
            if (res != nullptr)
                return jl_unbox_float32(res);
            else
                return button.get_value();
        }, task);
    })
    .add_type_method(SpinButton, reset_text_to_value_function, !)
    .method("set_value_to_text_function!", [](SpinButton& button, jl_value_t* task) {
        button.set_value_to_text_function([](const SpinButton& button, float value, jl_value_t* task) -> std::string {
            auto* res = jl_safe_call("SpinButton::text_to_value", task, jlcxx::box<const SpinButton&>(button), jl_box_float32(value));
            if (res != nullptr)
            {
                auto* str = jl_string_ptr(res);
                if (str != nullptr)
                    return std::string(str);
            }
            return std::string();
        }, task);
    })
    .add_type_method(SpinButton, reset_value_to_text_function)
    ;

    add_widget_signals<SpinButton>(spin, "SpinButton");
    add_signal_value_changed<SpinButton>(spin, "SpinButton");
    add_signal_wrapped<SpinButton>(spin, "SpinButton");
}