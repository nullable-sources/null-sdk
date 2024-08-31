#pragma once
#include <Windows.h>
#include <string>

#include "../pe-image.h"

namespace ntl::mem {
    struct resource_t {
    public:
        pe_image_t parent_module{ };
        std::string name{ }, type{ };

        HRSRC resource_handle{ };
        HGLOBAL resource_data{ };
        void* locked_data{ };
        size_t locked_data_size{ };

    public:
        resource_t() { }
        resource_t(std::string_view _name, std::string_view _type);
        resource_t(std::string_view _name, std::string_view _type, const pe_image_t& _parent_module) : parent_module(_parent_module), name(_name), type(_type) { }

    public:
        inline bool empty() const { return !resource_handle || !resource_data || !locked_data; }

        auto&& load(this auto&& self);

    public:
        inline operator bool() const { return !empty(); }
    };

    template <typename cast_t>
    struct resource_cast_t {
        static inline cast_t cast(const resource_t& resource) { return cast_t{ }; }
    };

    template <>
    struct resource_cast_t<std::vector<std::uint8_t>> {
        static inline std::vector<std::uint8_t> cast(const resource_t& resource) { return std::vector<std::uint8_t>((std::uint8_t*)resource.locked_data, (std::uint8_t*)resource.locked_data + resource.locked_data_size); }
    };

    template <typename string_t>
    struct resource_cast_t<std::basic_string<string_t>> {
        static inline std::basic_string<string_t> cast(const resource_t& resource) { return std::basic_string<string_t>((string_t*)resource.locked_data, (string_t*)resource.locked_data + resource.locked_data_size); }
    };
}

#include "resource.inl"