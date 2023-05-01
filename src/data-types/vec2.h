#pragma once
#include <cmath>
#include <array>
#include <vector>

#include <utils/compatibility/data-type-converter.h>
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
    
    //@note:    In general, you can leave the old constructors, but vs does not work well with requires, which causes errors (which do not affect compilation),
    //          so as soon as vs improves on requires, it will be possible to return the old constructors
    vec2_t(const coordinates_t& value) : vec2_t{ value, value } { }
    vec2_t(const coordinates_t& _x, const coordinates_t& _y) : x{ _x }, y{ _y } { }

    vec2_t(const std::array<coordinates_t, array_size>& _coordinates) : coordinates{ _coordinates } { }
    vec2_t(const std::vector<coordinates_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), array_size), coordinates.begin()); }

    template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<type_t, vec2_t<coordinates_t>>
    vec2_t(const type_t& value) { *this = null::compatibility::data_type_converter_t<type_t, vec2_t<coordinates_t>>::convert(value); }

public:
    float length() const { return std::hypot(x, y); }
    float dot(const vec2_t<coordinates_t>& vec) const { return x * vec.x + y * vec.y; }
    float cross(const vec2_t<coordinates_t>& vec) const { return x * vec.y - y * vec.x; }

    template <typename self_t> vec2_t<coordinates_t> direction(this self_t&& self, const vec2_t<coordinates_t>& to) { return vec2_t<coordinates_t>{ to - self }.normalized(); }

    template <typename self_t> vec2_t<coordinates_t> normalized(this self_t&& self) { return self / self.length(); }
    template <typename self_t> void normalize(this self_t&& self) { self /= self.length(); }

public:
    template <typename another_coordinates_t>
    operator vec2_t<another_coordinates_t>() const { return vec2_t<another_coordinates_t>{ (another_coordinates_t)x, (another_coordinates_t)y }; }

    template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<vec2_t<coordinates_t>, type_t>
    operator type_t() const { return null::compatibility::data_type_converter_t<vec2_t<coordinates_t>, type_t>::convert(*this); }

    template <typename self_t> auto&& operator [](this self_t&& self, const int& i) { return self.coordinates[i]; }

    template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.x; ++self.y; return self; }
    template <typename self_t> auto operator ++(this self_t&& self, int) { return vec2_t{ self.x++, self.y++ }; }
    template <typename self_t> auto&& operator --(this self_t&& self) { --self.x; --self.y; return self; }
    template <typename self_t> auto operator --(this self_t&& self, int) { return vec2_t{ self.x--, self.y-- }; }

    template <typename self_t> auto operator -(this self_t&& self) { return vec2_t{ -self.x, -self.y }; }
#define fast_arithmetic_operators(op) class_create_arithmetic_operators(vec, vec2_t, op, { return vec2_t(self.x op vec.x, self.y op vec.y); });
    fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(*); fast_arithmetic_operators(/); fast_arithmetic_operators(%);

    template <typename another_coordinates_t> bool operator ==(const vec2_t<another_coordinates_t>& vec) const { return x == vec.x && y == vec.y; };
    template <typename another_t> requires std::is_arithmetic_v<another_t> bool operator ==(const another_t& value) const { return x == value && y == value; };
#define fast_logic_operators(op) class_create_logic_operators(vec, vec2_t, op, { return self.x op vec.x && self.y op vec.y; }, { return self.x op##= vec.x && self.y op##= vec.y; });
    fast_logic_operators(<); fast_logic_operators(>);
};