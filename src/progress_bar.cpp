#include "../mousetrap_julia_binding.hpp"

void implement_progress_bar(jlcxx::Module& module)
{
    auto bar = module.add_type(ProgressBar)
    .add_constructor()
    .add_type_method(ProgressBar, pulse)
    .add_type_method(ProgressBar, set_fraction, !)
    .add_type_method(ProgressBar, get_fraction)
    .add_type_method(ProgressBar, set_is_inverted, !)
    .add_type_method(ProgressBar, get_is_inverted)
    .add_type_method(ProgressBar, set_text, !)
    .add_type_method(ProgressBar, get_text)
    .add_type_method(ProgressBar, set_show_text, !)
    .add_type_method(ProgressBar, get_show_text)
    .add_type_method(ProgressBar, set_orientation, !)
    .add_type_method(ProgressBar, get_orientation)
    ;

    add_widget_signals<ProgressBar>(bar, "ProgressBar");
}
