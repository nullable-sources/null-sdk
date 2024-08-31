#include "null-sdk.h"
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace ntl::mem {
    c_module& c_module::self() {
        static c_module self(pe_image_t{ (HMODULE)&__ImageBase });
        return self;
    }

    c_module* c_module::find_stored_module(std::string_view name) {
        if(auto found = std::ranges::find(stored_modules, name, &c_module::name); found != stored_modules.end()) return *found;
        return nullptr;
    }

    resource_t* c_module::find_resource(std::string_view name, std::string_view type) {
        auto found = std::ranges::find_if(resources, [&](const resource_t& resource) { return resource.name == name && (type.empty() || resource.type == type); });
        return found != resources.end() ? &(*found) : nullptr;
    }

    c_dll::i_export* c_dll::find_stored_export(std::string_view _name) {
        if(auto found = std::ranges::find(stored_exports, name, &i_export::name); found != stored_exports.end()) return (*found);
        return nullptr;
    }

    address_t c_dll::get_export(std::string_view _name) {
        if(i_export* found = find_stored_export(_name)) return (address_t)(*found);
        return load_export(_name);
    }

    address_t c_dll::load_export(std::string_view _name) {
        return (std::uintptr_t)GetProcAddress(pe_image.base_address.cast<HMODULE>(), _name.data());
    }
}