#include "../mousetrap_julia_binding.hpp"

// ### CLIPBOARD

void implement_clipboard(jlcxx::Module& module)
{
    auto clipboard = module.add_type(Clipboard)
    .constructor([](void* internal) -> Clipboard*{
        return new Clipboard((detail::ClipboardInternal*) internal);
    }, USE_FINALIZERS)
    .add_type_method(Clipboard, contains_string)
    .add_type_method(Clipboard, contains_image)
    .add_type_method(Clipboard, contains_file)
    .add_type_method(Clipboard, is_local)
    .method("set_string", [](Clipboard& self, const std::string& string){
        self.set_string(string);
    })
    .method("get_string", [](Clipboard& self, jl_value_t* task){
        self.get_string([](const Clipboard& self, const std::string& result, jl_value_t* task){
            jl_safe_call("Clipboard::get_string", jlcxx::box<const Clipboard&>(self), jlcxx::box<const std::string&>(result));
        }, task);
    })
    .method("set_image", [](Clipboard& self, Image& image){
        self.set_image(image);
    })
    .method("get_image", [](Clipboard& self, jl_value_t* task){
        self.get_image([](const Clipboard& self, const Image& result, jl_value_t* task){
            jl_safe_call("Clipboard::get_image", jlcxx::box<const Clipboard&>(self), jlcxx::box<const Image&>(result));
        }, task);
    })
    .method("set_file", [](Clipboard& self, FileDescriptor& file){
        self.set_file(file);
    })
    ;
}