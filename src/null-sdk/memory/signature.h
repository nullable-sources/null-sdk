#pragma once
#include "module/module.h"

namespace ntl {
    struct signature_t : public address_t {
    public:
        pe_image_t pe_image{ };

        std::vector<std::int32_t> bytes{ };

    public:
        signature_t(const c_module& module, std::string_view _signature) : signature_t(module.pe_image, _signature) { }
        signature_t(const pe_image_t& _pe_image, std::string_view _signature) : pe_image(_pe_image) {
            from_string(_signature);
        }

    public:
        std::string to_string() const {
            if(bytes.empty()) return "";

            std::string result{ };
            for(int byte : bytes) {
                if(byte == -1) result.append("?");
                else result.append(std::format("{:02X}", byte));
                result.append(" ");
            }

            if(!result.empty()) result.pop_back();
            return result;
        }

        template <typename self_t>
        auto&& from_string(this self_t&& self, std::string_view signature) {
            self.bytes = signature | std::views::split(' ') | std::views::transform([](const auto& splitted) { return std::string_view(splitted).contains("?") ? -1 : (int)strtoul(splitted.data(), nullptr, 16); }) | std::ranges::to<std::vector>();
            return self.bytes;
        }

    public:
        template <typename self_t>
        auto&& find(this self_t&& self) {
            if(!self.address) {
                PIMAGE_NT_HEADERS nt_headers = self.pe_image.nt_headers();
                auto finded = std::ranges::search(
                    std::views::iota((std::uintptr_t)nt_headers->OptionalHeader.ImageBase) | std::views::take((std::uintptr_t)nt_headers->OptionalHeader.SizeOfImage),
                    self.bytes,
                    [](std::uintptr_t image_byte, std::int32_t byte) { return byte == -1 || *(std::uint8_t*)image_byte == byte; }
                );


                if(!finded.empty()) self.address = finded.front();
                else sdk::logger(sdk::e_log_type::warning, std::format("cant find \"{}\" signature", self.to_string()));
            }

            return self;
        }
    };
}