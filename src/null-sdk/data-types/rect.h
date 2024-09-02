#pragma once
#include <numeric>

#include "vec2.h"

namespace ntl {
    enum e_rect_origin {
        top             = 1 << 0,
        bottom          = 1 << 1,
        left            = 1 << 2,
        right           = 1 << 3,
        center          = 1 << 4,

        top_left        = top | left,
        top_right       = top | right,
        bottom_left     = bottom | left,
        bottom_right    = bottom | right,

        center_top      = center | top,
        center_bottom   = center | bottom,
        center_left     = center | left,
        center_right    = center | right,

        vertival_mask   = top | bottom,
        horizontal_mask = left | right
    }; ENUM_CREATE_BIT_OPERATORS(e_rect_origin, false);
    ENUM_CREATE_CAST_OPERATOR(e_rect_origin, -);
}

template <typename corner_t>
struct rect_t {
public:
    template <float min = 0.f, float max = 1.f, float midpoint = std::midpoint(min, max)>
    static constexpr vec2_t<float> scale_from_origin(ntl::e_rect_origin origin) {
        vec2_t<float> scale = origin & ntl::e_rect_origin::center ? midpoint : min;
        if(origin & ntl::e_rect_origin::vertival_mask) scale.y = (origin & -ntl::e_rect_origin::vertival_mask) >> 1 ? max : min;
        if(origin & ntl::e_rect_origin::horizontal_mask) scale.x = (origin & -ntl::e_rect_origin::horizontal_mask) >> 3 ? max : min;
        return scale;
    }

public:
    static constexpr size_t array_size = 2;         //@note: size array{ min, max }
    static constexpr size_t array_linear_size = 4;  //@note: size array{ min.x, min.y, max.x, max.y }

public:
    union {
        struct { vec2_t<corner_t> min, max; };
        std::array<vec2_t<corner_t>, array_size> corners;
        std::array<corner_t, array_linear_size> linear_corners{ };
    };

public:
    inline constexpr rect_t() { }

    inline constexpr rect_t(corner_t _value) : rect_t(_value, _value) { }
    inline constexpr rect_t(const vec2_t<corner_t>& _vec) : rect_t(_vec, _vec) { }

    inline constexpr rect_t(corner_t _min, corner_t _max) : min(_min), max(_max) { }
    inline constexpr rect_t(const vec2_t<corner_t>& _min, const vec2_t<corner_t>& _max) : min(_min), max(_max) { }

    inline constexpr rect_t(corner_t a, corner_t size, const ntl::e_rect_origin& _origin) : min(a) { origin(_origin, size); }
    inline constexpr rect_t(const vec2_t<corner_t>& a, const vec2_t<corner_t>& size, const ntl::e_rect_origin& _origin) : min(a) { origin(_origin, size); }

    inline constexpr rect_t(corner_t min_x, corner_t min_y, corner_t max_x, corner_t max_y) : min(min_x, min_y), max(max_x, max_y) { }

    rect_t(const std::array<vec2_t<corner_t>, array_size>& _corners) : corners(_corners) { }
    rect_t(const std::array<corner_t, array_linear_size>& _corners) : linear_corners(_corners) { }

    template <typename type_t> requires ntl::compatibility::data_type_convertertable<type_t, rect_t<corner_t>>
    inline constexpr rect_t(const type_t& value) { *this = ntl::compatibility::data_type_converter_t<type_t, rect_t<corner_t>>::convert(value); }

public:
    inline constexpr bool contains(const vec2_t<corner_t>& point) const { return min <= point && max >= point; }
    inline constexpr bool contains(const rect_t<corner_t>& rect) const { return contains(rect.min) || contains(rect.max); }
    inline constexpr bool intersects(const rect_t<corner_t>& rect) const {
        if((rect.min.x <= min.x && rect.max.x <= min.x) || (rect.min.x >= max.x && rect.max.x >= max.x)) return false;
        if((rect.min.y <= min.y && rect.max.y <= min.y) || (rect.min.y >= max.y && rect.max.y >= max.y)) return false;
        return true;
    }

    inline constexpr vec2_t<corner_t> size() const { return max - min; }

    template <typename self_t> inline constexpr auto&& scale(this self_t&& self, const vec2_t<float>& _origin, const vec2_t<float>& scale) { return self.origin(-_origin, self.size() * scale); }
    template <typename self_t> inline constexpr auto&& scale(this self_t&& self, ntl::e_rect_origin _origin, const vec2_t<float>& _scale) { return self.scale(scale_from_origin(_origin), _scale); }

    inline constexpr vec2_t<corner_t> origin(const vec2_t<float>& scale) const { return min + size() * scale; }
    template <typename self_t> inline constexpr auto&& origin(this self_t&& self, const vec2_t<float>& scale, const vec2_t<corner_t>& size) { self.min -= size * scale; self.max = self.min + size; return self; }
    inline constexpr vec2_t<corner_t> origin(ntl::e_rect_origin _origin) const { return origin(scale_from_origin(_origin)); }
    template <typename self_t> inline constexpr auto&& origin(this self_t&& self, ntl::e_rect_origin _origin, const vec2_t<corner_t>& size) { return self.origin(scale_from_origin(_origin), size); }

public:
    FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, template <typename other_t>, rect_t<other_t>() const, rect_t<other_t>, (vec2_t<other_t>), min, max);
    FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, , FAST_OPS_ARGS_PACK(std::tuple<corner_t, corner_t, corner_t, corner_t>)() const, std::make_tuple, , min.x, min.y, max.x, max.y);

    template <typename type_t> requires ntl::compatibility::data_type_convertertable<rect_t<corner_t>, type_t>
    inline constexpr operator type_t() const { return ntl::compatibility::data_type_converter_t<rect_t<corner_t>, type_t>::convert(*this); }

    template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.corners[i]; }

    FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(inline constexpr, min, max);
    FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(inline constexpr, min, max);

    FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const rect_t<other_t>&, RHS_FIELD, min, max);
    FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const vec2_t<other_t>&, RHS_VALUE, min, max);
    FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, corner_t, RHS_VALUE, min, max);

    FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, template <typename other_t>, const rect_t<other_t>&, RHS_FIELD, min, max);
    FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, template <typename other_t>, const vec2_t<other_t>&, RHS_VALUE, min, max);
    FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, , corner_t, RHS_VALUE, min, max);

    FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const rect_t<other_t>&, RHS_FIELD, min, max);
    FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const vec2_t<other_t>&, RHS_VALUE, min, max);
    FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, template <typename self_t>, corner_t, RHS_VALUE, min, max);
};