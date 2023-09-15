//
// Created by clem on 8/27/23.
//

#include "../mousetrap_julia_binding.hpp"

void implement_style_class(jlcxx::Module& module)
{
    module.method("style_manager_add_css!", [](const std::string& string){
        mousetrap::StyleManager::add_css(string);
    });
    module.method("style_manager_color_to_css_rgba", [](float r, float g, float b, float a){
        return mousetrap::StyleManager::color_to_css(RGBA(r, g, b, a));
    });
    module.method("style_manager_color_to_css_hsva", [](float h, float s, float v, float a){
        return mousetrap::StyleManager::color_to_css(HSVA(h, s, v, a));
    });
}
