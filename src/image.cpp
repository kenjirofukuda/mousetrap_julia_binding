// ### IMAGE

#include "../mousetrap_julia_binding.hpp"

void implement_image(jlcxx::Module& module)
{
    define_enum_in(module, InterpolationType);
    module.add_enum_value(InterpolationType, INTERPOLATION_TYPE, NEAREST);
    module.add_enum_value(InterpolationType, INTERPOLATION_TYPE, TILES);
    module.add_enum_value(InterpolationType, INTERPOLATION_TYPE, BILINEAR);
    module.add_enum_value(InterpolationType, INTERPOLATION_TYPE, HYPERBOLIC);

    module.add_type(Image)
    .add_constructor()
    .add_constructor(const std::string&)
    .constructor([](size_t width, size_t height, jl_value_t* rgba){
        return new Image(width, height, unbox_rgba(rgba));
    }, USE_FINALIZERS)
    .method("create!", [](Image& image, size_t width, size_t height, jl_value_t* rgba){
        image.create(width, height, unbox_rgba(rgba));
    })
    .add_type_method(Image, create_from_file, !)
    .add_type_method(Image, save_to_file)
    .add_type_method(Image, get_n_pixels)
    .method("get_size", [](const Image& image) -> jl_value_t* {
        auto size = image.get_size();
        return box_vector2i(Vector2i(size.x, size.y));
    })
    .add_type_method(Image, as_scaled)
    .add_type_method(Image, as_cropped)
    .method("set_pixel_rgba!", [](Image& image, size_t x, size_t y, jl_value_t* rgba){
        image.set_pixel(x, y, unbox_rgba(rgba));
    })
    .method("set_pixel_hsva!", [](Image& image, size_t x, size_t y, jl_value_t* hsva){
        image.set_pixel(x, y, unbox_hsva(hsva));
    })
    .method("get_pixel", [](const Image& image, size_t x, size_t y) -> jl_value_t* {
        return box_rgba(image.get_pixel(x, y));
    })
    ;
}
