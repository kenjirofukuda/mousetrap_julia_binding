#include "../mousetrap_julia_binding.hpp"

class GCSentinel
{
    private:
        mutable jl_value_t* _value;

    public:
        template<typename T>
        GCSentinel(T x)
            : _value((jl_value_t*) x)
        {
            //std::cout << "gc protecting: " << _value << std::endl;
            jlcxx::protect_from_gc(_value);
        }

        ~GCSentinel()
        {
            //std::cout << "gc unprotecting: " << _value << std::endl;
            jlcxx::unprotect_from_gc(_value);
        }

        /* implicit */ operator jl_value_t*() const
        {
            return _value;
        }
};

void toggle_notify(GCSentinel* attachment, GObject* host, bool last_ref)
{
    //std::cout << "detaching " << attachment << std::endl;
    delete attachment;
}

void attach_pointer_to(GObject* host, GCSentinel* attachment)
{
    g_object_add_toggle_ref(host, (GToggleNotify) toggle_notify, attachment);
    //std::cout << "attaching " << attachment << std::endl;
}

jl_value_t* gc_protect_aux(NativeObject host, jl_value_t* value)
{
    // TODO: possibly still leaks memory

    auto sentinel = new GCSentinel(value);
    attach_pointer_to(host, sentinel);
    return sentinel->operator jl_value_t*();
}