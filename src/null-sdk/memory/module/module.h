#pragma once
#include "../../utils/logger/logger.h"
#include "../resource/resource.h"

namespace ntl {
    class c_module {
    public:
        //@note: i don't fucking want to rewrite it all
        static c_module& self();

    public:
        pe_image_t pe_image{ };
        std::string name{ };

        std::vector<resource_t> resources{ };

    public:
        c_module() { }
        c_module(pe_image_t _pe_image) : pe_image(_pe_image) { }
        c_module(std::string_view _name) : name(_name) {
            pe_image = pe_image_t((std::uintptr_t)GetModuleHandleA(name.data()));
            if(!pe_image.base_address) sdk::logger(sdk::e_log_type::warning, "cant get '{}' module.", name);
        }

    public:
        auto&& load_resources(this auto&& self);
        resource_t* find_resource(std::string_view name, std::string_view type = { }); //@note: if type empty, will be returned first resource with this name
    };

    class c_dll : public c_module {
    public: using c_module::c_module;
        class i_export : public address_t {
        public:
            c_dll* module{ };
            std::string name{ };

        public:
            i_export() { }
            i_export(const address_t& _address) : address_t(_address) { }
            i_export(std::string_view _module_name, std::string_view _name)
                : name(_name), address_t(c_dll(_module_name).get_export(name)) { }
            i_export(c_dll* _module, std::string_view _name)
                : module(_module), name(_name), address_t(_module->get_export(_name)) { }
        };

        template <typename>
        class c_export;

        template <typename return_t, typename ...args_t>
        class c_export<return_t(args_t...)> : public i_export {
        public: using i_export::i_export;
        public:
            using prototype_t = return_t(__stdcall*)(args_t...);

        public:
            inline return_t operator()(args_t... args) {
                if(module && !address) { address = module->get_export(name); }
                if(!address) sdk::logger(sdk::e_log_type::warning, "'{}' export address == nullptr", name.empty() ? "unknown" : name);
                return ((prototype_t)address)(std::forward<args_t>(args)...);
            }
        };

    public:
        std::vector<i_export*> stored_exports{ };

    public:
        virtual address_t get_export(std::string_view _name);
    };
}

#include "module.inl"