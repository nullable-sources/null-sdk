#pragma once
#include <Windows.h>
#include <string>

namespace null::sdk {
	struct resource_t {
	public:
		HMODULE hmodule{ };
		std::string name{ }, type{ };

		HRSRC resource{ };
		HGLOBAL data{ };
		void* locked_data{ };
		size_t size{ };

	public:
		resource_t() { }
		resource_t(const std::string_view& _name, const std::string_view& _type, HMODULE _hmodule = GetModuleHandle(NULL)) : name{ _name }, type{ _type }, hmodule{ _hmodule } {
			load();
		}

	public:
		void load();
	};
}