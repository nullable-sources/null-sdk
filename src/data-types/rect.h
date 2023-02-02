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

template <typename x_t = float, typename y_t = x_t>
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
    vec2_t<x_t, y_t> min{ }, max{ };

public:
    rect_t() { }

    template <typename t> requires std::is_arithmetic_v<t>
    rect_t(const t& _value) : rect_t{ _value, _value } { }

    template <typename another_x_t, typename another_y_t>
    rect_t(const vec2_t<another_x_t, another_y_t>& _vec) : rect_t{ _vec, _vec } { }

    template <typename t> requires std::is_arithmetic_v<t>
    rect_t(const t& _min, const t& _max) : min{ _min }, max{ _max } { }

    template <typename t> requires std::is_arithmetic_v<t>
    rect_t(const t& a, const t& size, const null::e_rect_origin& _origin) : min{ a } { origin(_origin, size); }

    template <typename another_x_t, typename another_y_t>
    rect_t(const vec2_t<another_x_t, another_y_t>& _min, const vec2_t<another_x_t, another_y_t>& _max) : min{ _min }, max{ _max } { }

    template <typename another_x_t, typename another_y_t>
    rect_t(const vec2_t<another_x_t, another_y_t>& a, const vec2_t<another_x_t, another_y_t>& size, const null::e_rect_origin& _origin) : min{ a } { origin(_origin, size); }

    template <typename t> requires std::is_arithmetic_v<t>
    rect_t(const t& min_x, const t& min_y, const t& max_x, const t& max_y) : min{ min_x, min_y }, max{ max_x, max_y } { }

public:
    bool contains(const vec2_t<x_t, y_t>& point) const { return min <= point && max >= point; }
    bool contains(const rect_t& rect) const { return contains(rect.min) || contains(rect.max); }
    bool intersects(const rect_t& rect) const {
        if((rect.min.x <= min.x && rect.max.x <= min.x) || (rect.min.x >= max.x && rect.max.x >= max.x)) return false;
        if((rect.min.y <= min.y && rect.max.y <= min.y) || (rect.min.y >= max.y && rect.max.y >= max.y)) return false;
        return true;
    }

    vec2_t<x_t, y_t> size() const { return max - min; }

    rect_t& scale(const vec2_t<float>& _origin, const vec2_t<float>& scale) { return origin(-_origin, size() * scale); }
    rect_t& scale(const null::e_rect_origin& _origin, const vec2_t<float>& _scale) { return scale(scale_from_origin(_origin), _scale); }

    vec2_t<x_t, y_t> origin(const vec2_t<float>& scale) const { return min + size() * scale; }
    rect_t& origin(const vec2_t<float>& scale, const vec2_t<x_t, y_t>& size) { min -= size * scale; max = min + size; return *this; }
    vec2_t<x_t, y_t> origin(const null::e_rect_origin& _origin) const { return origin(scale_from_origin(_origin)); }
    rect_t& origin(const null::e_rect_origin& _origin, const vec2_t<x_t, y_t>& size) { return origin(scale_from_origin(_origin), size); }

    template <typename another_x_t, typename another_y_t>
    rect_t<another_x_t, another_y_t> cast() const { return rect_t<another_x_t, another_y_t>{ min, max }; }

public:
    template <typename another_x_t, typename another_y_t>
    operator rect_t<another_x_t, another_y_t>() const { return cast<another_x_t, another_y_t>(); }

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

    template <typename another_x_t, typename another_y_t> bool operator ==(const rect_t<another_x_t, another_y_t>& rect) const { return min == rect.min && max == rect.max; };
    template <typename another_x_t, typename another_y_t> bool operator ==(const vec2_t<another_x_t, another_y_t>& vec) const { return min == vec && max == vec; };
    template <typename another_t> bool operator ==(const another_t& value) const { return min == value && max == value; };
    class_create_logic_operators(rect, rect_t, <, { return self.min < rect.min && self.max < rect.max; }, { return self.min <= rect.min && self.max <= rect.max; });
    class_create_logic_operators(rect, rect_t, >, { return self.min > rect.min && self.max > rect.max; }, { return self.min >= rect.min && self.max >= rect.max; });
};