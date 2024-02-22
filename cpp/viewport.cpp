#include "../mousetrap_julia_binding.hpp"

// ### VIEWPORT

void implement_viewport(jlcxx::Module& module)
{
    define_enum_in(module, ScrollbarVisibilityPolicy);
    module.add_enum_value(ScrollbarVisibilityPolicy, SCROLLBAR_VISIBILITY_POLICY, NEVER);
    module.add_enum_value(ScrollbarVisibilityPolicy, SCROLLBAR_VISIBILITY_POLICY, ALWAYS);
    module.add_enum_value(ScrollbarVisibilityPolicy, SCROLLBAR_VISIBILITY_POLICY, AUTOMATIC);

    define_enum_in(module, CornerPlacement);
    module.add_enum_value(CornerPlacement, CORNER_PLACEMENT, TOP_LEFT);
    module.add_enum_value(CornerPlacement, CORNER_PLACEMENT, TOP_RIGHT);
    module.add_enum_value(CornerPlacement, CORNER_PLACEMENT, BOTTOM_LEFT);
    module.add_enum_value(CornerPlacement, CORNER_PLACEMENT, BOTTOM_RIGHT);

    define_enum_in(module, ScrollType);
    module.add_enum_value(ScrollType, SCROLL_TYPE, NONE);
    module.add_enum_value(ScrollType, SCROLL_TYPE, JUMP);
    module.add_enum_value(ScrollType, SCROLL_TYPE, STEP_BACKWARD);
    module.add_enum_value(ScrollType, SCROLL_TYPE, STEP_FORWARD);
    module.add_enum_value(ScrollType, SCROLL_TYPE, STEP_UP);
    module.add_enum_value(ScrollType, SCROLL_TYPE, STEP_DOWN);
    module.add_enum_value(ScrollType, SCROLL_TYPE, STEP_LEFT);
    module.add_enum_value(ScrollType, SCROLL_TYPE, STEP_RIGHT);
    module.add_enum_value(ScrollType, SCROLL_TYPE, PAGE_BACKWARD);
    module.add_enum_value(ScrollType, SCROLL_TYPE, PAGE_FORWARD);
    module.add_enum_value(ScrollType, SCROLL_TYPE, PAGE_UP);
    module.add_enum_value(ScrollType, SCROLL_TYPE, PAGE_DOWN);
    module.add_enum_value(ScrollType, SCROLL_TYPE, PAGE_LEFT);
    module.add_enum_value(ScrollType, SCROLL_TYPE, PAGE_RIGHT);
    module.add_enum_value(ScrollType, SCROLL_TYPE, SCROLL_START);
    module.add_enum_value(ScrollType, SCROLL_TYPE, SCROLL_END);

    auto viewport = module.add_type(Viewport)
    .constructor<>(USE_FINALIZERS)
    .add_type_method(Viewport, set_propagate_natural_height, !)
    .add_type_method(Viewport, get_propagate_natural_height)
    .add_type_method(Viewport, set_propagate_natural_width, !)
    .add_type_method(Viewport, get_propagate_natural_width)
    .add_type_method(Viewport, set_horizontal_scrollbar_policy, !)
    .add_type_method(Viewport, get_horizontal_scrollbar_policy)
    .add_type_method(Viewport, set_vertical_scrollbar_policy, !)
    .add_type_method(Viewport, get_vertical_scrollbar_policy)
    .add_type_method(Viewport, set_scrollbar_placement, !)
    .add_type_method(Viewport, get_scrollbar_placement)
    .add_type_method(Viewport, set_has_frame, !)
    .add_type_method(Viewport, get_has_frame)
    .method("get_horizontal_adjustment", [](Viewport& self) -> void* {
        return self.get_horizontal_adjustment().get_internal();
    })
    .method("get_vertical_adjustment", [](Viewport& self) -> void* {
        return self.get_horizontal_adjustment().get_internal();
    })
    .add_type_method(Viewport, set_kinetic_scrolling_enabled, !)
    .add_type_method(Viewport, get_kinetic_scrolling_enabled)
    .method("set_child!", [](Viewport& self, void* child){
        self.set_child(*((Widget*) child));
    })
    .add_type_method(Viewport, remove_child)
    ;

    add_widget_signals<Viewport>(viewport, "Viewport");
    add_signal_scroll_child<Viewport>(viewport, "Viewport");
}