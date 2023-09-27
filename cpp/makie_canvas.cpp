#include "../mousetrap_julia_binding.hpp"

namespace mousetrap
{
    class MakieCanvas;
    namespace detail {
        struct _MakieCanvasInternal
        {
            GObject parent;
            GtkGLArea* area;
        };

        using MakieCanvasInternal = _MakieCanvasInternal;
        DEFINE_INTERNAL_MAPPING(MakieCanvas);

        DECLARE_NEW_TYPE(MakieCanvasInternal, makie_canvas_internal, MAKIE_CANVAS_INTERNAL)

        static void makie_canvas_internal_finalize(GObject* object)
        {
            auto* self = MOUSETRAP_MAKIE_CANVAS_INTERNAL(object);
            G_OBJECT_CLASS(makie_canvas_internal_parent_class)->finalize(object);
            g_object_unref(self->area);
        }

        DEFINE_NEW_TYPE_TRIVIAL_INIT(MakieCanvasInternal, makie_canvas_internal, MAKIE_CANVAS_INTERNAL)

        DEFINE_NEW_TYPE_TRIVIAL_CLASS_INIT(MakieCanvasInternal, makie_canvas_internal, MAKIE_CANVAS_INTERNAL)

        static MakieCanvasInternal* makie_canvas_internal_new(GtkGLArea* area)
        {
            auto* self = (MakieCanvasInternal*) g_object_new(makie_canvas_internal_get_type(), nullptr);
            makie_canvas_internal_init(self);

            self->area = area;
            g_object_ref_sink(self->area);
            return self;
        }
    }

    class MakieCanvas :
        public detail::notify_if_gtk_uninitialized,
        public Widget,
        HAS_SIGNAL(MakieCanvas, realize),
        HAS_SIGNAL(MakieCanvas, unrealize),
        HAS_SIGNAL(MakieCanvas, destroy),
        HAS_SIGNAL(MakieCanvas, hide),
        HAS_SIGNAL(MakieCanvas, show),
        HAS_SIGNAL(MakieCanvas, map),
        HAS_SIGNAL(MakieCanvas, unmap),
        HAS_SIGNAL(MakieCanvas, resize),
        HAS_SIGNAL(MakieCanvas, render)
    {
        private:
            detail::MakieCanvasInternal* _internal = nullptr;

        public:
            MakieCanvas()
            : Widget(gtk_gl_area_new()),
              CTOR_SIGNAL(MakieCanvas, realize),
              CTOR_SIGNAL(MakieCanvas, unrealize),
              CTOR_SIGNAL(MakieCanvas, destroy),
              CTOR_SIGNAL(MakieCanvas, hide),
              CTOR_SIGNAL(MakieCanvas, show),
              CTOR_SIGNAL(MakieCanvas, map),
              CTOR_SIGNAL(MakieCanvas, unmap),
              CTOR_SIGNAL(MakieCanvas, resize),
              CTOR_SIGNAL(MakieCanvas, render)
            {
                _internal = detail::makie_canvas_internal_new(GTK_GL_AREA(operator NativeWidget()));
                g_object_ref_sink(_internal);
            }

            MakieCanvas(detail::MakieCanvasInternal* internal)
            : Widget(GTK_WIDGET(internal->area)),
              CTOR_SIGNAL(MakieCanvas, realize),
              CTOR_SIGNAL(MakieCanvas, unrealize),
              CTOR_SIGNAL(MakieCanvas, destroy),
              CTOR_SIGNAL(MakieCanvas, hide),
              CTOR_SIGNAL(MakieCanvas, show),
              CTOR_SIGNAL(MakieCanvas, map),
              CTOR_SIGNAL(MakieCanvas, unmap),
              CTOR_SIGNAL(MakieCanvas, resize),
              CTOR_SIGNAL(MakieCanvas, render)
            {
                _internal = g_object_ref(internal);
            }

            ~MakieCanvas()
            {
                g_object_unref(_internal);
            }
    };
}

void implement_makie_canvas(jlcxx::Module& module)
{
    auto canvas = module.add_type(MakieCanvas)
        .add_constructor()
    ;

    add_widget_signals<MakieCanvas>(canvas, "MakieCanvas");
    add_signal_resize<MakieCanvas>(canvas, "MakieCanvas");
    add_signal_render<MakieCanvas>(canvas, "MakieCanvas");
}