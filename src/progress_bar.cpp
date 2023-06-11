
/ ### PROGRESS BAR

#include "../mousetrap_julia_binding.hpp"

static void implement_progress_bar(jlcxx::Module& module)
{
    define_enum_in(module, ProgressBarDisplayMode);
    module.add_enum_value(ProgressBarDisplayMode, PROGRESS_BAR_DISPLAY_MODE, SHOW_TEXT);
    module.add_enum_value(ProgressBarDisplayMode, PROGRESS_BAR_DISPLAY_MODE, SHOW_PERCENTAGE);

    auto bar = module.add_type(ProgressBar)
    .add_constructor()
    .add_type_method(ProgressBar, pulse)
    .add_type_method(ProgressBar, set_fraction, !)
    .add_type_method(ProgressBar, get_fraction)
    .add_type_method(ProgressBar, set_is_inverted, !)
    .add_type_method(ProgressBar, get_is_inverted)
    .add_type_method(ProgressBar, set_text, !)
    .add_type_method(ProgressBar, get_text)
    .add_type_method(ProgressBar, set_display_mode, !)
    .add_type_method(ProgressBar, get_display_mode)
    .add_type_method(ProgressBar, set_orientation, !)
    .add_type_method(ProgressBar, get_orientation)
    ;

    add_widget_signals<ProgressBar>(bar, "ProgressBar");
}
