#pragma once
#include <utils/memory/pe_image.h>

namespace memory {
    class c_module {
    public:
        static inline std::vector<c_module*> stored_modules{ };

        static c_module* find_stored_module(std::string_view name) {
            if(auto finded = std::ranges::find_if(stored_modules, [&](c_module* module) { return module->name == name; }); finded != stored_modules.end()) return *finded;
            return nullptr;
        }

    public:
        class i_export : public address_t {
        public:
            c_module* module{ };
            std::string name{ };

        public:
            i_export(const address_t& _address) : address_t{_address} { }
            i_export(std::string_view _module_name, std::string_view _name) : i_export(find_stored_module(_module_name), _name) { }
            i_export(c_module* _module, std::string_view _name) : module(_module), name(_name), address_t{ _module->get_export(_name) } {
                if(i_export* finded = module->find_stored_export(_name)) *this = *finded;
                else module->stored_exports.push_back(this);
            }
        };

        template<typename>
        class c_export;

        template <typename return_t, typename ...args_t>
        class c_export<return_t(args_t...)> : public i_export {
        public: using i_export::i_export;
            typedef return_t(*prototype_t)(args_t...);

        public:
            return_t operator()(args_t... args) {
                if(!address) throw std::runtime_error{ std::format("'{}' export address == nullptr", name.empty() ? "unknown" : name) };
                return ((prototype_t)address)(args...);
            }
        };

    public:
        std::string name{ };
        pe_image_t pe_image{ };

        std::vector<i_export*> stored_exports{ };

    public:
        c_module(std::string_view _name) : name(_name) {
            if(c_module* finded = find_stored_module(_name)) {
                *this = *finded;
            } else {
                pe_image = pe_image_t{ (std::uintptr_t)GetModuleHandleA(name.data()) };
                if(!pe_image.base_address) throw std::runtime_error{ std::format("cant get '{}' module", name) };
                stored_modules.push_back(this);
            }
        }

    public:
        i_export* find_stored_export(std::string_view _name) {
            if(auto finded = std::ranges::find_if(stored_exports, [&](i_export* _export) { return _export->name == _name; }); finded != stored_exports.end()) return (*finded);
            return nullptr;
        }

        address_t get_export(std::string_view _name) {
            if(i_export* finded = find_stored_export(_name)) return (address_t)(*finded);
            return address_t{ (std::uintptr_t)GetProcAddress(pe_image.base_address.cast<HMODULE>(), _name.data()) };
        }
    };
}