#pragma once
#include <array>
#include <ranges>
#include <algorithm>

#include "null-sdk/utils/fast-operators.h"
#include "null-sdk/data-types/vec4.h"

namespace ntl::sdk {
    template <typename channel_t>
    struct i_color {
    public:
        static constexpr size_t channels_size = 4; //@note: size array{ r, g, b, a }

    public:
        union {
            struct { channel_t r, g, b, a; };
            std::array<channel_t, channels_size> channels{ };
        };

    public:
        inline constexpr i_color() { }

        inline constexpr i_color(channel_t _rgba) : i_color(_rgba, _rgba, _rgba, _rgba) { };
        inline constexpr i_color(channel_t _rgb, channel_t _a) : i_color(_rgb, _rgb, _rgb, _a) { }
        inline constexpr i_color(channel_t _r, channel_t _g, channel_t _b, channel_t _a) : r(_r), g(_g), b(_b), a(_a) { }

        inline constexpr i_color(const vec3_t<channel_t> _rgb, channel_t _a) : i_color(_rgb.x, _rgb.y, _rgb.z, _a) { }
        inline constexpr i_color(const vec4_t<channel_t> _rgba) : i_color(_rgba.x, _rgba.y, _rgba.z, _rgba.w) { }

        inline constexpr i_color(const i_color<channel_t>& color, channel_t _a) : i_color(color.r, color.g, color.b, _a) { }
        inline i_color(const std::array<channel_t, channels_size>& _channels) : channels(_channels) { }
        inline i_color(const std::vector<channel_t>& _channels) { std::move(_channels.begin(), std::next(_channels.begin(), std::min(_channels.size(), channels_size)), channels.begin()); }

        template <typename type_t> requires ntl::compatibility::data_type_convertertable<type_t, i_color<channel_t>>
        inline constexpr i_color(const type_t& value) : i_color(ntl::compatibility::data_type_converter_t<type_t, i_color<channel_t>>::convert(value)) { }

    public:
        template <typename other_t> inline constexpr i_color<other_t> cast() const { return i_color<other_t>((other_t)r, (other_t)g, (other_t)b, (other_t)a); }

        template <typename self_t> inline constexpr auto rgb(this self_t&& self) { return vec3_t<channel_t>(self.r, self.g, self.b); }

        inline channel_t brightness() const { return *std::max_element(channels.begin(), std::prev(channels.end())); }

    public:
        FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, , vec3_t<channel_t>() const, vec3_t<channel_t>, , r, g, b);
        FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, , vec4_t<channel_t>() const, vec4_t<channel_t>, , r, g, b, a);
        FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, , FAST_OPS_ARGS_PACK(std::tuple<channel_t, channel_t, channel_t, channel_t>)() const, std::make_tuple, , r, g, b, a);

        template <typename type_t> requires ntl::compatibility::data_type_convertertable<i_color<channel_t>, type_t>
        inline constexpr operator type_t() const { return ntl::compatibility::data_type_converter_t<i_color<channel_t>, type_t>::convert(*this); }

        FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(inline constexpr, r, g, b, a);
        FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(inline constexpr, r, g, b, a);

        FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const i_color<other_t>&, RHS_FIELD, r, g, b, a);
        FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, channel_t, RHS_VALUE, r, g, b, a);

        FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, template <typename other_t>, const i_color<other_t>&, RHS_FIELD, r, g, b, a);
        FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, , channel_t, RHS_VALUE, r, g, b, a);

        FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const i_color<other_t>&, RHS_FIELD, r, g, b, a);
        FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, template <typename self_t>, channel_t, RHS_VALUE, r, g, b, a);
    };
}