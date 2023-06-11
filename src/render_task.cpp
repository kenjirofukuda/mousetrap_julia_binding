//
// Created by clem on 6/11/23.
//

#include "../mousetrap_julia_binding.hpp"

// ### RENDER TASK

static void implement_render_task(jlcxx::Module& module)
{
    auto render_task = module.add_type(RenderTask)
    .constructor([](Shape& shape, void* shader_maybe, void* transform_maybe, BlendMode blend_mode) -> RenderTask* {
        return new RenderTask(
        shape,
        (Shader*) shader_maybe,
        (transform_maybe == nullptr ? GLTransform() : *((GLTransform*) transform_maybe)),
        blend_mode
        );
    }, USE_FINALIZERS)
    .add_type_method(RenderTask, render)
    .add_type_method(RenderTask, set_uniform_float)
    .add_type_method(RenderTask, set_uniform_int)
    .add_type_method(RenderTask, set_uniform_uint)
    .method("set_uniform_vec2", [](RenderTask& task, const std::string& name, jl_value_t* vec){
        task.set_uniform_vec2(name, unbox_vector2f(vec));
    })
    .method("set_uniform_vec3", [](RenderTask& task, const std::string& name, jl_value_t* vec){
        task.set_uniform_vec3(name, unbox_vector3f(vec));
    })
    .method("set_uniform_vec4", [](RenderTask& task, const std::string& name, jl_value_t* vec){
        task.set_uniform_vec4(name, unbox_vector4f(vec));
    })
    .add_type_method(RenderTask, set_uniform_transform)
    .method("set_uniform_rgba", [](RenderTask& task, const std::string& name, jl_value_t* rgba){
        task.set_uniform_rgba(name, unbox_rgba(rgba));
    })
    .method("set_uniform_hsva", [](RenderTask& task, const std::string& name, jl_value_t* hsva){
        task.set_uniform_hsva(name, unbox_hsva(hsva));
    })
    .add_type_method(RenderTask, get_uniform_float)
    .add_type_method(RenderTask, get_uniform_int)
    .add_type_method(RenderTask, get_uniform_uint)
    .method("get_uniform_vec2", [](RenderTask& task, const std::string& name) -> jl_value_t* {
        return box_vector2f(task.get_uniform_vec2(name));
    })
    .method("set_uniform_vec3", [](RenderTask& task, const std::string& name) -> jl_value_t* {
        return box_vector3f(task.get_uniform_vec3(name));
    })
    .method("set_uniform_vec4", [](RenderTask& task, const std::string& name) -> jl_value_t* {
        return box_vector4f(task.get_uniform_vec4(name));
    })
    .add_type_method(RenderTask, get_uniform_transform)
    .method("set_uniform_rgba", [](RenderTask& task, const std::string& name) -> jl_value_t* {
        return box_rgba(task.get_uniform_rgba(name));
    })
    .method("set_uniform_hsva", [](RenderTask& task, const std::string& name) -> jl_value_t* {
        return box_hsva(task.get_uniform_hsva(name));
    })
    ;
}