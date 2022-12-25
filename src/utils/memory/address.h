#pragma once
#include <utils/win/win.h>

//@credits: thx lagcomp/csgo_sdk for this superior code
namespace memory {
    struct address_t {
    public:
        std::uintptr_t address{ };

    public:
        address_t() { }
        address_t(const auto& value) : address{ (std::uintptr_t)value } { }

    public:
        template <typename cast_t> cast_t cast() const { return (cast_t)address; }

        address_t& deref(const int& steps = 1) { address = *cast<std::uintptr_t*>(); if(steps > 1) deref(steps - 1); return *this; }

        address_t& offset(const std::intptr_t& offset) { address += offset; return *this; }
        address_t& offset(const std::vector<std::intptr_t>& offsets) { std::ranges::for_each(offsets, [&](const std::intptr_t& _offset) { address += _offset; }); return *this; }

        address_t& jump(const std::intptr_t& _offset) {
            address_t return_address{ address_t{ *this }.offset(_offset) };
            return return_address.offset({ address_t{ return_address }.deref().cast<std::int32_t>(), sizeof(std::uint32_t) });
        }

    public:
        template <typename cast_t> operator cast_t() const { return cast<cast_t>(); }
        operator bool() const { return address; }
    };

    struct vtable_t : private address_t {
    public:
        std::uintptr_t* get() { return *cast<std::uintptr_t**>(); }
        std::uintptr_t operator[](const int& idx) { return get()[idx]; }

        template <typename funtion_t>
        funtion_t function(const int& index) {
            return (funtion_t)(get()[index]);
        }
    };
}