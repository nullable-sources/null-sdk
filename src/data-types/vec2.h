#pragma once
#include <cmath>
#include <array>
#include <vector>
#include <utils/fast_operators.h>

template <typename coordinates_t = float>
struct vec2_t {
public:
    static constexpr size_t array_size{ 2 }; //@note: size array{ x, y }

public:
    union {
        struct { coordinates_t x, y; };
        std::array<coordinates_t, array_size> coordinates{ };
    };

public:
    vec2_t() { }

    template <typename t> requires std::is_same_v<t, coordinates_t> || std::is_convertible_v<t, coordinates_t>
    vec2_t(const t& value) : vec2_t{ value, value } { }

    template <typename another_x_t, typename another_y_t>
    vec2_t(const another_x_t& _x, const another_y_t& _y) : x{ (coordinates_t)_x }, y{ (coordinates_t)_y } { }

    vec2_t(const std::array<coordinates_t, array_size>& _coordinates) : coordinates{ _coordinates } { }
    vec2_t(const std::vector<coordinates_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), array_size), coordinates.begin()); }

public:
    float length() const { return std::hypot(x, y); }
    float dot(const vec2_t& vec) const { return x * vec.x + y * vec.y; }
    float cross(const vec2_t& vec) const { return x * vec.y - y * vec.x; }

    template <typename another_coordinates_t>
    vec2_t<another_coordinates_t> cast() const { return vec2_t<another_coordinates_t>{ x, y }; }

public:
    template <typename another_coordinates_t>
    operator vec2_t<another_coordinates_t>() const { return cast<another_coordinates_t>(); }

    template <typename self_t> auto&& operator [](this self_t&& self, const int& i) { return self.coordinates[i]; }

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

    template <typename another_coordinates_t> bool operator ==(const vec2_t<another_coordinates_t>& vec) const { return x == vec.x && y == vec.y; };
    template <typename another_t> requires std::is_arithmetic_v<another_t> bool operator ==(const another_t& value) const { return x == value && y == value; };
    class_create_logic_operators(vec, vec2_t, <, { return self.x < vec.x && self.y < vec.y; }, { return self.x <= vec.x && self.y <= vec.y; });
    class_create_logic_operators(vec, vec2_t, >, { return self.x > vec.x && self.y > vec.y; }, { return self.x >= vec.x && self.y >= vec.y; });
};