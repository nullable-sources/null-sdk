module;
#include <windows.h>
#include <string_view>
#include <string>
#include <format>
#include <vector>
#include <ranges>
export module null.sdk:memory.win_module;

import :utils.logger;
import :memory.resource;
import :memory.pe_image;

extern "C" IMAGE_DOS_HEADER __ImageBase;

export namespace memory {
    class c_module {
    public:
        //@note: i don't fucking want to rewrite it all
        static c_module& self() {
			static c_module self{ { (HMODULE)&__ImageBase } };
			return self;
        }

    public:
        pe_image_t pe_image{ };

        std::vector<resource_t> resources{ };

    public:
		c_module() : c_module{ self() } { }
        c_module(const pe_image_t& _pe_image) : pe_image{ _pe_image } { }
        c_module(const std::string_view& name) {
			pe_image = pe_image_t{ (std::uintptr_t)GetModuleHandleA(name.data()) };
			if(!pe_image.base_address) utils::logger.log(utils::e_log_type::warning, "cant get '{}' module.", name);
        }

    public:
		//@note: if type empty, will be returned first resource with this name
        resource_t* find_resource(const std::string_view& name, const std::string_view& type = { }) {
			const auto& finded{ std::ranges::find_if(resources, [&](const resource_t& resource) { return resource.name == name && (type.empty() || resource.type == type); }) };
			return finded != resources.end() ? &(*finded) : nullptr;
        }

        auto& load_resources() {
			static const auto to_string{
			[](const char* name) {
				return
					(std::uint64_t)name & 0xFFFF0000
					? std::string{ name } | std::views::transform([](const char& c) { return std::tolower(c); }) | std::ranges::to<std::string>()
					: std::format("#{}", (std::uint16_t)name); //@note: https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-findresourcea#remarks
			}
			};

			static const auto enum_names{
				[](HMODULE module, LPCSTR type, LPSTR name, LONG_PTR param) -> BOOL {
					std::vector<resource_t>* resources{ (std::vector<resource_t>*)param };
					resource_t new_resource{ to_string(name), to_string(type), { module } };

					//@note:	of course, you can clean up self.resources, but because of this you will have to reload previously loaded resources
					//			to be honest, i do not know what is more expensive in performance, and i somehow do not want to do tests, so let it be so
					if(const auto& finded{ std::ranges::find_if(*resources, [&](const resource_t& resource) { return resource.name == new_resource.name && resource.type == new_resource.type; }) };
						finded == resources->end()) resources->push_back(new_resource);
					return true;
				}
			};

			static const auto enum_types{
				[](HMODULE module, LPSTR type, LONG_PTR param) -> BOOL {
					EnumResourceNamesA(module, type, (ENUMRESNAMEPROCA)enum_names, param);
					return true;
				}
			};

			EnumResourceTypesA(pe_image.base_address, (ENUMRESTYPEPROCA)enum_types, (LONG_PTR)&resources);
			return *this;
        }
    };
}