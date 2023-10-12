#include "null-sdk.h"
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace memory {
	c_module& c_module::self() {
		static c_module self{ { (HMODULE)&__ImageBase } };
		return self;
	}

	c_module* c_module::find_stored_module(std::string_view name) {
		if(auto finded{ std::ranges::find_if(stored_modules, [&](c_module* module) { return module->name == name; }) }; finded != stored_modules.end()) return *finded;
		return nullptr;
	}

	resource_t* c_module::find_resource(std::string_view name, std::string_view type) {
		auto finded{ std::ranges::find_if(resources, [&](const resource_t& resource) { return resource.name == name && (type.empty() || resource.type == type); }) };
		return finded != resources.end() ? &(*finded) : nullptr;
	}

	c_dll::i_export* c_dll::find_stored_export(std::string_view _name) {
		if(auto finded{ std::ranges::find_if(stored_exports, [&](i_export* _export) { return _export->name == _name; }) }; finded != stored_exports.end()) return (*finded);
		return nullptr;
	}

	address_t c_dll::get_export(std::string_view _name) {
		if(i_export* finded{ find_stored_export(_name) }) return (address_t)(*finded);
		return load_export(_name);
	}

	address_t c_dll::load_export(std::string_view _name) {
		return address_t{ (std::uintptr_t)GetProcAddress(pe_image.base_address.cast<HMODULE>(), _name.data()) };
	}
}