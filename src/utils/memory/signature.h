#pragma once
#include <utils/memory/module.h>

namespace memory {
    struct signature_t : address_t {
    public:
        pe_image_t pe_image{ };
        std::string signature{ };

        std::vector<std::int32_t> bytes{ };

    public:
        signature_t(const c_module& module, std::string_view _signature) : signature_t{ module.pe_image, _signature } { }
        signature_t(const pe_image_t& _pe_image, std::string_view _signature) : pe_image{ _pe_image }, signature{ _signature } {
            if(signature.empty()) throw std::runtime_error{ "signature empty" };
            to_bytes();
        }

    public:
        std::vector<std::int32_t> to_bytes() {
            if(!bytes.empty()) return bytes;
            for(std::string_view byte : signature | std::views::split(' ') | std::views::transform([](const auto& splitted) { return std::string_view{ splitted }; })) {
                bytes.push_back(byte.contains("?") ? -1 : strtoul(byte.data(), nullptr, 16));
            }
            return bytes;
        }

        address_t& find() {
            if(!address) {
                PIMAGE_NT_HEADERS nt_headers{ pe_image.nt_headers() };
                auto finded{ std::ranges::search(std::views::iota((std::uintptr_t)nt_headers->OptionalHeader.ImageBase) | std::views::take((std::uintptr_t)nt_headers->OptionalHeader.SizeOfImage), bytes,
                    [](const std::uint8_t& image_byte, const std::int32_t& byte) { return byte == -1 || image_byte == byte; },
                    [](const std::uintptr_t& image_byte) { return *(std::uint8_t*)image_byte; }, [](const std::int32_t& byte) { return byte; }
                    ) };

                if(!finded.empty()) address = finded.front();
                else throw std::runtime_error{ std::format("cant find '{}' signature", signature) };
            }
            return *this;
        }
    };
}