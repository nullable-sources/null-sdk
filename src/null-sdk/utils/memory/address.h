#pragma once
#include <cstdint>
#include <vector>
#include <ranges>
#include <algorithm>

//@credits: thx lagcomp/csgo_sdk for this superior code
namespace memory {
    struct address_t {
    public:
        std::uintptr_t address{ };

    public:
        inline constexpr address_t() { }
        inline constexpr address_t(const auto& value) : address((std::uintptr_t)value) { }

    public:
        template <typename cast_t> inline constexpr cast_t cast() const { return (cast_t)address; }

        template <typename self_t> inline auto&& deref(this self_t&& self, int steps = 1) { for(; steps >= 1; steps--) self.address = *self.cast<std::uintptr_t*>(); return self; }

        template <typename self_t> inline auto&& offset(this self_t&& self, std::intptr_t offset) { self.address += offset; return self; }
        template <typename self_t> inline auto&& offset(this self_t&& self, const std::vector<std::intptr_t>& offsets) { std::ranges::for_each(offsets, [&](std::intptr_t _offset) { self.address += _offset; }); return self; }

        template <typename self_t> inline auto&& jump(this self_t&& self, std::intptr_t offset) {
            address_t return_address = self.offseted(offset);
            self.address = return_address.offset({ return_address.derefed().cast<std::int32_t>(), sizeof(std::uint32_t) });
            return self;
        }

        inline address_t derefed(int steps = 1) const { return address_t(*this).deref(steps); }
        inline address_t offseted(std::intptr_t offset) const { return address_t(*this).offset(offset); }
        inline address_t offseted(const std::vector<std::intptr_t>& offsets) const { return address_t(*this).offset(offsets); }
        inline address_t jumped(std::intptr_t offset) const { return address_t(*this).jump(offset); }

    public:
        template <typename cast_t> inline constexpr operator cast_t() const { return cast<cast_t>(); }
        inline constexpr operator bool() const { return address; }
    };

    struct vtable_t {
    public:
        template <std::size_t, typename>
        struct func_t;

        template <std::size_t index, typename return_t, typename ...args_t>
        class func_t<index, return_t(args_t...)> {
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

    public:
        template <typename self_t>
        static inline constexpr std::uintptr_t* get(self_t self) { return *(std::uintptr_t**)self; }

        template <typename self_t, typename prototype_t = memory::address_t>
        static inline constexpr prototype_t get(self_t self, std::size_t index) { return (prototype_t)(get(self)[index]); }
    };
}