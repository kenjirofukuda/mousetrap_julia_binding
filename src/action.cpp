#include "../mousetrap_julia_binding.hpp"

// ### ACTION

void implement_action(jlcxx::Module& module)
{
    auto action = module.add_type(Action)
    .constructor( [](const std::string& id, void* app_ptr){
        return new Action(id, *((Application*) app_ptr));
    }, USE_FINALIZERS)
    .add_type_method(Action, get_id)
    .add_type_method(Action, set_state, !)
    .add_type_method(Action, get_state)
    .add_type_method(Action, activate)
    .add_type_method(Action, add_shortcut, !)
    .add_type_method(Action, get_shortcuts)
    .add_type_method(Action, clear_shortcuts, !)
    .add_type_method(Action, set_enabled, !)
    .add_type_method(Action, get_enabled)
    .add_type_method(Action, get_is_stateful)
    ;

    action.method("set_function!", [](Action& action, jl_function_t* task) {
        action.set_function([](Action& action, jl_function_t* task){
            jl_safe_call("Action::activate", task, jlcxx::box<Action&>(action));
        }, gc_protect(action, task));
    });

    action.method("set_stateful_function!", [](Action& action, jl_function_t* task) {
        action.set_stateful_function([](Action& action, bool b, jl_function_t* task) -> bool{
            auto* out = jl_safe_call("Action::activate", task, jlcxx::box<Action&>(action), jl_box_bool(b));
            if (out != nullptr)
                return (bool) jl_unbox_bool(out);
            else
                return false;
        }, gc_protect(action, task));
    });

    add_signal_activated<Action>(action, "Action");
}