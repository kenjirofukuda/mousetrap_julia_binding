//
// Created by clem on 8/26/23.
//

#include "../mousetrap_julia_binding.hpp"

enum class AnimationState
{
    IDLE = Animation::State::IDLE,
    PAUSED = Animation::State::PAUSED,
    PLAYING = Animation::State::PLAYING,
    DONE = Animation::State::DONE,
};

enum class AnimationTimingFunction
{
    LINEAR = Animation::TimingFunction::LINEAR,
    EXPONENTIAL = Animation::TimingFunction::EXPONENTIAL,
    EXPONENTIAL_REVERSE = Animation::TimingFunction::EXPONENTIAL_REVERSE,
    EXPONENTIAL_SIGMOID = Animation::TimingFunction::EXPONENTIAL_SIGMOID,
    SINE = Animation::TimingFunction::SINE,
    SINE_REVERSE = Animation::TimingFunction::SINE_REVERSE,
    SINE_SIGMOID = Animation::TimingFunction::SINE_SIGMOID,
    CIRCULAR = Animation::TimingFunction::CIRCULAR,
    CIRCULAR_REVERSE = Animation::TimingFunction::CIRCULAR_REVERSE,
    CIRCULAR_SIGMOID = Animation::TimingFunction::CIRCULAR_SIGMOID,
    OVERSHOOT = Animation::TimingFunction::OVERSHOOT,
    OVERSHOOT_REVERSE = Animation::TimingFunction::OVERSHOOT_REVERSE,
    OVERSHOOT_SIGMOID = Animation::TimingFunction::OVERSHOOT_SIGMOID,
    ELASTIC = Animation::TimingFunction::ELASTIC,
    ELASTIC_REVERSE = Animation::TimingFunction::ELASTIC_REVERSE,
    ELASTIC_SIGMOID = Animation::TimingFunction::ELASTIC_SIGMOID,
    BOUNCE = Animation::TimingFunction::BOUNCE,
    BOUNCE_REVERSE = Animation::TimingFunction::BOUNCE_REVERSE,
    BOUNCE_SIGMOID = Animation::TimingFunction::BOUNCE_SIGMOID
};

void implement_animation(jlcxx::Module& module)
{
    define_enum_in(module, AnimationState);
    module.add_enum_value(AnimationState, ANIMATION_STATE, IDLE);
    module.add_enum_value(AnimationState, ANIMATION_STATE, PAUSED);
    module.add_enum_value(AnimationState, ANIMATION_STATE, PLAYING);
    module.add_enum_value(AnimationState, ANIMATION_STATE, DONE);

    define_enum_in(module, AnimationTimingFunction);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, LINEAR);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, EXPONENTIAL);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, EXPONENTIAL_REVERSE);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, EXPONENTIAL_SIGMOID);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, SINE);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, SINE_REVERSE);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, SINE_SIGMOID);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, CIRCULAR);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, CIRCULAR_REVERSE);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, CIRCULAR_SIGMOID);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, OVERSHOOT);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, OVERSHOOT_REVERSE);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, OVERSHOOT_SIGMOID);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, ELASTIC);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, ELASTIC_REVERSE);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, ELASTIC_SIGMOID);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, BOUNCE);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, BOUNCE_REVERSE);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, BOUNCE_SIGMOID);

    auto animation = module.add_type(Animation)
        .constructor([](void* widget, float time_mys){
            return new Animation(*((Widget*) widget), microseconds(time_mys));
        })
        .method("get_state", [](Animation& self){
            return (AnimationState) self.get_state();
        })
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
        .method("set_timing_function!", [](Animation& self, AnimationTimingFunction function){
            self.set_timing_function((Animation::TimingFunction) function);
        })
        .method("get_timing_function", [](Animation& self){
            return (AnimationTimingFunction) self.get_timing_function();
        })
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