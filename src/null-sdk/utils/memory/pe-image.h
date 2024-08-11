#pragma once
#include "address.h"

namespace memory {
    struct pe_image_t {
    public:
        address_t base_address{ };

    public:
        inline constexpr PIMAGE_DOS_HEADER dos_header() { return base_address.cast<PIMAGE_DOS_HEADER>(); }
        inline PIMAGE_NT_HEADERS nt_headers() { return base_address.offseted(dos_header()->e_lfanew).cast<PIMAGE_NT_HEADERS>(); }
    };
}