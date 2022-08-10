#pragma once
#include <utils/memory/address.h>

namespace memory {
    struct pe_image_t {
    public:
        address_t base_address{ };

    public:
        PIMAGE_DOS_HEADER dos_header() { return base_address.cast<PIMAGE_DOS_HEADER>(); }
        PIMAGE_NT_HEADERS nt_headers() { return address_t{ base_address }.offset({ dos_header()->e_lfanew }).cast<PIMAGE_NT_HEADERS>(); }
    };
}