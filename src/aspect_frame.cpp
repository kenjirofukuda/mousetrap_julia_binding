#include "../mousetrap_julia_binding.hpp"

// ### ASPECT FRAME

static void implement_aspect_frame(jlcxx::Module& module)
{
    auto aspect_frame = module.add_type(AspectFrame)
    .constructor([](float ratio, float x_alignment, float y_alignment){
        return new AspectFrame(ratio, x_alignment, y_alignment);
    }, USE_FINALIZERS)
    .add_type_method(AspectFrame, set_ratio, !)
    .add_type_method(AspectFrame, get_ratio)
    .add_type_method(AspectFrame, set_child_x_alignment, !)
    .add_type_method(AspectFrame, set_child_y_alignment, !)
    .add_type_method(AspectFrame, get_child_x_alignment)
    .add_type_method(AspectFrame, get_child_y_alignment)
    .add_type_method(AspectFrame, remove_child, !)
    .method("set_child", [](AspectFrame& instance, void* widget){
        instance.set_child(*((Widget*) widget));
    });

    add_widget_signals<AspectFrame>(aspect_frame, "AspectFrame");
}