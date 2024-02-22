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
    EXPONENTIAL_EASE_IN = Animation::TimingFunction::EXPONENTIAL_EASE_IN,
    EXPONENTIAL_EASE_OUT = Animation::TimingFunction::EXPONENTIAL_EASE_OUT,
    EXPONENTIAL_SIGMOID = Animation::TimingFunction::EXPONENTIAL_SIGMOID,
    SINE_EASE_IN = Animation::TimingFunction::SINE_EASE_IN,
    SINE_EASE_OUT = Animation::TimingFunction::SINE_EASE_OUT,
    SINE_SIGMOID = Animation::TimingFunction::SINE_SIGMOID,
    CIRCULAR_EASE_IN = Animation::TimingFunction::CIRCULAR_EASE_IN,
    CIRCULAR_EASE_OUT = Animation::TimingFunction::CIRCULAR_EASE_OUT,
    CIRCULAR_SIGMOID = Animation::TimingFunction::CIRCULAR_SIGMOID,
    OVERSHOOT_EASE_IN = Animation::TimingFunction::OVERSHOOT_EASE_IN,
    OVERSHOOT_EASE_OUT = Animation::TimingFunction::OVERSHOOT_EASE_OUT,
    OVERSHOOT_SIGMOID = Animation::TimingFunction::OVERSHOOT_SIGMOID,
    ELASTIC_EASE_IN = Animation::TimingFunction::ELASTIC_EASE_IN,
    ELASTIC_EASE_OUT = Animation::TimingFunction::ELASTIC_EASE_OUT,
    ELASTIC_SIGMOID = Animation::TimingFunction::ELASTIC_SIGMOID,
    BOUNCE_EASE_IN = Animation::TimingFunction::BOUNCE_EASE_IN,
    BOUNCE_EASE_OUT = Animation::TimingFunction::BOUNCE_EASE_OUT,
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
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, EXPONENTIAL_EASE_IN);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, EXPONENTIAL_EASE_OUT);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, EXPONENTIAL_SIGMOID);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, SINE_EASE_IN);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, SINE_EASE_OUT);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, SINE_SIGMOID);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, CIRCULAR_EASE_IN);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, CIRCULAR_EASE_OUT);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, CIRCULAR_SIGMOID);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, OVERSHOOT_EASE_IN);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, OVERSHOOT_EASE_OUT);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, OVERSHOOT_SIGMOID);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, ELASTIC_EASE_IN);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, ELASTIC_EASE_OUT);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, ELASTIC_SIGMOID);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, BOUNCE_EASE_IN);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, BOUNCE_EASE_OUT);
    module.add_enum_value(AnimationTimingFunction, ANIMATION_TIMING_FUNCTION, BOUNCE_SIGMOID);

    auto animation = module.add_type(Animation)
        .constructor([](void* widget, float time_mys){
            return new Animation(*((Widget*) widget), microseconds(time_mys));
        }, USE_FINALIZERS)
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