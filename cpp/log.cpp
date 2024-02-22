#include "../mousetrap_julia_binding.hpp"

// ### LOG

void implement_log(jlcxx::Module& module)
{
    define_enum_in(module, LogLevel);
    module.add_enum_value(LogLevel, LOG_LEVEL, DEBUG);
    module.add_enum_value(LogLevel, LOG_LEVEL, INFO);
    module.add_enum_value(LogLevel, LOG_LEVEL, WARNING);
    module.add_enum_value(LogLevel, LOG_LEVEL, CRITICAL);
    module.add_enum_value(LogLevel, LOG_LEVEL, FATAL);

    module.set_const("MOUSETRAP_DOMAIN", jl_box_string("Mousetrap"));
    module.set_const("MOUSETRAP_JULIA_DOMAIN", jl_box_string("Mousetrap.jl"));

    module.method("log_debug", [](const std::string& message, LogDomain domain){
        log::debug(message, domain);
    });

    module.method("log_info", [](const std::string& message, LogDomain domain){
        log::info(message, domain);
    });

    module.method("log_warning", [](const std::string& message, LogDomain domain){
        log::warning(message, domain);
    });

    module.method("log_critical", [](const std::string& message, LogDomain domain){
        log::critical(message, domain);
    });

    module.method("log_fatal", [](const std::string& message, LogDomain domain){
        log::fatal(message, domain);
    });

    module.method("log_set_surpress_debug", [](LogDomain domain, bool b)
    {
        log::set_surpress_debug(domain, b);
    });

    module.method("log_set_surpress_info", [](LogDomain domain, bool b)
    {
        log::set_surpress_info(domain, b);
    });

    module.method("log_get_surpress_debug", [](LogDomain domain)
    {
        return log::get_surpress_debug(domain);
    });

    module.method("log_get_surpress_info", [](LogDomain domain)
    {
        return log::get_surpress_info(domain);
    });

    module.method("log_set_file", [](const std::string& path) -> bool {
        return log::set_file(path);
    });

    /*
    module.method("log_reset_file_formatting_function", [](){
       log::reset_file_formatting_function();
    });

    module.method("log_set_file_formatting_function", [](jl_value_t* task){
        log::set_file_formatting_function([](const std::string& message, const std::map<std::string, std::string>& fields){

            jl_gc_enable();

            static auto* dict_ctor = jl_eval_string("Dict{String, String}");
            static auto* setindex = jl_get_function(jl_base_module, "setindex!");

            auto* message_jl = jl_box_string(message);
            auto* dict = jl_calln(dict_ctor)
            for (auto& pair : fields)
                jl_calln(setindex, dict, jl_box_string(pair.first), jl_box_string(pair.second));

            auto* res = jl_safe_call("log::formatting_function", task, message, dict);

            std::string out;
            if (res != nullptr)
                out = jl_unbox_string(res);

            jl_gc_enable();
            return out;
        }, task);
    });
    */
}