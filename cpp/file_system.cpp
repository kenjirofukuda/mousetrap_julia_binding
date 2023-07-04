#include "../mousetrap_julia_binding.hpp"

// ### FILE SYSTEM

void implement_file_system(jlcxx::Module& module)
{
    module.method("create_file_at!", [](const FileDescriptor& destination, bool replace) {
        return file_system::create_file_at(destination, replace);
    });
    module.method("create_directory_at!", [](const FileDescriptor& destination){
        return file_system::create_directory_at(destination);
    });
    module.method("delete_at!", [](const FileDescriptor& destination){
        return file_system::delete_at(destination);
    });
    module.method("copy!", [](const FileDescriptor& from, const FileDescriptor& to, bool allow_overwrite, bool make_backup, bool follow_symlinks){
        return file_system::copy(from, to, allow_overwrite, make_backup, follow_symlinks);
    });
    module.method("move!", [](const FileDescriptor& from, const FileDescriptor& to, bool allow_overwrite, bool make_backup, bool follow_symlinks){
        return file_system::move(from, to, allow_overwrite, make_backup, follow_symlinks);
    });
    module.method("move_to_trash!", [](const FileDescriptor& file){
        return file_system::move_to_trash(file);
    });
    module.method("open_file", [](const FileDescriptor& file){
        file_system::open_file(file);
    });
    module.method("open_url", [](const std::string& url){
        file_system::open_url(url);
    });
    module.method("show_in_file_explorer", [](const FileDescriptor& file){
        file_system::show_in_file_explorer(file);
    });
}