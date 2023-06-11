#include "../mousetrap_julia_binding.hpp"

enum SectionFormat
{
    NORMAL = MenuModel::SectionFormat::NORMAL,
    HORIZONTAL_BUTTONS = MenuModel::SectionFormat::HORIZONTAL_BUTTONS,
    HORIZONTAL_BUTTONS_LEFT_TO_RIGHT = MenuModel::SectionFormat::HORIZONTAL_BUTTONS_LEFT_TO_RIGHT,
    HORIZONTAL_BUTTONS_RIGHT_TO_LEFT = MenuModel::SectionFormat::HORIZONTAL_BUTTONS_RIGHT_TO_LEFT,
    CIRCULAR_BUTTONS = MenuModel::SectionFormat::CIRCULAR_BUTTONS,
    INLINE_BUTTONS = MenuModel::SectionFormat::INLINE_BUTTONS
};

// ### MENU MODEL

void implement_menu_model(jlcxx::Module& module)
{
    define_enum_in(module, SectionFormat);
    module.add_enum_value(SectionFormat, SECTION_FORMAT, NORMAL);
    module.add_enum_value(SectionFormat, SECTION_FORMAT, HORIZONTAL_BUTTONS);
    module.add_enum_value(SectionFormat, SECTION_FORMAT, HORIZONTAL_BUTTONS_LEFT_TO_RIGHT);
    module.add_enum_value(SectionFormat, SECTION_FORMAT, HORIZONTAL_BUTTONS_RIGHT_TO_LEFT);
    module.add_enum_value(SectionFormat, SECTION_FORMAT, CIRCULAR_BUTTONS);
    module.add_enum_value(SectionFormat, SECTION_FORMAT, INLINE_BUTTONS);

    auto menu_model = module.add_type(MenuModel)
    .add_constructor()
    .add_type_method(MenuModel, add_action, !)
    .method("add_widget!", [](MenuModel& model, void* widget){
        model.add_widget(*((Widget*) widget));
    })
    .method("add_section!", [](MenuModel& model, const std::string& label, const MenuModel& other, SectionFormat format){
        model.add_section(label, other, (MenuModel::SectionFormat) format);
    })
    .add_type_method(MenuModel, add_submenu, !)
    .add_type_method(MenuModel, add_icon, !)
    ;

    add_signal_items_changed<MenuModel>(menu_model, "MenuModel");
}