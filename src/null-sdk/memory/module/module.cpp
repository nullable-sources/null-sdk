#include "module.h"
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace ntl {
    c_module& c_module::self() {
        static c_module self(pe_image_t((HMODULE)&__ImageBase));
        return self;
    }

    resource_t* c_module::find_resource(std::string_view name, std::string_view type) {
        auto found = std::ranges::find_if(resources, [&](const resource_t& resource) { return resource.name == name && (type.empty() || resource.type == type); });
        return found != resources.end() ? &(*found) : nullptr;
    }

    address_t c_dll::get_export(std::string_view _name) {
        return (std::uintptr_t)GetProcAddress(pe_image.base_address.cast<HMODULE>(), _name.data());
    }
}