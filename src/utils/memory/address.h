#pragma once
#include <utils/win/win.h>

//@credits: thx lagcomp/csgo_sdk for this superior code
namespace memory {
    struct address_t {
    public:
        std::uintptr_t address{ };

    public:
        address_t() { }
        address_t(auto value) : address((std::uintptr_t)value) { }

    public:
        template <typename cast_t> cast_t cast() { return (cast_t)address; }

        address_t& deref() { address = *cast<std::uintptr_t*>(); return *this; }

        address_t& offset(const std::intptr_t& offset) { address += offset; return *this; }
        address_t& offset(const std::vector<std::intptr_t>& offsets) { std::ranges::for_each(offsets, [&](const std::intptr_t& _offset) { address += _offset; }); return *this; }

        address_t& jump(const std::intptr_t& _offset) {
            address_t return_address{ address_t{ *this }.offset(_offset) };
            return return_address.offset({ address_t{ return_address }.deref().cast<std::uint32_t>(), sizeof(std::uint32_t) });
        }

    public:
        template <typename cast_t> operator cast_t() { return cast<cast_t>(); }
        operator bool() { return address; }
    };

    struct vtable_t : private address_t {
    public:
        std::uintptr_t* get() { return *cast<std::uintptr_t**>(); }
        std::uintptr_t operator[](int idx) { return get()[idx]; }

        template <typename funtion_t>
        funtion_t function(int index) {
            return (funtion_t)(get()[index]);
        }
    };
}