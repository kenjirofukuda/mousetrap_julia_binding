#include "../mousetrap_julia_binding.hpp"

// ### FRAME CLOCK

void implement_frame_clock(jlcxx::Module& module)
{
    auto frame_clock = module.add_type(FrameClock)
    .constructor([](void* internal){
        return new FrameClock(GDK_FRAME_CLOCK(internal));
    }, USE_FINALIZERS)
    .method("get_target_frame_duration", [](FrameClock& self){
        return self.get_target_frame_duration().as_microseconds();
    })
    .method("get_time_since_last_frame", [](FrameClock& self){
        return self.get_time_since_last_frame().as_microseconds();
    })
    .add_type_method(FrameClock, get_fps)
    ;

    add_signal_update<FrameClock>(frame_clock, "FrameClock");
    add_signal_paint<FrameClock>(frame_clock, "FrameClock");
}