#include "../mousetrap_julia_binding.hpp"

// ### FILE MONITOR

void implement_file_monitor(jlcxx::Module& module)
{
    define_enum_in(module, FileMonitorEvent);
    module.add_enum_value(FileMonitorEvent, FILE_MONITOR_EVENT, CHANGED);
    module.add_enum_value(FileMonitorEvent, FILE_MONITOR_EVENT, CHANGES_DONE_HINT);
    module.add_enum_value(FileMonitorEvent, FILE_MONITOR_EVENT, DELETED);
    module.add_enum_value(FileMonitorEvent, FILE_MONITOR_EVENT, CREATED);
    module.add_enum_value(FileMonitorEvent, FILE_MONITOR_EVENT, ATTRIBUTE_CHANGED);
    module.add_enum_value(FileMonitorEvent, FILE_MONITOR_EVENT, RENAMED);
    module.add_enum_value(FileMonitorEvent, FILE_MONITOR_EVENT, MOVED_IN);
    module.add_enum_value(FileMonitorEvent, FILE_MONITOR_EVENT, MOVED_OUT);

    auto monitor = module.add_type(FileMonitor)
    .constructor([](void* internal){
        return new FileMonitor((detail::FileMonitorInternal*) internal);
    }, USE_FINALIZERS)
    .add_type_method(FileMonitor, cancel, !)
    .add_type_method(FileMonitor, is_cancelled)
    .method("on_file_changed!", [](FileMonitor& self, jl_value_t* task){
        self.on_file_changed([](FileMonitor& self, FileMonitorEvent event, const FileDescriptor& file_self, const FileDescriptor& file_other, jl_value_t* task){
            jl_safe_call("FileMonitor::on_file_changed", task,
                         jlcxx::box<FileMonitor&>(self),
                         jlcxx::box<FileMonitorEvent>(event),
                         jl_box_voidpointer(file_self.get_internal()),
                         jl_box_voidpointer(file_other.get_internal())
            );
        }, task);
    })
    ;
}
