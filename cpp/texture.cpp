#include "../mousetrap_julia_binding.hpp"

// ### TEXTURE

void implement_texture(jlcxx::Module& module)
{
    #if MOUSETRAP_ENABLE_OPENGL_COMPONENT

    define_enum_in(module, TextureWrapMode);
    module.add_enum_value(TextureWrapMode, TEXTURE_WRAP_MODE, ZERO);
    module.add_enum_value(TextureWrapMode, TEXTURE_WRAP_MODE, ONE);
    module.add_enum_value(TextureWrapMode, TEXTURE_WRAP_MODE, REPEAT);
    module.add_enum_value(TextureWrapMode, TEXTURE_WRAP_MODE, MIRROR);
    module.add_enum_value(TextureWrapMode, TEXTURE_WRAP_MODE, STRETCH);

    define_enum_in(module, TextureScaleMode);
    module.add_enum_value(TextureScaleMode, TEXTURE_SCALE_MODE, NEAREST);
    module.add_enum_value(TextureScaleMode, TEXTURE_SCALE_MODE, LINEAR);

    auto texture = module.add_type(Texture)
    .add_constructor()
    ;

    auto render_texture = module.add_type(RenderTexture)
    .add_constructor()
    .add_type_method(RenderTexture, bind_as_render_target)
    .add_type_method(RenderTexture, unbind_as_render_target)
    ;

    module.method("texture_download", [](void* texture) -> Image {
        return ((Texture*) texture)->download();
    });
    module.method("texture_bind", [](void* texture) -> void {
        ((Texture*) texture)->bind();
    });
    module.method("texture_unbind", [](void* texture) -> void {
        ((Texture*) texture)->unbind();
    });
    module.method("texture_create!", [](void* texture, size_t width, size_t height) {
        ((Texture*) texture)->create(width, height);
    });
    module.method("texture_create_from_image!", [](void* texture, const Image& image) {
        ((Texture*) texture)->create_from_image(image);
    });
    module.method("texture_create_from_file!", [](void* texture, const std::string& path) {
        ((Texture*) texture)->create_from_file(path);
    });
    module.method("texture_set_wrap_mode!", [](void* texture, TextureWrapMode mode){
        ((Texture*) texture)->set_wrap_mode(mode);
    });
    module.method("texture_set_scale_mode!", [](void* texture, TextureScaleMode mode){
        ((Texture*) texture)->set_scale_mode(mode);
    });
    module.method("texture_get_wrap_mode", [](void* texture){
        return ((Texture*) texture)->get_wrap_mode();
    });
    module.method("texture_get_scale_mode", [](void* texture){
        return ((Texture*) texture)->get_scale_mode();
    });
    module.method("texture_get_size", [](void* texture) -> jl_value_t* {
        return box_vector2i(((Texture*) texture)->get_size());
    });
    module.method("texture_get_native_handle", [](void* texture) -> GLNativeHandle{
        return ((Texture*) texture)->get_native_handle();
    });
    module.method("render_texture_bind_as_render_target", [](void* texture){
        ((RenderTexture*) texture)->bind_as_render_target();
    });
    module.method("render_texture_unbind_as_render_target", [](void* texture){
        ((RenderTexture*) texture)->unbind_as_render_target();
    });

    #endif // MOUSETRAP_ENABLE_OPENGL_COMPONENT
}