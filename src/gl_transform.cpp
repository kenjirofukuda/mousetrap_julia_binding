
#include "../mousetrap_julia_binding.hpp"

// ### GL TRANSFORM

void implement_gl_transform(jlcxx::Module& module)
{
    // #if MOUSETRAP_ENABLE_OPENGL_COMPONENT

    auto transform = module.add_type(GLTransform)
    .add_constructor()
    .method("apply_to_2f", [](GLTransform& self, float x, float y){
        return box_vector2f(self.apply_to(Vector2f(x, y)));
    })
    .method("apply_to_3f", [](GLTransform& self, float x, float y, float z){
        return box_vector3f(self.apply_to(Vector3f(x, y, z)));
    })
    .add_type_method(GLTransform, combine_with)
    .method("rotate!", [](GLTransform& self, float angle_rads, float x, float y){
        self.rotate(radians(angle_rads), Vector2f(x, y));
    })
    .method("translate!", [](GLTransform& self, float x, float y){
        self.translate(Vector2f(x, y));
    })
    .method("scale!", [](GLTransform& self, float x, float y){
        self.scale(x, y);
    })
    .method("reset!", [](GLTransform& self){
        self.reset();
    })
    .method("setindex!", [](GLTransform& self, size_t x, size_t y, float value){
        self.transform[x][y] = value;
    })
    .method("getindex", [](GLTransform& self, size_t x, size_t y){
        return self.transform[x][y];
    })
    ;

    // #endif // MOUSETRAP_ENABLE_OPENGL_COMPONENT
}
