module;
#include <windows.h>
#include <string>
#include <system_error>
export module null.sdk:memory.resource;

import :utils.logger;
import :memory.pe_image;

export namespace memory {
	struct resource_t {
	public:
		pe_image_t parent_module{ };
		std::string name{ }, type{ };

		HRSRC resource_handle{ };
		HGLOBAL resource_data{ };
		void* locked_data{ };
		size_t locked_data_size{ };

	public:
		resource_t() { }
		resource_t(std::string_view _name, std::string_view _type) : name{ _name }, type{ _type } { }
		resource_t(std::string_view _name, std::string_view _type, const pe_image_t& _parent_module) : parent_module{ _parent_module }, name{ _name }, type{ _type } { }

	public:
		bool empty() const { return !resource_handle || !resource_data || !locked_data; }

		//@todo: P0847
		auto& load() {
			if(!empty()) return *this;

			if(!(resource_handle = FindResourceA(parent_module.base_address, name.data(), type.data())))
				utils::logger(utils::e_log_type::warning, "cant find[type '{}'][name '{}'] resource.Error: '{}'[{}]", type, name, std::system_category().message(GetLastError()), GetLastError());

			if(!(resource_data = LoadResource(parent_module.base_address, resource_handle)))
				utils::logger(utils::e_log_type::warning, "cant load [type '{}'] [name '{}'] resource. Error: '{}' [{}]", type, name, std::system_category().message(GetLastError()), GetLastError());

			if(!(locked_data_size = SizeofResource(parent_module.base_address, resource_handle)))
				utils::logger(utils::e_log_type::warning, "cant get size [type '{}'] [name '{}'] resource. Error: '{}' [{}]", type, name, std::system_category().message(GetLastError()), GetLastError());

			if(!(locked_data = LockResource(resource_data)))
				utils::logger(utils::e_log_type::warning, "cant lock [type '{}'] [name '{}'] resource. Error: '{}' [{}]", type, name, std::system_category().message(GetLastError()), GetLastError());

			return *this;
		}

	public:
		operator bool() const { return !empty(); }
	};

	template <typename cast_t>
	struct resource_cast_t {
		static cast_t cast(const resource_t& resource) { return cast_t{ }; }
	};

	template <typename string_t>
	struct resource_cast_t<std::basic_string<string_t>> {
		static std::basic_string<string_t> cast(const resource_t& resource) { return std::basic_string<string_t>{ (string_t*)resource.locked_data, (string_t*)resource.locked_data + resource.locked_data_size }; }
	};
}