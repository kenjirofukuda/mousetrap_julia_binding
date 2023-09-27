#include "../mousetrap_julia_binding.hpp"

namespace mousetrap
{
    class GLCanvas;
    namespace detail {
        struct _GLCanvasInternal
        {
            GObject parent;
            GtkGLArea* area;
        };

        using GLCanvasInternal = _GLCanvasInternal;
        DEFINE_INTERNAL_MAPPING(GLCanvas);

        DECLARE_NEW_TYPE(GLCanvasInternal, makie_canvas_internal, MAKIE_CANVAS_INTERNAL)

        static void makie_canvas_internal_finalize(GObject* object)
        {
            auto* self = MOUSETRAP_MAKIE_CANVAS_INTERNAL(object);
            G_OBJECT_CLASS(makie_canvas_internal_parent_class)->finalize(object);
            g_object_unref(self->area);
        }

        DEFINE_NEW_TYPE_TRIVIAL_INIT(GLCanvasInternal, makie_canvas_internal, MAKIE_CANVAS_INTERNAL)

        DEFINE_NEW_TYPE_TRIVIAL_CLASS_INIT(GLCanvasInternal, makie_canvas_internal, MAKIE_CANVAS_INTERNAL)

        static GLCanvasInternal* makie_canvas_internal_new(GtkGLArea* area)
        {
            auto* self = (GLCanvasInternal*) g_object_new(makie_canvas_internal_get_type(), nullptr);
            makie_canvas_internal_init(self);

            self->area = area;
            gtk_gl_area_set_required_version(self->area, 3, 3);
            g_object_ref_sink(self->area);
            return self;
        }
    }

    class GLCanvas :
        public detail::notify_if_gtk_uninitialized,
        public Widget,
        HAS_SIGNAL(GLCanvas, realize),
        HAS_SIGNAL(GLCanvas, unrealize),
        HAS_SIGNAL(GLCanvas, destroy),
        HAS_SIGNAL(GLCanvas, hide),
        HAS_SIGNAL(GLCanvas, show),
        HAS_SIGNAL(GLCanvas, map),
        HAS_SIGNAL(GLCanvas, unmap),
        HAS_SIGNAL(GLCanvas, resize),
        HAS_SIGNAL(GLCanvas, render)
    {
        private:
            detail::GLCanvasInternal* _internal = nullptr;

        public:
            GLCanvas()
            : Widget(gtk_gl_area_new()),
              CTOR_SIGNAL(GLCanvas, realize),
              CTOR_SIGNAL(GLCanvas, unrealize),
              CTOR_SIGNAL(GLCanvas, destroy),
              CTOR_SIGNAL(GLCanvas, hide),
              CTOR_SIGNAL(GLCanvas, show),
              CTOR_SIGNAL(GLCanvas, map),
              CTOR_SIGNAL(GLCanvas, unmap),
              CTOR_SIGNAL(GLCanvas, resize),
              CTOR_SIGNAL(GLCanvas, render)
            {
                _internal = detail::makie_canvas_internal_new(GTK_GL_AREA(operator NativeWidget()));
                g_object_ref_sink(_internal);
            }

            GLCanvas(detail::GLCanvasInternal* internal)
            : Widget(GTK_WIDGET(internal->area)),
              CTOR_SIGNAL(GLCanvas, realize),
              CTOR_SIGNAL(GLCanvas, unrealize),
              CTOR_SIGNAL(GLCanvas, destroy),
              CTOR_SIGNAL(GLCanvas, hide),
              CTOR_SIGNAL(GLCanvas, show),
              CTOR_SIGNAL(GLCanvas, map),
              CTOR_SIGNAL(GLCanvas, unmap),
              CTOR_SIGNAL(GLCanvas, resize),
              CTOR_SIGNAL(GLCanvas, render)
            {
                _internal = g_object_ref(internal);
            }

            ~GLCanvas()
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

void implement_makie_canvas(jlcxx::Module& module)
{
    auto canvas = module.add_type(GLCanvas)
        .add_constructor()
        .add_type_method(GLCanvas, make_current)
        .add_type_method(GLCanvas, queue_render)
        .add_type_method(GLCanvas, get_auto_render)
        .add_type_method(GLCanvas, set_auto_render)
        .method("get_context", [](GLCanvas& self) -> void* {
            return reinterpret_cast<void*>(self.get_context());
        })
    ;
    add_widget_signals<GLCanvas>(canvas, "GLCanvas");
    add_signal_resize<GLCanvas>(canvas, "GLCanvas");
    add_signal_render<GLCanvas>(canvas, "GLCanvas");
}