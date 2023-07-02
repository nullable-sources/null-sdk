#include <null-sdk.h>

namespace memory {
	auto&& resource_t::load(this auto&& self) {
		if(!self.empty()) return self;

		if(!(self.resource_handle = FindResourceA(self.parent_module.base_address, self.name.data(), self.type.data())))
			utils::logger(utils::e_log_type::warning, "cant find[type '{}'][name '{}'] resource.Error: '{}'[{}]", self.type, self.name, std::system_category().message(GetLastError()), GetLastError());
		
		if(!(self.resource_data = LoadResource(self.parent_module.base_address, self.resource_handle)))
			utils::logger(utils::e_log_type::warning, "cant load [type '{}'] [name '{}'] resource. Error: '{}' [{}]", self.type, self.name, std::system_category().message(GetLastError()), GetLastError());

		if(!(self.locked_data_size = SizeofResource(self.parent_module.base_address, self.resource_handle)))
			utils::logger(utils::e_log_type::warning, "cant get size [type '{}'] [name '{}'] resource. Error: '{}' [{}]", self.type, self.name, std::system_category().message(GetLastError()), GetLastError());

		if(!(self.locked_data = LockResource(self.resource_data)))
			utils::logger(utils::e_log_type::warning, "cant lock [type '{}'] [name '{}'] resource. Error: '{}' [{}]", self.type, self.name, std::system_category().message(GetLastError()), GetLastError());

		return self;
	}
}