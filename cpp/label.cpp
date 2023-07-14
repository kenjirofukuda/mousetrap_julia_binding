#include "../mousetrap_julia_binding.hpp"

// ### LABEL

void implement_label(jlcxx::Module& module)
{
    define_enum_in(module, EllipsizeMode)
    module.add_enum_value(EllipsizeMode, ELLIPSIZE_MODE, NONE);
    module.add_enum_value(EllipsizeMode, ELLIPSIZE_MODE, START);
    module.add_enum_value(EllipsizeMode, ELLIPSIZE_MODE, MIDDLE);
    module.add_enum_value(EllipsizeMode, ELLIPSIZE_MODE, END);

    define_enum_in(module, LabelWrapMode)
    module.add_enum_value(LabelWrapMode, LABEL_WRAP_MODE, NONE);
    module.add_enum_value(LabelWrapMode, LABEL_WRAP_MODE, ONLY_ON_WORD);
    module.add_enum_value(LabelWrapMode, LABEL_WRAP_MODE, ONLY_ON_CHAR);
    module.add_enum_value(LabelWrapMode, LABEL_WRAP_MODE, WORD_OR_CHAR);

    auto label = module.add_type(Label)
    .add_constructor()
    .add_constructor(const std::string&)
    .add_type_method(Label, set_text, !)
    .add_type_method(Label, get_text)
    .add_type_method(Label, set_use_markup, !)
    .add_type_method(Label, get_use_markup)
    .add_type_method(Label, set_ellipsize_mode, !)
    .add_type_method(Label, get_ellipsize_mode)
    .add_type_method(Label, set_wrap_mode, !)
    .add_type_method(Label, get_wrap_mode)
    .add_type_method(Label, set_justify_mode, !)
    .add_type_method(Label, get_justify_mode)
    .add_type_method(Label, set_max_width_chars, !)
    .add_type_method(Label, get_max_width_chars)
    .add_type_method(Label, set_x_alignment, !)
    .add_type_method(Label, get_x_alignment)
    .add_type_method(Label, set_y_alignment, !)
    .add_type_method(Label, get_y_alignment)
    .add_type_method(Label, set_is_selectable, !)
    .add_type_method(Label, get_is_selectable)
    ;

    add_widget_signals<Label>(label, "Label");
}