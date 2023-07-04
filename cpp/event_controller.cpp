#include "../mousetrap_julia_binding.hpp"

// ### EVENT CONTROLLER

void implement_event_controller(jlcxx::Module& module)
{
    define_enum_in(module, PropagationPhase);
    module.add_enum_value(PropagationPhase, PROPAGATION_PHASE, NONE);
    module.add_enum_value(PropagationPhase, PROPAGATION_PHASE, CAPTURE);
    module.add_enum_value(PropagationPhase, PROPAGATION_PHASE, BUBBLE);
    module.add_enum_value(PropagationPhase, PROPAGATION_PHASE, TARGET);

    module.method("set_propagation_phase!", [](void* controller, PropagationPhase phase) {
        ((EventController*) controller)->set_propagation_phase(phase);
    });
    module.method("get_propagation_phase", [](void* controller) {
        return ((EventController*) controller)->get_propagation_phase();
    });

    define_enum_in(module, ButtonID);
    module.add_enum_value(ButtonID, BUTTON_ID, NONE);
    module.add_enum_value(ButtonID, BUTTON_ID, ANY);
    module.add_enum_value(ButtonID, BUTTON_ID, BUTTON_01);
    module.add_enum_value(ButtonID, BUTTON_ID, BUTTON_02);
    module.add_enum_value(ButtonID, BUTTON_ID, BUTTON_03);
    module.add_enum_value(ButtonID, BUTTON_ID, BUTTON_04);
    module.add_enum_value(ButtonID, BUTTON_ID, BUTTON_05);
    module.add_enum_value(ButtonID, BUTTON_ID, BUTTON_06);
    module.add_enum_value(ButtonID, BUTTON_ID, BUTTON_07);
    module.add_enum_value(ButtonID, BUTTON_ID, BUTTON_08);
    module.add_enum_value(ButtonID, BUTTON_ID, BUTTON_09);

    module.method("get_current_button", [](void* gesture) -> ButtonID {
        return ((SingleClickGesture*) gesture)->get_current_button();
    });
    module.method("set_only_listens_to_button!", [](void* gesture, ButtonID id) {
        ((SingleClickGesture*) gesture)->set_only_listens_to_button(id);
    });
    module.method("get_only_listens_to_button", [](void* gesture) -> ButtonID {
        return ((SingleClickGesture*) gesture)->get_only_listens_to_button();
    });
    module.method("get_touch_only", [](void* gesture) -> bool {
        return ((SingleClickGesture*) gesture)->get_touch_only();
    });
    module.method("set_touch_only!", [](void* gesture, bool b){
        ((SingleClickGesture*) gesture)->set_touch_only(b);
    });
}

