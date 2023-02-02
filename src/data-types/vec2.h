#pragma once
#include <cmath>
#include <utils/fast_operators.h>

template <typename x_t = float, typename y_t = x_t>
struct vec2_t {
public:
    x_t x{ }; y_t y{ };

public:
    vec2_t() { }

    template <typename t> requires std::is_arithmetic_v<t>
    vec2_t(const t& value) : vec2_t{ value, value } { }

    template <typename another_x_t, typename another_y_t>
    vec2_t(const another_x_t& _x, const another_y_t& _y) : x{ (x_t)_x }, y{ (y_t)_y } { }

public:
    float length() const { return std::hypot(x, y); }
    float dot(const vec2_t& vec) const { return x * vec.x + y * vec.y; }
    float cross(const vec2_t& vec) const { return x * vec.y - y * vec.x; }

    template <typename another_x_t, typename another_y_t>
    vec2_t<another_x_t, another_y_t> cast() const { return vec2_t<another_x_t, another_y_t>{ x, y }; }

public:
    template <typename another_x_t, typename another_y_t>
    operator vec2_t<another_x_t, another_y_t>() const { return cast<another_x_t, another_y_t>(); }

    template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.x; ++self.y; return self; }
    template <typename self_t> auto operator ++(this self_t&& self, int) { return vec2_t{ self.x++, self.y++ }; }
    template <typename self_t> auto&& operator --(this self_t&& self) { --self.x; --self.y; return self; }
    template <typename self_t> auto operator --(this self_t&& self, int) { return vec2_t{ self.x--, self.y-- }; }

    template <typename self_t> auto operator -(this self_t&& self) { return vec2_t{ -self.x, -self.y }; }
    class_create_arithmetic_operators(vec, vec2_t, -, { return vec2_t(self.x - vec.x, self.y - vec.y); });
    class_create_arithmetic_operators(vec, vec2_t, +, { return vec2_t(self.x + vec.x, self.y + vec.y); });
    class_create_arithmetic_operators(vec, vec2_t, *, { return vec2_t(self.x * vec.x, self.y * vec.y); });
    class_create_arithmetic_operators(vec, vec2_t, /, { return vec2_t(self.x / vec.x, self.y / vec.y); });
    class_create_arithmetic_operators(vec, vec2_t, %, { return vec2_t(self.x % vec.x, self.y % vec.y); });

    template <typename another_x_t, typename another_y_t> bool operator ==(const vec2_t<another_x_t, another_y_t>& vec) const { return x == vec.x && y == vec.y; };
    template <typename another_t> requires std::is_arithmetic_v<another_t> bool operator ==(const another_t& value) const { return x == value && y == value; };
    class_create_logic_operators(vec, vec2_t, <, { return self.x < vec.x && self.y < vec.y; }, { return self.x <= vec.x && self.y <= vec.y; });
    class_create_logic_operators(vec, vec2_t, >, { return self.x > vec.x && self.y > vec.y; }, { return self.x >= vec.x && self.y >= vec.y; });
};