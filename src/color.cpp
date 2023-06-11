#include "../mousetrap_julia_binding.hpp"

// ### COLOR

static void implement_color(jlcxx::Module& module)
{
    module.method("rgba_to_hsva", [](jl_value_t* rgba)
    {
        return box_hsva(rgba_to_hsva(unbox_rgba(rgba)));
    });

    module.method("hsva_to_rgba", [](jl_value_t* hsva)
    {
        return box_rgba(hsva_to_rgba(unbox_hsva(hsva)));
    });

    module.method("rgba_to_html_code", [](jl_value_t* rgba) -> std::string
    {
        return rgba_to_html_code(unbox_rgba(rgba));
    });

    module.method("html_code_to_rgba", [](const std::string& code) -> jl_value_t*
    {
        return box_rgba(html_code_to_rgba(code));
    });
}