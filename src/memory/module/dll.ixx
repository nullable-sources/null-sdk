module;
#include <windows.h>
#include <vector>
#include <string>
export module null.sdk:memory.module.dll;

import :utils.logger;
import :memory.module;
import :memory.address;
import :memory.pe_image;

export namespace memory {
    class c_dll : public c_module {
    public:
        class i_export : public address_t {
        public:
            c_dll* module{ };
            std::string name{ };

        public:
            i_export() { }
            i_export(const address_t& _address) : address_t{ _address } { }
            i_export(const std::string_view& _module_name, const std::string_view& _name) : name{ _name } {
                if(module = (c_dll*)find_stored_module(_module_name)) {
                    if(i_export * finded{ module->find_stored_export(_name) }) *this = *finded;
                    else {
                        address = module->get_export(_name);
                        module->stored_exports.push_back(this);
                    }
                } else {
                    address = c_dll{ _module_name, false }.get_export(name);
                }
            }
            i_export(c_dll* _module, const std::string_view& _name) : module{ _module }, name{ _name }, address_t{ _module->get_export(_name) } {
                if(i_export * finded{ module->find_stored_export(_name) }) *this = *finded;
                else module->stored_exports.push_back(this);
            }
        };

        template <typename, typename = void>
        class c_export;

        struct stdcall_t { };
        struct cdecl_t { };
        struct fastcall_t { };

        template <typename conversion_t, typename return_t, typename ...args_t>
        struct calling_conversion_t {
            using prototype_t = return_t(args_t...);
        };

        template <typename return_t, typename ...args_t>
        struct calling_conversion_t<stdcall_t, return_t, args_t...> {
            using prototype_t = return_t(__stdcall*)(args_t...);
        };

        template <typename return_t, typename ...args_t>
        struct calling_conversion_t<cdecl_t, return_t, args_t...> {
            using prototype_t = return_t(__cdecl*)(args_t...);
        };

        template <typename return_t, typename ...args_t>
        struct calling_conversion_t<fastcall_t, return_t, args_t...> {
            using prototype_t = return_t(__fastcall*)(args_t...);
        };

        template <typename return_t, typename ...args_t>
        class c_export<return_t(args_t...)> : public i_export {
        public: using i_export::i_export;
        	using prototype_t = calling_conversion_t<stdcall_t, return_t, args_t...>::prototype_t;

        public:
            return_t operator()(args_t... args) {
                if(module && !address) { address = module->load_export(name); }
                if(!address) utils::logger.log(utils::e_log_type::warning, "'{}' export address == nullptr", name.empty() ? "unknown" : name);
                return ((prototype_t)address)(args...);
            }
        };

        template <typename call_conv_t, typename return_t, typename ...args_t>
        class c_export<call_conv_t, return_t(args_t...)> : public i_export {
        public: using i_export::i_export;
        	using prototype_t = calling_conversion_t<call_conv_t, return_t, args_t...>::prototype_t;

        public:
            return_t operator()(args_t... args) {
                if(module && !address) { address = module->load_export(name); }
                if(!address) utils::logger.log(utils::e_log_type::warning, "'{}' export address == nullptr", name.empty() ? "unknown" : name);
                return ((prototype_t)address)(args...);
            }
        };

    public:
        std::vector<i_export*> stored_exports{ };

    public:
        c_dll(const std::string_view& _name, const bool& store = true) : c_module{ _name, store } { }

    public:
        virtual i_export* find_stored_export(const std::string_view& _name) {
            if(const auto& finded{ std::ranges::find_if(stored_exports, [&](i_export* _export) { return _export->name == _name; }) }; finded != stored_exports.end()) return (*finded);
            return nullptr;
        }

        virtual address_t get_export(const std::string_view& _name) {
            if(i_export* finded{ find_stored_export(_name) }) return (address_t)(*finded);
            return load_export(_name);
        }

        virtual address_t load_export(const std::string_view& _name) {
	        return address_t{ (std::uintptr_t)GetProcAddress(pe_image.base_address.cast<HMODULE>(), _name.data()) };
        }
    };
}