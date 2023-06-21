#include "../mousetrap_julia_binding.hpp"

// ### TIME

void implement_time(jlcxx::Module& module)
{
    module.method("ns_to_minutes", [](int64_t ns) -> double {
        return nanoseconds(ns).as_minutes();
    });
    module.method("ns_to_seconds", [](int64_t ns) -> double {
        return nanoseconds(ns).as_seconds();
    });
    module.method("ns_to_milliseconds", [](int64_t ns) -> double {
        return nanoseconds(ns).as_milliseconds();
    });
    module.method("ns_to_microseconds", [](int64_t ns) -> double {
        return nanoseconds(ns).as_microseconds();
    });
    module.method("minutes_to_ns", [](double x) -> int64_t {
        return minutes(x).as_nanoseconds();
    });
    module.method("seconds_to_ns", [](double x) -> int64_t {
        return seconds(x).as_nanoseconds();
    });
    module.method("milliseconds_to_ns", [](double x) -> int64_t {
        return milliseconds(x).as_nanoseconds();
    });
    module.method("microseconds_to_ns", [](double x) -> int64_t {
        return milliseconds(x).as_nanoseconds();
    });

    auto clock = module.add_type(Clock)
    .add_constructor()
    .method("restart!", [](Clock& clock) -> double {
        return clock.restart().as_microseconds();
    })
    .method("elapsed", [](Clock& clock) -> double {
        return clock.elapsed().as_microseconds();
    })
    ;
}