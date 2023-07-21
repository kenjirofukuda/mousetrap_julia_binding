#include "../mousetrap_julia_binding.hpp"

void implement_stack(jlcxx::Module& module)
{
    define_enum_in(module, StackTransitionType);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, NONE);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, CROSSFADE);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, SLIDE_RIGHT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, SLIDE_LEFT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, SLIDE_DOWN);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, SLIDE_UP);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, SLIDE_LEFT_RIGHT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, SLIDE_UP_DOWN);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, OVER_UP);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, OVER_DOWN);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, OVER_LEFT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, OVER_RIGHT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, UNDER_UP);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, UNDER_DOWN);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, UNDER_LEFT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, UNDER_RIGHT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, OVER_UP_DOWN);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, OVER_DOWN_UP);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, OVER_LEFT_RIGHT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, OVER_RIGHT_LEFT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, ROTATE_LEFT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, ROTATE_RIGHT);
    module.add_enum_value(StackTransitionType, STACK_TRANSITION_TYPE, ROTATE_LEFT_RIGHT);

    auto stack = module.add_type(Stack)
    .add_constructor()
    .method("get_selection_model", [](Stack& stack) -> void* {
        return stack.get_selection_model().get_internal();
    })
    .method("add_child!", [](Stack& stack, void* widget, const std::string& title) -> std::string {
        return stack.add_child(*((Widget*) widget), title);
    })
    .method("remove_child!", [](Stack& stack, const std::string& id) {
        stack.remove_child(id);
    })
    .add_type_method(Stack, get_n_children)
    .method("set_visible_child!", [](Stack& stack, const std::string& id) {
        stack.set_visible_child(id);
    })
    .method("get_visible_child!", [](Stack& stack) -> std::string {
        return stack.get_visible_child();
    })
    .add_type_method(Stack, get_child_at)
    .add_type_method(Stack, set_transition_type, !)
    .add_type_method(Stack, get_transition_type)
    .method("set_transition_duration!", [](Stack& stack, float duration_mys){
        stack.set_transition_duration(microseconds(duration_mys));
    })
    .method("get_transition_duration", [](Stack& stack) -> float {
        return stack.get_transition_duration().as_microseconds();
    })
    .add_type_method(Stack, set_is_horizontally_homogeneous, !)
    .add_type_method(Stack, get_is_horizontally_homogeneous)
    .add_type_method(Stack, set_is_vertically_homogeneous, !)
    .add_type_method(Stack, get_is_vertically_homogeneous)
    .add_type_method(Stack, set_should_interpolate_size, !)
    .add_type_method(Stack, get_should_interpolate_size)
    ;

    add_widget_signals<Stack>(stack, "Stack");

    auto sidebar = module.add_type(StackSidebar)
    .add_constructor(const Stack&)
    ;
    add_widget_signals<StackSidebar>(sidebar, "SideBar");

    auto switcher = module.add_type(StackSwitcher)
    .add_constructor(const Stack&)
    ;
    add_widget_signals<StackSwitcher>(switcher, "StackSwitcher");
}