//
// Created by clem on 8/26/23.
//

#include "../mousetrap_julia_binding.hpp"

void implement_animation(jlcxx::Module& module)
{
    define_enum_in(module, Animation::State);
    module.add_enum_value(Animation::State, ANIMATION_STATE, IDLE);
    module.add_enum_value(Animation::State, ANIMATION_STATE, PAUSED);
    module.add_enum_value(Animation::State, ANIMATION_STATE, PLAYING);
    module.add_enum_value(Animation::State, ANIMATION_STATE, DONE);

    define_enum_in(module, Animation::TimingFunction);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, LINEAR);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, EXPONENTIAL);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, EXPONENTIAL_REVERSE);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, EXPONENTIAL_SIGMOID);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, SINE);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, SINE_REVERSE);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, SINE_SIGMOID);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, CIRCULAR);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, CIRCULAR_REVERSE);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, CIRCULAR_SIGMOID);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, OVERSHOOT);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, OVERSHOOT_REVERSE);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, OVERSHOOT_SIGMOID);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, ELASTIC);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, ELASTIC_REVERSE);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, ELASTIC_SIGMOID);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, BOUNCE);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, BOUNCE_REVERSE);
    module.add_enum_value(Animation::TimingFunction, ANIMATION_TIMING_FUNCTION, BOUNCE_SIGMOID);

    auto animation = module.add_type(Animation)
        .constructor([](void* widget, float time_mys){
            return new Animation(*((Widget*) widget), microseconds(time_mys));
        })
        .add_type_method(Animation, get_state)
        .add_type_method(Animation, play, !)
        .add_type_method(Animation, pause, !)
        .add_type_method(Animation, reset, !)
        .method("set_duration!", [](Animation& self, float time_mys){
            self.set_duration(microseconds(time_mys));
        })
        .method("get_duration", [](Animation& self){
            return self.get_duration().as_microseconds();
        })
        .add_type_method(Animation, set_lower, !)
        .add_type_method(Animation, get_lower)
        .add_type_method(Animation, set_upper, !)
        .add_type_method(Animation, get_upper)
        .add_type_method(Animation, get_value)
        .add_type_method(Animation, set_repeat_count, !)
        .add_type_method(Animation, get_repeat_count)
        .add_type_method(Animation, set_is_reversed, !)
        .add_type_method(Animation, get_is_reversed)
        .add_type_method(Animation, set_timing_function, !)
        .add_type_method(Animation, get_timing_function)
        .method("on_tick!", [](Animation& self, jl_value_t* task){
            self.on_tick([](Animation& self, double value, jl_value_t* task){
                jl_safe_call("Animation::on_tick!", task,
                     jlcxx::box<Animation&>(self),
                     jl_box_float64(value)
                );
            }, gc_protect(self, task));
        })
        .method("on_done!", [](Animation& self, jl_value_t* task){
            self.on_done([](Animation& self, jl_value_t* task){
                jl_safe_call("Animation::on_done!", task,
                             jlcxx::box<Animation&>(self)
                 );
            }, gc_protect(self, task));
        })
   ;
}