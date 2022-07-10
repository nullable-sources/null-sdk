#pragma once
#include <utility>
#include <vector>
#include <format>
#include <stdexcept>
#include <functional>
#include <Windows.h>

namespace utils::wrapper::dll {
    class i_dll {
    public:
        class i_method {
        public:
            i_dll* parent{ };
            std::string name{ };

        public:
            i_method(i_dll* _parent, std::string _name) : parent(_parent), name(_name) {
                parent->wrapped_methods.push_back(this);
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
                method = (method_t)GetProcAddress(parent->module, name.c_str());
                return method != nullptr;
            }

            return_t operator()(args_t... args) { return method(args...); }
        };

    public:
        std::string name{ };
        HMODULE module{ };

        std::vector<i_method*> wrapped_methods{ };

    public:
        void load() {
            module = GetModuleHandleA(name.c_str());
            if(!module) throw std::runtime_error(std::format("cant get '{}' module", name));

            std::ranges::for_each(wrapped_methods, [](i_method* method) {
                if(!method->load()) throw std::runtime_error(std::format("cant load '{}' method", method->name));
                });
        }
    };
}