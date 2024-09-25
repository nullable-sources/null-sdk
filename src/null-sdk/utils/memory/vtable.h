#pragma once
#include "address.h"

namespace ntl {
    struct vtable_t {
    public:
        template <std::size_t, typename>
        struct func_t;

        template <std::size_t index, typename return_t, typename ...args_t>
        struct func_t<index, return_t(args_t...)> {
        public:
            template <typename self_t>
            using prototype_t = return_t(__thiscall*)(self_t, args_t...);

        public:
            template <typename self_t>
            static inline prototype_t<self_t> get(self_t self) {
                return vtable_t::get<self_t, prototype_t<self_t>>(self, index);
            }

            template <typename self_t>
            static inline return_t call(self_t self, args_t... args) {
                return func_t::get(self)(self, std::forward<args_t>(args)...);
            }
        };

        struct copied_t {
        public:
            std::uintptr_t* original_ptr{ };
            std::vector<std::uintptr_t> vtable{ };

        public:
            template <typename instance_t>
            inline void override(instance_t instance) { *vtable_t::get_ptr(instance) = vtable.data(); }
            template <typename instance_t>
            inline void restore(instance_t instance) { *vtable_t::get_ptr(instance) = original_ptr; }

            inline void replace(std::size_t index, ntl::address_t function) { vtable[index] = function; }
            inline std::size_t size() { return vtable.size(); }
            inline bool empty() { return vtable.empty(); }
        };

    public:
        template <typename self_t>
        static inline std::uintptr_t** get_ptr(self_t self) { return (std::uintptr_t**)self; }
        template <typename self_t>
        static inline std::uintptr_t* get(self_t self) { return *get_ptr(self); }

        template <typename self_t, typename prototype_t = address_t>
        static inline prototype_t get(self_t self, std::size_t index) { return (prototype_t)(get(self)[index]); }

        template <typename self_t>
        static inline copied_t copy(self_t self, std::size_t methods_count) {
            copied_t copied_vtable{ };
            copied_vtable.original_ptr = get(self);

            for(std::size_t index : std::views::iota(0u, methods_count))
                copied_vtable.vtable.push_back(get(self, index));

            return copied_vtable;
        }
    };
}