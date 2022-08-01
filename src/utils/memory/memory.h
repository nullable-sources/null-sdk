#pragma once
#include <utils/win/win.h>

//@note: I gave a hard shit, I'll rewrite it normally later
namespace memory {
    struct signature_t {
    public:
        struct {
            std::uintptr_t base{ };
            std::uintptr_t size{ };
        } module{ };

        std::string signature{ };
        std::vector<std::int32_t> bytes{ };
        std::uintptr_t first_match{ };

    public:
        signature_t(std::string_view module_name, std::string_view _signature) : signature(_signature) {
            HMODULE module_handle = GetModuleHandleA(module_name.data());
            PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((std::uintptr_t)module_handle + ((PIMAGE_DOS_HEADER)module_handle)->e_lfanew);
            module.base = nt_headers->OptionalHeader.ImageBase;
            module.size = nt_headers->OptionalHeader.SizeOfImage;
            to_bytes();
        }

        int get_first_unknown_opcode() {
            if(auto finded = std::ranges::find(bytes, -1); finded != bytes.end()) return std::distance(bytes.begin(), finded);
            return -1;
        }

        std::vector<std::int32_t> to_bytes() {
            if(!bytes.empty()) return bytes;
            for(const auto splited : std::views::split(signature, std::string_view{ " " })) {
                std::string_view byte{ splited.begin(), splited.end() };
                if(byte.contains("?")) bytes.push_back(-1);
                else bytes.push_back(strtoul(byte.data(), nullptr, 16));
            }
            return bytes;
        }

        std::uintptr_t find() {
            if(first_match) return first_match;

            int finded_offset{ };
            for(const std::uintptr_t& module_byte : std::views::iota(module.base, module.base + module.size)) {
                if(bytes[finded_offset] == -1 || *(std::uint8_t*)module_byte == bytes[finded_offset]) {
                    if(!first_match) first_match = module_byte;

                    finded_offset++;
                    if(finded_offset == bytes.size()) return first_match;
                } else if(first_match) {
                    finded_offset = first_match = 0;
                }
            }

            if(!first_match)
                throw std::runtime_error(std::format("cant find '{}' signature", signature));

            return first_match;
        }

        std::uintptr_t read(std::uint32_t instruction_size, std::uint32_t opcode_offset = -1) {
            std::uintptr_t addresss = find();
#if _WIN64
            return (std::uintptr_t)(addresss + (*(std::uint32_t*)(addresss + (opcode_offset == -1 ? get_first_unknown_opcode() : opcode_offset))) + instruction_size);
#else
            return (std::uintptr_t)(address + instruction_size);
#endif
        }
    };

    struct vtable_t {
    public:
        std::uintptr_t* object{ };

    public:
        template<typename object_t>
        vtable_t(object_t* _object) : object((std::uintptr_t*)_object) { }

        std::uintptr_t* get() { return *(std::uintptr_t**)object; }
        std::uintptr_t operator[](int idx) { return get()[idx]; }

        template <typename funtion_t>
        funtion_t function(int index) {
            return (funtion_t)(get()[index]);
        }

    };
}