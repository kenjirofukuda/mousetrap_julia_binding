#include "../mousetrap_julia_binding.hpp"

// ### IMAGE DISPLAY

void implement_image_display(jlcxx::Module& module)
{
    auto image_display = module.add_type(ImageDisplay)
    .add_constructor(const std::string&)
    .add_constructor(const Image&)
    .add_constructor(const Icon&)
    .method("get_size", [](ImageDisplay& x) -> jl_value_t* {
        return box_vector2i(x.get_size());
    })
    .add_type_method(ImageDisplay, create_from_file, !)
    .add_type_method(ImageDisplay, create_from_image, !)
    .add_type_method(ImageDisplay, create_from_icon, !)
    .add_type_method(ImageDisplay, create_as_file_preview, !)
    .add_type_method(ImageDisplay, clear, !)
    .add_type_method(ImageDisplay, set_scale, !)
    .add_type_method(ImageDisplay, get_scale)
    ;

    add_widget_signals<ImageDisplay>(image_display, "ImageDisplay");
}