#pragma once
#include <data-types/vec2.h>

namespace null::sdk {
    template <typename x_t, typename y_t = x_t>
        requires vec2_concept<x_t, y_t>
    class i_rect {
    public:
        enum e_origin : std::uint8_t {
            top = 1 << 0,
            bottom = 1 << 1,
            left = 1 << 2,
            right = 1 << 3,
            center = 1 << 4,

            vertival_mask = top | bottom,
            horizontal_mask = left | right
        };

        static i_vec2<float> scale_from_origin(const e_origin& origin) {
            i_vec2<float> scale{ origin & center ? 0.5f : 0.f };
            if(origin & vertival_mask) scale.y = (origin & vertival_mask) >> 1;
            if(origin & horizontal_mask) scale.x = (origin & horizontal_mask) >> 3;
            return scale;
        }

    public:
        i_vec2<x_t, y_t> min{ }, max{ };

    public:
        i_rect() { }

        template <typename t> requires std::is_arithmetic_v<t>
        i_rect(const t& _value) : i_rect{ _value, _value } { }

        template <typename another_x_t, typename another_y_t>
        i_rect(const i_vec2<another_x_t, another_y_t>& _vec) : i_rect{ _vec, _vec } { }

        template <typename t> requires std::is_arithmetic_v<t>
        i_rect(const t& _min, const t& _max) : min{ _min }, max{ _max } { }

        template <typename t, typename origin_t> requires std::is_arithmetic_v<t> && (std::is_arithmetic_v<origin_t> || std::is_same_v<origin_t, e_origin>)
        i_rect(const t& a, const t& size, const origin_t& _origin) : min{ a } { origin(_origin, size); }

        template <typename another_x_t, typename another_y_t>
        i_rect(const i_vec2<another_x_t, another_y_t>& _min, const i_vec2<another_x_t, another_y_t>& _max) : min{ _min }, max{ _max } { }

        template <typename another_x_t, typename another_y_t, typename origin_t> requires std::is_arithmetic_v<origin_t> || std::is_same_v<origin_t, e_origin>
        i_rect(const i_vec2<another_x_t, another_y_t>& a, const i_vec2<another_x_t, another_y_t>& size, const origin_t& _origin) : min{ a } { origin(_origin, size); }

        template <typename t> requires std::is_arithmetic_v<t>
        i_rect(const t& min_x, const t& min_y, const t& max_x, const t& max_y) : min{ min_x, min_y }, max{ max_x, max_y } { }

    public:
        bool contains(const i_vec2<x_t, y_t>& point) const { return min <= point && max >= point; }
        bool contains(const i_rect& rect) const { return contains(rect.min) || contains(rect.max); }
        bool intersects(const i_rect& rect) const {
            if((rect.min.x <= min.x && rect.max.x <= min.x) || (rect.min.x >= max.x && rect.max.x >= max.x)) return false;
            if((rect.min.y <= min.y && rect.max.y <= min.y) || (rect.min.y >= max.y && rect.max.y >= max.y)) return false;
            return true;
        }

        i_vec2<x_t, y_t> size() const { return max - min; }

        i_rect& scale(const i_vec2<float>& _origin, const i_vec2<float>& scale) { return origin(-_origin, size() * scale); }
        template <typename origin_t> requires std::is_arithmetic_v<origin_t> || std::is_same_v<origin_t, e_origin>
        i_rect& scale(const origin_t& _origin, const i_vec2<float>& _scale) { return scale(scale_from_origin((e_origin)_origin), _scale); }

        i_vec2<x_t, y_t> origin(const i_vec2<float>& scale) const { return min + size() * scale; }
        i_rect& origin(const i_vec2<float>& scale, const i_vec2<x_t, y_t>& size) { min -= size * scale; max = min + size; return *this; }
        template <typename origin_t> requires std::is_arithmetic_v<origin_t> || std::is_same_v<origin_t, e_origin>
        i_vec2<x_t, y_t> origin(const origin_t& _origin) const { return origin(scale_from_origin((e_origin)_origin)); }
        template <typename origin_t> requires std::is_arithmetic_v<origin_t> || std::is_same_v<origin_t, e_origin>
        i_rect& origin(const origin_t& _origin, const i_vec2<x_t, y_t>& size) { return origin(scale_from_origin((e_origin)_origin), size); }

        template <typename another_x_t, typename another_y_t>
        i_rect<another_x_t, another_y_t> cast() const { return i_rect<another_x_t, another_y_t>{ min, max }; }

    public:
        template <typename another_x_t, typename another_y_t>
        operator i_rect<another_x_t, another_y_t>() const { return cast<another_x_t, another_y_t>(); }

        template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.min; ++self.max; return self; }
        template <typename self_t> auto operator ++(this self_t&& self, int) { return i_rect{ self.min++, self.max++ }; }
        template <typename self_t> auto&& operator --(this self_t&& self) { --self.min; --self.max; return self; }
        template <typename self_t> auto operator --(this self_t&& self, int) { return i_rect{ self.min--, self.max-- }; }

        template <typename self_t> auto operator -(this self_t&& self) { return i_rect{ -self.min, -self.max }; }
        class_create_arithmetic_operators(rect, i_rect, -, { return i_rect(self.min - rect.min, self.max - rect.max); });
        class_create_arithmetic_operators(rect, i_rect, +, { return i_rect(self.min + rect.min, self.max + rect.max); });
        class_create_arithmetic_operators(rect, i_rect, *, { return i_rect(self.min * rect.min, self.max * rect.max); });
        class_create_arithmetic_operators(rect, i_rect, /, { return i_rect(self.min / rect.min, self.max / rect.max); });
        class_create_arithmetic_operators(rect, i_rect, %, { return i_rect(self.min % rect.min, self.max % rect.max); });

        template <typename another_x_t, typename another_y_t> bool operator ==(const i_rect<another_x_t, another_y_t>& rect) const { return min == rect.min && max == rect.max; };
        template <typename another_x_t, typename another_y_t> bool operator ==(const i_vec2<another_x_t, another_y_t>& vec) const { return min == vec && max == vec; };
        template <typename another_t> requires vec2_concept<another_t, another_t> bool operator ==(const another_t& value) const { return min == value && max == value; };
        class_create_logic_operators(rect, i_rect, <, { return self.min < rect.min && self.max < rect.max; }, { return self.min <= rect.min && self.max <= rect.max; });
        class_create_logic_operators(rect, i_rect, >, { return self.min > rect.min && self.max > rect.max; }, { return self.min >= rect.min && self.max >= rect.max; });
    };
}

using rect_t = null::sdk::i_rect<float>;