#pragma once
#include <Windows.h>

#include "address.h"

namespace ntl {
    struct pe_image_t {
    public:
        address_t base_address{ };

    public:
        inline constexpr pe_image_t() { }
        template <is_allowed_address_construct value_t>
        inline constexpr pe_image_t(value_t value) : base_address(value) { }

    public:
        template <typename cast_t> inline constexpr cast_t cast() const { return base_address.cast<cast_t>(); }

    public:
        inline constexpr PIMAGE_DOS_HEADER dos_header() { return base_address.cast<PIMAGE_DOS_HEADER>(); }
        inline PIMAGE_NT_HEADERS nt_headers() { return base_address.offseted(dos_header()->e_lfanew).cast<PIMAGE_NT_HEADERS>(); }
        inline PIMAGE_SECTION_HEADER image_section_header() {
            static constexpr std::uintptr_t optional_header_offset = offsetof(IMAGE_NT_HEADERS, OptionalHeader);
            PIMAGE_NT_HEADERS nt_header = nt_headers();
            return address_t(nt_header).offseted({ optional_header_offset, nt_header->FileHeader.SizeOfOptionalHeader }).cast<PIMAGE_SECTION_HEADER>();
        }

    public:
        template <is_allowed_address_construct cast_t> inline constexpr operator cast_t() const { return cast<cast_t>(); }
        inline constexpr operator bool() const { return base_address; }
    };
}