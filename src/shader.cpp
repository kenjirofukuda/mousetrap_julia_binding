#include "../mousetrap_julia_binding.hpp"

// ### SHADER

void implement_shader(jlcxx::Module& module)
{
    // #if MOUSETRAP_ENABLE_OPENGL_COMPONENT

    define_enum_in(module, ShaderType);
    module.add_enum_value(ShaderType, SHADER_TYPE, FRAGMENT);
    module.add_enum_value(ShaderType, SHADER_TYPE, VERTEX);

    auto shader = module.add_type(Shader)
    .add_type_method(Shader, get_program_id)
    .add_type_method(Shader, get_fragment_shader_id)
    .add_type_method(Shader, get_vertex_shader_id)
    .add_type_method(Shader, create_from_string, !)
    .add_type_method(Shader, create_from_file, !)
    .add_type_method(Shader, get_uniform_location)
    .add_type_method(Shader, set_uniform_float, !)
    .add_type_method(Shader, set_uniform_int, !)
    .add_type_method(Shader, set_uniform_uint, !)
    .method("set_uniform_vec2!", [](Shader& shader, const std::string& name, jl_value_t* vec2){
        shader.set_uniform_vec2(name, Vector2f(
        jl_unbox_float32(jl_get_property(vec2, "x")),
        jl_unbox_float32(jl_get_property(vec2, "y"))
        ));
    })
    .method("set_uniform_vec3!", [](Shader& shader, const std::string& name, jl_value_t* vec3){
        shader.set_uniform_vec2(name, Vector3f(
        jl_unbox_float32(jl_get_property(vec3, "x")),
        jl_unbox_float32(jl_get_property(vec3, "y")),
        jl_unbox_float32(jl_get_property(vec3, "z"))
        ));
    })
    .method("set_uniform_vec4!", [](Shader& shader, const std::string& name, jl_value_t* vec4){
        shader.set_uniform_vec2(name, Vector4f(
        jl_unbox_float32(jl_get_property(vec4, "x")),
        jl_unbox_float32(jl_get_property(vec4, "y")),
        jl_unbox_float32(jl_get_property(vec4, "z")),
        jl_unbox_float32(jl_get_property(vec4, "w"))
        ));
    })
    .method("set_uniform_transform!", [](Shader& shader, const std::string& name, GLTransform& transform){
        shader.set_uniform_transform(name, transform);
    })
    ;

    module.method("shader_get_vertex_position_location", [](){
        return Shader::get_vertex_position_location();
    });
    module.method("shader_get_vertex_color_location", [](){
        return Shader::get_vertex_color_location();
    });
    module.method("shader_get_vertex_texture_coordinate_location", [](){
        return Shader::get_vertex_texture_coordinate_location();
    });

    #endif
}