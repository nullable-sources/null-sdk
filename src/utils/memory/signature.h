#pragma once
#include <utils/memory/module/module.h>

namespace memory {
    struct signature_t : address_t {
    public:
        pe_image_t pe_image{ };
        std::string signature{ };

        std::vector<std::int32_t> bytes{ };

    public:
        signature_t(const c_module& module, const std::string_view& _signature) : signature_t{ module.pe_image, _signature } { }
        signature_t(const pe_image_t& _pe_image, const std::string_view& _signature) : pe_image{ _pe_image }, signature{ _signature } {
            if(signature.empty()) throw std::runtime_error{ "signature empty" };
            to_bytes();
        }

    public:
        template <typename self_t>
        auto&& to_bytes(this self_t&& self) {
            if(!self.bytes.empty()) return self.bytes;
            self.bytes = self.signature | std::views::split(' ') | std::views::transform([](const auto& splitted) { return std::string_view{ splitted }.contains("?") ? -1 : (int)strtoul(splitted.data(), nullptr, 16); }) | std::ranges::to<std::vector>();
            return self.bytes;
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