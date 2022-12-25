#pragma once
#include <cmath>

#include <utils/fast_operators.h>

namespace null::sdk {
    template <typename x_t, typename y_t>
    concept vec2_concept = std::is_arithmetic_v<x_t> && std::is_arithmetic_v<y_t>;

    template <typename x_t, typename y_t = x_t> requires vec2_concept<x_t, y_t>
    class i_vec2 {
    public:
        x_t x{ }; y_t y{ };

    public:
        i_vec2() { }

        template <typename t> requires std::is_arithmetic_v<t>
        i_vec2(const t& value) : i_vec2{ value, value } { }

        template <typename another_x_t, typename another_y_t>  requires vec2_concept<another_x_t, another_y_t>
        i_vec2(const another_x_t& _x, const another_y_t& _y) : x{ (x_t)_x }, y{ (y_t)_y } { }

    public:
        float length() const { return std::hypot(x, y); }
        float dot(const i_vec2& vec) const { return x * vec.x + y * vec.y; }
        float cross(const i_vec2& vec) const { return x * vec.y - y * vec.x; }

        template <typename another_x_t, typename another_y_t>
        i_vec2<another_x_t, another_y_t> cast() const { return i_vec2<another_x_t, another_y_t>{ x, y }; }

    public:
        template <typename another_x_t, typename another_y_t>
        operator i_vec2<another_x_t, another_y_t>() const { return cast<another_x_t, another_y_t>(); }

        template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.x; ++self.y; return self; }
        template <typename self_t> auto operator ++(this self_t&& self, int) { return i_vec2{ self.x++, self.y++ }; }
        template <typename self_t> auto&& operator --(this self_t&& self) { --self.x; --self.y; return self; }
        template <typename self_t> auto operator --(this self_t&& self, int) { return i_vec2{ self.x--, self.y-- }; }

        template <typename self_t> auto operator -(this self_t&& self) { return i_vec2{ -self.x, -self.y }; }
        class_create_arithmetic_operators(vec, i_vec2, -, { return i_vec2(self.x - vec.x, self.y - vec.y); });
        class_create_arithmetic_operators(vec, i_vec2, +, { return i_vec2(self.x + vec.x, self.y + vec.y); });
        class_create_arithmetic_operators(vec, i_vec2, *, { return i_vec2(self.x * vec.x, self.y * vec.y); });
        class_create_arithmetic_operators(vec, i_vec2, /, { return i_vec2(self.x / vec.x, self.y / vec.y); });
        class_create_arithmetic_operators(vec, i_vec2, %, { return i_vec2(self.x % vec.x, self.y % vec.y); });

        template <typename another_x_t, typename another_y_t> bool operator ==(const i_vec2<another_x_t, another_y_t>& vec) const { return x == vec.x && y == vec.y; };
        template <typename another_t> requires vec2_concept<another_t, another_t> bool operator ==(const another_t& value) const { return x == value && y == value; };
        class_create_logic_operators(vec, i_vec2, <, { return self.x < vec.x && self.y < vec.y; }, { return self.x <= vec.x && self.y <= vec.y; });
        class_create_logic_operators(vec, i_vec2, >, { return self.x > vec.x && self.y > vec.y; }, { return self.x >= vec.x && self.y >= vec.y; });
    };
}

using vec2_t = null::sdk::i_vec2<float>;