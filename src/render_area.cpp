#include "../mousetrap_julia_binding.hpp"

// ### RENDER AREA

void implement_render_area(jlcxx::Module& module)
{
    auto render_area = module.add_type(RenderArea)
    .add_constructor()
    .method("add_render_task!", [](RenderArea& area, RenderTask& task){
        area.add_render_task(task);
    })
    .add_type_method(RenderArea, clear_render_tasks, !)
    .add_type_method(RenderArea, render_render_tasks)
    .add_type_method(RenderArea, queue_render)
    .add_type_method(RenderArea, make_current)
    .method("from_gl_coordinates", [](RenderArea& area, jl_value_t* in) -> jl_value_t* {
        auto vec2_in = unbox_vector2f(in);
        return box_vector2f(area.from_gl_coordinates(vec2_in));
    })
    .method("to_gl_coordinates", [](RenderArea& area, jl_value_t* in) -> jl_value_t* {
        auto vec2_in = unbox_vector2f(in);
        return box_vector2f(area.to_gl_coordinates(vec2_in));
    })
    .method("flush", [](RenderArea&){
        RenderArea::flush();
    })
    .method("clear", [](RenderArea&){
        RenderArea::clear();
    })
    ;

    add_widget_signals<RenderArea>(render_area, "RenderArea");
    add_signal_resize<RenderArea>(render_area, "RenderArea");
    add_signal_render<RenderArea>(render_area, "RenderArea");
}