#pragma once
#include <Windows.h>
#include <string>
#include <utils/memory/pe_image.h>

namespace memory {
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
		resource_t(const std::string_view& _name, const std::string_view& _type, const pe_image_t& _parent_module = { GetModuleHandleA(nullptr) }) : parent_module{ _parent_module }, name{ _name }, type{ _type } { }

	public:
		bool empty() const { return !resource_handle || !resource_data || !locked_data; }
		
		template <typename self_t> auto&& load(this self_t&& self);

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

#include <utils/memory/resource/resource.inl>