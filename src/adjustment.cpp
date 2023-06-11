//
// Created by clem on 6/11/23.
//

#include "../mousetrap_julia_binding.hpp"

// ### ADJUSTMENT

static void implement_adjustment(jlcxx::Module& module)
{
    auto adjustment = module.add_type(Adjustment)
    .constructor([](void* internal){
        return new Adjustment(GTK_ADJUSTMENT(internal));
    }, USE_FINALIZERS)
    .add_constructor(float, float, float, float)
    .add_type_method(Adjustment, get_lower)
    .add_type_method(Adjustment, get_upper)
    .add_type_method(Adjustment, get_value)
    .add_type_method(Adjustment, get_increment)
    .add_type_method(Adjustment, set_lower, !)
    .add_type_method(Adjustment, set_upper, !)
    .add_type_method(Adjustment, set_value, !)
    .add_type_method(Adjustment, set_increment, !)
    ;

    add_signal_value_changed<Adjustment>(adjustment, "Adjustment");
    add_signal_properties_changed<Adjustment>(adjustment, "Adjustment");
}
