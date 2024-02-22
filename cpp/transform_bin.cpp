//
// Created by clem on 8/26/23.
//

#include "../mousetrap_julia_binding.hpp"

void implement_transform_bin(jlcxx::Module& module)
{
    auto bin = module.add_type(TransformBin)
    .constructor<>(USE_FINALIZERS)
    .method("set_child!", [](TransformBin& self, void* widget){
        self.set_child(*((Widget*) widget));
    })
    .add_type_method(TransformBin, remove_child, !)
    .add_type_method(TransformBin, reset, !)
    .method("rotate!", [](TransformBin& self, float angle_dg){
        self.rotate(degrees(angle_dg));
    })
    .method("translate!", [](TransformBin& self, float x, float y){
        self.translate(Vector2f(x, y));
    })
    .add_type_method(TransformBin, scale, !)
    .add_type_method(TransformBin, skew, !)
    ;

    add_widget_signals<TransformBin>(bin, "TransformBin");
}
