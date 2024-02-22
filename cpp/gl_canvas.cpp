#include "../mousetrap_julia_binding.hpp"

namespace mousetrap
{
    class GLArea;
    namespace detail {
        struct _GLAreaInternal
        {
            GObject parent;
            GtkGLArea* area;
        };

        using GLAreaInternal = _GLAreaInternal;
        DEFINE_INTERNAL_MAPPING(GLArea);

        DECLARE_NEW_TYPE(GLAreaInternal, makie_canvas_internal, MAKIE_CANVAS_INTERNAL)

        static void makie_canvas_internal_finalize(GObject* object)
        {
            auto* self = MOUSETRAP_MAKIE_CANVAS_INTERNAL(object);
            G_OBJECT_CLASS(makie_canvas_internal_parent_class)->finalize(object);
            g_object_unref(self->area);
        }

        DEFINE_NEW_TYPE_TRIVIAL_INIT(GLAreaInternal, makie_canvas_internal, MAKIE_CANVAS_INTERNAL)

        DEFINE_NEW_TYPE_TRIVIAL_CLASS_INIT(GLAreaInternal, makie_canvas_internal, MAKIE_CANVAS_INTERNAL)

        static GLAreaInternal* makie_canvas_internal_new(GtkGLArea* area)
        {
            auto* self = (GLAreaInternal*) g_object_new(makie_canvas_internal_get_type(), nullptr);
            makie_canvas_internal_init(self);

            self->area = area;
            gtk_gl_area_set_required_version(self->area, 3, 3);
            g_object_ref_sink(self->area);
            return self;
        }
    }

    class GLArea :
        public detail::notify_if_gtk_uninitialized,
        public Widget,
        HAS_SIGNAL(GLArea, realize),
        HAS_SIGNAL(GLArea, unrealize),
        HAS_SIGNAL(GLArea, destroy),
        HAS_SIGNAL(GLArea, hide),
        HAS_SIGNAL(GLArea, show),
        HAS_SIGNAL(GLArea, map),
        HAS_SIGNAL(GLArea, unmap),
        HAS_SIGNAL(GLArea, resize),
        HAS_SIGNAL(GLArea, render)
    {
        private:
            detail::GLAreaInternal* _internal = nullptr;

        public:
            GLArea()
            : Widget(gtk_gl_area_new()),
              CTOR_SIGNAL(GLArea, realize),
              CTOR_SIGNAL(GLArea, unrealize),
              CTOR_SIGNAL(GLArea, destroy),
              CTOR_SIGNAL(GLArea, hide),
              CTOR_SIGNAL(GLArea, show),
              CTOR_SIGNAL(GLArea, map),
              CTOR_SIGNAL(GLArea, unmap),
              CTOR_SIGNAL(GLArea, resize),
              CTOR_SIGNAL(GLArea, render)
            {
                _internal = detail::makie_canvas_internal_new(GTK_GL_AREA(operator NativeWidget()));
                g_object_ref_sink(_internal);
            }

            GLArea(detail::GLAreaInternal* internal)
            : Widget(GTK_WIDGET(internal->area)),
              CTOR_SIGNAL(GLArea, realize),
              CTOR_SIGNAL(GLArea, unrealize),
              CTOR_SIGNAL(GLArea, destroy),
              CTOR_SIGNAL(GLArea, hide),
              CTOR_SIGNAL(GLArea, show),
              CTOR_SIGNAL(GLArea, map),
              CTOR_SIGNAL(GLArea, unmap),
              CTOR_SIGNAL(GLArea, resize),
              CTOR_SIGNAL(GLArea, render)
            {
                _internal = g_object_ref(internal);
            }

            ~GLArea()
            {
                g_object_unref(_internal);
            }

            void make_current()
            {
                gtk_gl_area_make_current(_internal->area);
            }

            void queue_render()
            {
                gtk_gl_area_queue_render(_internal->area);
            }

            bool get_auto_render() const
            {
                return gtk_gl_area_get_auto_render(_internal->area);
            }

            void set_auto_render(bool b)
            {
                gtk_gl_area_set_auto_render(_internal->area, b);
            }

            GdkGLContext* get_context() const
            {
                return gtk_gl_area_get_context(_internal->area);
            }
    };
}

void implement_gl_canvas(jlcxx::Module& module)
{
    auto canvas = module.add_type(GLArea)
        .constructor<>(USE_FINALIZERS)
        .add_type_method(GLArea, make_current)
        .add_type_method(GLArea, queue_render)
        .add_type_method(GLArea, get_auto_render)
        .add_type_method(GLArea, set_auto_render, !)
        .method("get_context", [](GLArea& self) -> void* {
            return reinterpret_cast<void*>(self.get_context());
        })
    ;
    add_widget_signals<GLArea>(canvas, "GLArea");
    add_signal_resize<GLArea>(canvas, "GLArea");
    add_signal_render<GLArea>(canvas, "GLArea");
}