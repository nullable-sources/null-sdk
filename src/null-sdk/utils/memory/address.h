#pragma once
#include "../win/win.h"

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

    struct vtable_t : private address_t {
    public:
        inline constexpr std::uintptr_t* get() { return *cast<std::uintptr_t**>(); }
        inline std::uintptr_t operator[](int idx) { return get()[idx]; }

        template <typename funtion_t>
        inline funtion_t function(int index) {
            return (funtion_t)(get()[index]);
        }
    };
}