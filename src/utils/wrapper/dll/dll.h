#pragma once
#include <utility>
#include <vector>
#include <format>
#include <stdexcept>
#include <functional>
#include <Windows.h>
#include <map>

namespace utils::wrapper::dll {
    class i_dll {
    public:
        static inline std::map<std::string, HMODULE> loaded_dlls{ };

    public:
        class i_method {
        public:
            static inline std::vector<i_method*> wrapped_methods{ };

        public:
            std::string dll{ }, name{ };

        public:
            i_method(i_dll* _dll, const std::string& _name) : i_method(_dll->name, _name) { }
            i_method(const std::string& _dll, const std::string& _name) : dll(_dll), name(_name) {
                if(i_method* finded = find()) {
                    *this = *finded;
                } else wrapped_methods.push_back(this);
            }

            i_method* find() {
                if(auto finded = std::ranges::find_if(wrapped_methods, [&](i_method* method) {
                    return method->name == name && method->dll == dll;
                    }); finded != wrapped_methods.end()) {
                    return *finded;
                }
                return nullptr;
            }

            virtual bool load() = 0;
        };

        template<typename>
        class c_method;

        template <typename return_t, typename ...args_t>
        class c_method<return_t(args_t...)> : public i_method {
        public:
            using i_method::i_method;

            typedef return_t(*method_t)(args_t...);
            method_t method{ };

        public:
            bool load() override {
                if(!loaded_dlls[dll]) i_dll{ dll }.load();
                if(c_method* finded = (c_method*)find(); finded && finded->method) {
                    method = finded->method;
                } else method = (method_t)GetProcAddress(loaded_dlls[dll], name.c_str());
                return method != nullptr;
            }

            return_t operator()(args_t... args) {
                if(!method && !load()) throw std::runtime_error(std::format("cant get '{}' method", name));
                return method(args...);
            }
        };

    public:
        std::string name{ };

    public:
        void load() {
            loaded_dlls[name] = GetModuleHandleA(name.c_str());
            if(!loaded_dlls[name]) throw std::runtime_error(std::format("cant get '{}' module", name));
        }
    };
}