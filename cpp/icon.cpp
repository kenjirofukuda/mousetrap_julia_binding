#include "../mousetrap_julia_binding.hpp"

// ### ICON

void implement_icon(jlcxx::Module& module)
{
    module.add_type(Icon)
    .add_constructor()
    .add_type_method(Icon, create_from_file, !)
    .method("create_from_theme!", [](Icon& icon, void* theme, IconID id, size_t square_resolution, size_t scale){
        return icon.create_from_theme(*((IconTheme*) theme), id, square_resolution, scale);
    })
    .add_type_method(Icon, get_name)
    .add_type_method(Icon, get_scale)
    .method("get_size", [](const Icon& icon) -> jl_value_t*{
        return box_vector2i(icon.get_size());
    })
    ;

    module.method("compare_icons", [](const Icon& a, const Icon& b) -> bool {
        return a == b;
    });

    module.add_type(IconTheme)
    .add_constructor(const Window&)
    .add_type_method(IconTheme, get_icon_names)
    .method("has_icon_icon", [](const IconTheme& theme, const Icon& icon) -> bool {
        return theme.has_icon(icon);
    })
    .method("has_icon_id", [](const IconTheme& theme, const IconID& id) -> bool {
        return theme.has_icon(id);
    })
    .add_type_method(IconTheme, add_resource_path, !)
    .add_type_method(IconTheme, set_resource_path, !)
    ;
}