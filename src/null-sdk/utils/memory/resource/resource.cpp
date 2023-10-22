#include "null-sdk.h"

namespace memory {
	resource_t::resource_t(std::string_view _name, std::string_view _type) : name(_name), type(_type) {
		parent_module = c_module::self().pe_image;
	}
}