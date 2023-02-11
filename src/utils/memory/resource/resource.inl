#include <null-sdk.h>

namespace memory {
	template <typename self_t>
	auto&& resource_t::load(this self_t&& self) {
		if(!self.empty()) return self;

		if(!(self.resource_handle = FindResourceA(self.parent_module.base_address, self.name.data(), self.type.data())))
			throw std::runtime_error{ std::format("cant find [type '{}'] [name '{}'] resource. Error: '{}' [{}]", self.type, self.name, std::system_category().message(GetLastError()), GetLastError()) };
		
		if(!(self.resource_data = LoadResource(self.parent_module.base_address, self.resource_handle)))
			throw std::runtime_error{ std::format("cant load [type '{}'] [name '{}'] resource. Error: '{}' [{}]", self.type, self.name, std::system_category().message(GetLastError()), GetLastError()) };

		if(!(self.locked_data_size = SizeofResource(self.parent_module.base_address, self.resource_handle)))
			throw std::runtime_error{ std::format("cant get size [type '{}'] [name '{}'] resource. Error: '{}' [{}]", self.type, self.name, std::system_category().message(GetLastError()), GetLastError()) };

		if(!(self.locked_data = LockResource(self.resource_data)))
			throw std::runtime_error{ std::format("cant lock [type '{}'] [name '{}'] resource. Error: '{}' [{}]", self.type, self.name, std::system_category().message(GetLastError()), GetLastError()) };

		return self;
	}
}