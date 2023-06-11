#include "../mousetrap_julia_binding.hpp"

// ### SELECTION MODEL

static void implement_selection_model(jlcxx::Module& module)
{
    define_enum_in(module, SelectionMode);
    module.add_enum_value(SelectionMode, SELECTION_MODE, NONE);
    module.add_enum_value(SelectionMode, SELECTION_MODE, SINGLE);
    module.add_enum_value(SelectionMode, SELECTION_MODE, MULTIPLE);

    auto selection = module.add_type(SelectionModel)
    .constructor([](void* internal){
        return new SelectionModel((detail::SelectionModelInternal*) internal);
    }, USE_FINALIZERS)
    .method("get_internal", [](SelectionModel& model) -> void* {
        return model.get_internal();
    })
    .add_type_method(SelectionModel, get_selection)
    .add_type_method(SelectionModel, select_all, !)
    .add_type_method(SelectionModel, unselect_all, !)
    .add_type_method(SelectionModel, select, !)
    .add_type_method(SelectionModel, unselect, !)
    ;

    add_signal_selection_changed<SelectionModel>(selection, "SelectionModel");
}
