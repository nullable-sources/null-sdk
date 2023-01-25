#include <null-sdk.h>

namespace null::sdk {
	void resource_t::load() {
		resource = FindResourceA(hmodule, name.data(), type.data());
		data = LoadResource(hmodule, resource);
		size = SizeofResource(hmodule, resource);
		locked_data = LockResource(data);
	}
}