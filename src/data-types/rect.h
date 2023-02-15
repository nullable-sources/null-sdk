#pragma once
#include <data-types/vec2.h>

namespace null {
    enum e_rect_origin {
        top     = 1 << 0,
        bottom  = 1 << 1,
        left    = 1 << 2,
        right   = 1 << 3,
        center  = 1 << 4,

        top_left    = top | left,
        top_right   = top | right,
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

template <typename corners_t = float>
struct rect_t {
public:
    template <float min = 0.f, float max = 1.f, float midpoint = std::midpoint(min, max)>
    static vec2_t<float> scale_from_origin(const null::e_rect_origin& origin) {
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
        struct { vec2_t<corners_t> min, max; };
        std::array<vec2_t<corners_t>, array_size> corners;
        std::array<corners_t, array_linear_size> linear_corners{ };
    };

public:
    rect_t() { }

    rect_t(const corners_t& _value) : rect_t{ _value, _value } { }
    rect_t(const vec2_t<corners_t>& _vec) : rect_t{ _vec, _vec } { }

    rect_t(const corners_t & _min, const corners_t & _max) : min{ _min }, max{ _max } { }
    rect_t(const vec2_t<corners_t>& _min, const vec2_t<corners_t>& _max) : min{ _min }, max{ _max } { }

    rect_t(const corners_t& a, const corners_t& size, const null::e_rect_origin& _origin) : min{ a } { origin(_origin, size); }
    rect_t(const vec2_t<corners_t>& a, const vec2_t<corners_t>& size, const null::e_rect_origin& _origin) : min{ a } { origin(_origin, size); }

    rect_t(const corners_t & min_x, const corners_t & min_y, const corners_t & max_x, const corners_t& max_y) : min{ min_x, min_y }, max{ max_x, max_y } { }

    rect_t(const std::array<vec2_t<corners_t>, array_size>& _corners) : corners{ _corners } { }
    rect_t(const std::array<corners_t, array_linear_size>& _corners) : linear_corners{ _corners } { }

    template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<type_t, rect_t<corners_t>>
    rect_t(const type_t& value) { *this = null::compatibility::data_type_converter_t<type_t, rect_t<corners_t>>::convert(value); }

public:
    bool contains(const vec2_t<corners_t>& point) const { return min <= point && max >= point; }
    bool contains(const rect_t& rect) const { return contains(rect.min) || contains(rect.max); }
    bool intersects(const rect_t& rect) const {
        if((rect.min.x <= min.x && rect.max.x <= min.x) || (rect.min.x >= max.x && rect.max.x >= max.x)) return false;
        if((rect.min.y <= min.y && rect.max.y <= min.y) || (rect.min.y >= max.y && rect.max.y >= max.y)) return false;
        return true;
    }

    vec2_t<corners_t> size() const { return max - min; }

    rect_t& scale(const vec2_t<float>& _origin, const vec2_t<float>& scale) { return origin(-_origin, size() * scale); }
    rect_t& scale(const null::e_rect_origin& _origin, const vec2_t<float>& _scale) { return scale(scale_from_origin(_origin), _scale); }

    vec2_t<corners_t> origin(const vec2_t<float>& scale) const { return min + size() * scale; }
    rect_t& origin(const vec2_t<float>& scale, const vec2_t<corners_t>& size) { min -= size * scale; max = min + size; return *this; }
    vec2_t<corners_t> origin(const null::e_rect_origin& _origin) const { return origin(scale_from_origin(_origin)); }
    rect_t& origin(const null::e_rect_origin& _origin, const vec2_t<corners_t>& size) { return origin(scale_from_origin(_origin), size); }

public:
    template <typename another_corners_t>
    operator rect_t<another_corners_t>() const { return rect_t<another_corners_t>{ (vec2_t<another_corners_t>)min, (vec2_t<another_corners_t>)max }; }

    template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<rect_t<corners_t>, type_t>
    operator type_t() const { return null::compatibility::data_type_converter_t<rect_t<corners_t>, type_t>::convert(*this); }

    template <typename self_t> auto&& operator [](this self_t&& self, const int& i) { return self.corners[i]; }

    template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.min; ++self.max; return self; }
    template <typename self_t> auto operator ++(this self_t&& self, int) { return rect_t{ self.min++, self.max++ }; }
    template <typename self_t> auto&& operator --(this self_t&& self) { --self.min; --self.max; return self; }
    template <typename self_t> auto operator --(this self_t&& self, int) { return rect_t{ self.min--, self.max-- }; }

    template <typename self_t> auto operator -(this self_t&& self) { return rect_t{ -self.min, -self.max }; }
    class_create_arithmetic_operators(rect, rect_t, -, { return rect_t(self.min - rect.min, self.max - rect.max); });
    class_create_arithmetic_operators(rect, rect_t, +, { return rect_t(self.min + rect.min, self.max + rect.max); });
    class_create_arithmetic_operators(rect, rect_t, *, { return rect_t(self.min * rect.min, self.max * rect.max); });
    class_create_arithmetic_operators(rect, rect_t, /, { return rect_t(self.min / rect.min, self.max / rect.max); });
    class_create_arithmetic_operators(rect, rect_t, %, { return rect_t(self.min % rect.min, self.max % rect.max); });

    template <typename another_corners_t> bool operator ==(const rect_t<another_corners_t>& rect) const { return min == rect.min && max == rect.max; };
    template <typename another_corners_t> bool operator ==(const vec2_t<another_corners_t>& vec) const { return min == vec && max == vec; };
    template <typename another_t> bool operator ==(const another_t& value) const { return min == value && max == value; };
    class_create_logic_operators(rect, rect_t, <, { return self.min < rect.min && self.max < rect.max; }, { return self.min <= rect.min && self.max <= rect.max; });
    class_create_logic_operators(rect, rect_t, >, { return self.min > rect.min && self.max > rect.max; }, { return self.min >= rect.min && self.max >= rect.max; });
};