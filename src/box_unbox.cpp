#include "../mousetrap_julia_binding.hpp"

jl_value_t* box_vector2f(Vector2f in)
{
    static auto* ctor = jl_eval_string("mousetrap.Vector2f");
    return jl_safe_call("box_vector2f", ctor, jl_box_float32(in.x), jl_box_float32(in.y));
}

Vector2f unbox_vector2f(jl_value_t* in)
{
    return Vector2f {
    jl_unbox_float32(jl_get_property(in, "x")),
    jl_unbox_float32(jl_get_property(in, "y"))
    };
}

jl_value_t* box_vector2i(Vector2i in)
{
    static auto* ctor = jl_eval_string("mousetrap.Vector2i");
    return jl_safe_call("box_vector2i",ctor, jl_box_int64(in.x), jl_box_int64(in.y));
}

Vector2f unbox_vector2i(jl_value_t* in)
{
    return Vector2i {
    jl_unbox_int64(jl_get_property(in, "x")),
    jl_unbox_int64(jl_get_property(in, "y"))
    };
}

jl_value_t* box_vector3f(Vector3f in)
{
    static auto* ctor = jl_eval_string("mousetrap.Vector3f");
    return jl_safe_call("box_vector3f",ctor, jl_box_float32(in.x), jl_box_float32(in.y), jl_box_float32(in.z));
}

Vector3f unbox_vector3f(jl_value_t* in)
{
    return Vector3f {
    jl_unbox_float32(jl_get_property(in, "x")),
    jl_unbox_float32(jl_get_property(in, "y")),
    jl_unbox_float32(jl_get_property(in, "z"))
    };
}

jl_value_t* box_vector4f(Vector4f in)
{
    static auto* ctor = jl_eval_string("mousetrap.Vector4f");
    return jl_safe_call("box_vector4f",ctor,
                    jl_box_float32(in.x),
                    jl_box_float32(in.y),
                    jl_box_float32(in.z),
                    jl_box_float32(in.z)
    );
}

Vector4f unbox_vector4f(jl_value_t* in)
{
    return Vector4f {
    jl_unbox_float32(jl_get_property(in, "x")),
    jl_unbox_float32(jl_get_property(in, "y")),
    jl_unbox_float32(jl_get_property(in, "z")),
    jl_unbox_float32(jl_get_property(in, "w"))
    };
}

jl_value_t* box_rgba(RGBA in)
{
    static auto* ctor = jl_eval_string("return mousetrap.RGBA");
    return jl_safe_call("box_rgba",
    ctor,
    jl_box_float32(in.r),
    jl_box_float32(in.g),
    jl_box_float32(in.b),
    jl_box_float32(in.a)
    );
}

RGBA unbox_rgba(jl_value_t* in)
{
    return RGBA {
    jl_unbox_float32(jl_get_property(in, "r")),
    jl_unbox_float32(jl_get_property(in, "g")),
    jl_unbox_float32(jl_get_property(in, "b")),
    jl_unbox_float32(jl_get_property(in, "a"))
    };
}

jl_value_t* box_hsva(HSVA in)
{
    static auto* ctor = jl_eval_string("return mousetrap.RGBA");
    return jl_safe_call("box_hsva",
    ctor,
    jl_box_float32(in.h),
    jl_box_float32(in.s),
    jl_box_float32(in.v),
    jl_box_float32(in.a)
    );
}

HSVA unbox_hsva(jl_value_t* in)
{
    return HSVA {
    jl_unbox_float32(jl_get_property(in, "h")),
    jl_unbox_float32(jl_get_property(in, "s")),
    jl_unbox_float32(jl_get_property(in, "v")),
    jl_unbox_float32(jl_get_property(in, "a"))
    };
}