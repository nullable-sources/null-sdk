#pragma once
#include <Windows.h>
#include "address.h"

namespace memory {
    struct pe_image_t {
    public:
        address_t base_address{ };

    public:
        inline constexpr pe_image_t() { }
        template <is_not_sdk_address_t value_t>
        inline constexpr pe_image_t(value_t value) : base_address(value) { }

    public:
        template <typename cast_t> inline constexpr cast_t cast() const { return base_address.cast<cast_t>(); }

    public:
        inline constexpr PIMAGE_DOS_HEADER dos_header() { return base_address.cast<PIMAGE_DOS_HEADER>(); }
        inline PIMAGE_NT_HEADERS nt_headers() { return base_address.offseted(dos_header()->e_lfanew).cast<PIMAGE_NT_HEADERS>(); }

    public:
        template <typename cast_t> inline constexpr operator cast_t() const { return cast<cast_t>(); }
        inline constexpr operator bool() const { return base_address; }
    };
}