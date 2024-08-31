#pragma once
#include "rgba.h"

struct hsv_color_t {
public:
    union {
        struct { float h, s, v, a; };
        std::array<float, 4> channels{ };
    };

public:
    inline constexpr hsv_color_t() : hsv_color_t(0.f, 0.f, 1.f, 1.f) { }
    inline constexpr hsv_color_t(float _h, float _a = 1.f) : hsv_color_t(_h, 1.f, 1.f, _a) { }
    inline constexpr hsv_color_t(float _h, float _s, float _v, float _a = 1.f) : h(_h), s(_s), v(_v), a(_a) { }

    inline constexpr hsv_color_t(const vec3_t<float> _hsv, float _a) : hsv_color_t(_hsv.x, _hsv.y, _hsv.z, _a) { }
    inline constexpr hsv_color_t(const vec4_t<float> _hsva) : hsv_color_t(_hsva.x, _hsva.y, _hsva.z, _hsva.w) { }
    hsv_color_t(const ntl::sdk::i_color<float>& rgba) : channels{ rgba.channels } {
        const double max{ std::ranges::max(rgba.channels | std::views::take(3)) };
        const double delta{ max - std::ranges::min(rgba.channels | std::views::take(3)) };

        if(delta <= 0.f) channels = { 0.f, 0.f, (float)max, rgba.a };
        else {
            if(max == rgba.r)       h = std::fmodf((rgba.g - rgba.b) / delta, 6.f);
            else if(max == rgba.g)  h = (rgba.b - rgba.r) / delta + 2.f;
            else if(max == rgba.b)  h = (rgba.r - rgba.g) / delta + 4.f;
            h *= 60.f;
            if(h < 0.f) h += 360.f;

            s = max > 0.f ? delta / max : 0.f;
            v = max;
        }
    }

public:
    FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, , vec3_t<float>() const, vec3_t<float>, , h, s, v);
    FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, , vec4_t<float>() const, vec4_t<float>, , h, s, v, a);

    operator ntl::sdk::i_color<float>() const {
        const double chroma{ v * s };
        const double prime{ std::fmod(h / 60.f, 6.f) };
        const double x{ chroma * (1.f - std::fabs(std::fmod(prime, 2.f) - 1.f)) };

        vec3_t<double> rgb{ };
        switch((int)prime) {
            case 0: rgb = { chroma, x, 0.f }; break;
            case 1: rgb = { x, chroma, 0.f }; break;
            case 2: rgb = { 0.f, chroma, x }; break;
            case 3: rgb = { 0.f, x, chroma }; break;
            case 4: rgb = { x, 0.f, chroma }; break;
            case 5: rgb = { chroma, 0.f, x }; break;
        }

        const double m{ v - chroma };
        return ntl::sdk::i_color<double>{ rgb + m, a }.cast<float>();
    }

    FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(inline constexpr, h, s, v, a);
    FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(inline constexpr, h, s, v, a);

    FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, const hsv_color_t&, RHS_FIELD, h, s, v, a);
    FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, float, RHS_VALUE, h, s, v, a);

    FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, , const hsv_color_t&, RHS_FIELD, h, s, v, a);
    FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, , float, RHS_VALUE, h, s, v, a);

    FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, template <typename self_t>, const hsv_color_t&, RHS_FIELD, h, s, v, a);
    FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, template <typename self_t>, float, RHS_VALUE, h, s, v, a);
};