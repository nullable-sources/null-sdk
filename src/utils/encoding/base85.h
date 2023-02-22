#pragma once
#include <ranges>
#include <algorithm>

namespace utils::encoding {
    struct base85_t {
    public:
        std::vector<std::uint8_t> output{ }, input{ };

    public:
        base85_t(const std::string_view& _input) : input{ _input.begin(), _input.end() } { }
        base85_t(const std::vector<std::uint8_t>& _input) : input{ _input } { }

    public:
        base85_t& decode() {
            static const auto decode_byte{ [](const std::uint8_t& c) { return c - (c >= '\\' ? 36 : 35); } };
            for(const auto& iterator : std::views::iota(input.begin(), input.end()) | std::views::stride(5)) {
                std::uint32_t chunk{ };
                std::ranges::for_each(std::views::iota(iterator) | std::views::take(std::min((int)std::distance(iterator, input.end()), 5)) | std::views::reverse, [&](const auto& chunk_iterator) { chunk = chunk * 85 + decode_byte(*chunk_iterator); });
                std::ranges::move(std::views::iota(0, 4)
                                  | std::views::transform([&](const int& i) { return (chunk >> (i * 8)) & 0xFF; })
                                  | std::ranges::to<std::vector>(), std::back_inserter(output));
            }
            return *this;
        }

        base85_t& encode() {
            static const auto encode_byte{ [](std::uint32_t c) { c = (c % 85) + 35; return c + (c >= '\\' ? 1 : 0); } };
            for(const auto& iterator : std::views::iota(input.begin(), input.end()) | std::views::stride(4)) {
                std::uint32_t chunk{ };
                std::ranges::for_each(std::views::iota(iterator) | std::views::take(std::min((int)std::distance(iterator, input.end()), 4)) | std::views::reverse, [&](const auto& chunk_iterator) { chunk |= *chunk_iterator << 8 * std::distance(iterator, chunk_iterator); });
                std::ranges::move(std::views::iota(0, 5)
                                  | std::views::transform([&](const int&) { std::uint32_t byte{ encode_byte(chunk) }; chunk /= 85; return byte; })
                                  | std::ranges::to<std::vector>(), std::back_inserter(output));
            }
            return *this;
        }
    };
}