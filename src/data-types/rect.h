#pragma once
#include "data-types/vec2.h"

namespace null {
    enum e_rect_origin {
        top     = 1 << 0,
        bottom  = 1 << 1,
        left    = 1 << 2,
        right   = 1 << 3,
        center  = 1 << 4,

        top_left        = top | left,
        top_right       = top | right,
        bottom_left     = bottom | left,
        bottom_right    = bottom | right,

        center_top      = center | top,
        center_bottom   = center | bottom,
        center_left     = center | left,
        center_right    = center | right,

        vertival_mask = top | bottom,
        horizontal_mask = left | right
    }; enum_create_bit_operators(e_rect_origin, false);
    enum_create_cast_operator(e_rect_origin, -);
}

template <typename corner_t>
struct rect_t {
public:
    template <float min = 0.f, float max = 1.f, float midpoint = std::midpoint(min, max)>
    static vec2_t<float> scale_from_origin(null::e_rect_origin origin) {
        vec2_t<float> scale{ origin & null::e_rect_origin::center ? midpoint : min };
        if(origin & null::e_rect_origin::vertival_mask) scale.y = (origin & -null::e_rect_origin::vertival_mask) >> 1 ? max : min;
        if(origin & null::e_rect_origin::horizontal_mask) scale.x = (origin & -null::e_rect_origin::horizontal_mask) >> 3 ? max : min;
        return scale;
    }

public:
    static constexpr size_t array_size{ 2 };          //@note: size array{ min, max }
    static constexpr size_t array_linear_size{ 4 };   //@note: size array{ min.x, min.y, max.x, max.y }

public:
    union {
        struct { vec2_t<corner_t> min, max; };
        std::array<vec2_t<corner_t>, array_size> corners;
        std::array<corner_t, array_linear_size> linear_corners{ };
    };

public:
    rect_t() { }

    rect_t(corner_t _value) : rect_t{ _value, _value } { }
    rect_t(const vec2_t<corner_t>& _vec) : rect_t{ _vec, _vec } { }

    rect_t(corner_t _min, corner_t _max) : min{ _min }, max{ _max } { }
    rect_t(const vec2_t<corner_t>& _min, const vec2_t<corner_t>& _max) : min{ _min }, max{ _max } { }

    rect_t(corner_t a, corner_t size, const null::e_rect_origin& _origin) : min{ a } { origin(_origin, size); }
    rect_t(const vec2_t<corner_t>& a, const vec2_t<corner_t>& size, const null::e_rect_origin& _origin) : min{ a } { origin(_origin, size); }

    rect_t(corner_t min_x, corner_t min_y, corner_t max_x, corner_t max_y) : min{ min_x, min_y }, max{ max_x, max_y } { }

    rect_t(const std::array<vec2_t<corner_t>, array_size>& _corners) : corners{ _corners } { }
    rect_t(const std::array<corner_t, array_linear_size>& _corners) : linear_corners{ _corners } { }

    template <typename type_t> requires null::compatibility::data_type_convertertable<type_t, rect_t<corner_t>>
    rect_t(const type_t& value) { *this = null::compatibility::data_type_converter_t<type_t, rect_t<corner_t>>::convert(value); }

public:
    bool contains(const vec2_t<corner_t>& point) const { return min <= point && max >= point; }
    bool contains(const rect_t<corner_t>& rect) const { return contains(rect.min) || contains(rect.max); }
    bool intersects(const rect_t<corner_t>& rect) const {
        if((rect.min.x <= min.x && rect.max.x <= min.x) || (rect.min.x >= max.x && rect.max.x >= max.x)) return false;
        if((rect.min.y <= min.y && rect.max.y <= min.y) || (rect.min.y >= max.y && rect.max.y >= max.y)) return false;
        return true;
    }

    vec2_t<corner_t> size() const { return max - min; }

    template <typename self_t> auto&& scale(this self_t&& self, const vec2_t<float>& _origin, const vec2_t<float>& scale) { return self.origin(-_origin, self.size() * scale); }
    template <typename self_t> auto&& scale(this self_t&& self, null::e_rect_origin _origin, const vec2_t<float>& _scale) { return self.scale(scale_from_origin(_origin), _scale); }

    vec2_t<corner_t> origin(const vec2_t<float>& scale) const { return min + size() * scale; }
    template <typename self_t> auto&& origin(this self_t&& self, const vec2_t<float>& scale, const vec2_t<corner_t>& size) { self.min -= size * scale; self.max = self.min + size; return self; }
    vec2_t<corner_t> origin(null::e_rect_origin _origin) const { return origin(scale_from_origin(_origin)); }
    template <typename self_t> auto&& origin(this self_t&& self, null::e_rect_origin _origin, const vec2_t<corner_t>& size) { return self.origin(scale_from_origin(_origin), size); }

public:
    fast_ops_structure_convert_operator(template <typename other_t>, rect_t<other_t>() const, rect_t<other_t>, (vec2_t<other_t>), min, max);
    fast_ops_structure_convert_operator(, fast_ops_args_pack(std::tuple<corner_t, corner_t, corner_t, corner_t>)() const, std::make_tuple, , min.x, min.y, max.x, max.y);

    template <typename type_t> requires null::compatibility::data_type_convertertable<rect_t<corner_t>, type_t>
    operator type_t() const { return null::compatibility::data_type_converter_t<rect_t<corner_t>, type_t>::convert(*this); }

    template <typename self_t> auto&& operator [](this self_t&& self, int i) { return self.corners[i]; }

    fast_ops_structure_all_prefix_operators(min, max);
    fast_ops_structure_all_postfix_operators(min, max);

    fast_ops_structure_all_arithmetic_operators(fast_ops_args_pack(template <typename self_t, typename other_t>), const rect_t<other_t>&, rhs_field, min, max);
    fast_ops_structure_all_arithmetic_operators(fast_ops_args_pack(template <typename self_t, typename other_t>), const vec2_t<other_t>&, rhs_value, min, max);
	fast_ops_structure_all_arithmetic_operators(template <typename self_t>, corner_t, rhs_value, min, max);

    fast_ops_structure_equal_operator(template <typename other_t>, const rect_t<other_t>&, rhs_field, min, max);
    fast_ops_structure_equal_operator(template <typename other_t>, const vec2_t<other_t>&, rhs_value, min, max);
	fast_ops_structure_equal_operator(, corner_t, rhs_value, min, max);

    fast_ops_structure_all_comparison_operators(fast_ops_args_pack(template <typename self_t, typename other_t>), const rect_t<other_t>&, rhs_field, min, max);
    fast_ops_structure_all_comparison_operators(fast_ops_args_pack(template <typename self_t, typename other_t>), const vec2_t<other_t>&, rhs_value, min, max);
    fast_ops_structure_all_comparison_operators(template <typename self_t>, corner_t, rhs_value, min, max);
};