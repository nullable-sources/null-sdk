module;
#include <array>
#include <vector>
#include <cmath>

#include <utils/fast_operators.h>
export module null.sdk:math.vec2;

import :utils.compatibility_type_converter;

export template <typename coordinates_t>
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
    vec2_t(coordinates_t value) : vec2_t{ value, value } { }
    vec2_t(coordinates_t _x, coordinates_t _y) : x{ _x }, y{ _y } { }
    vec2_t(const std::tuple<coordinates_t, coordinates_t>& tuple) : x{ std::get<0>(tuple) }, y{ std::get<1>(tuple) } { }

    vec2_t(const std::array<coordinates_t, array_size>& _coordinates) : coordinates{ _coordinates } { }
    vec2_t(const std::vector<coordinates_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), array_size), coordinates.begin()); }

    template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<type_t, vec2_t<coordinates_t>>
    vec2_t(const type_t& value) { *this = null::compatibility::data_type_converter_t<type_t, vec2_t<coordinates_t>>::convert(value); }

public:
    float length() const { return std::hypot(x, y); }
    float dot(const vec2_t<coordinates_t>& vec) const { return x * vec.x + y * vec.y; }
    float cross(const vec2_t<coordinates_t>& vec) const { return x * vec.y - y * vec.x; }

    vec2_t<coordinates_t> direction(const vec2_t<coordinates_t>& to) const { return vec2_t<coordinates_t>{ to - *this }.normalized(); }

    vec2_t<coordinates_t> normalized() const { return *this / length(); }
    void normalize() { *this /= length(); }

public: //@note: converter opereators and methods
    template <typename another_coordinates_t> operator vec2_t<another_coordinates_t>() const { return vec2_t<another_coordinates_t>{ (another_coordinates_t)x, (another_coordinates_t)y }; }
    operator std::tuple<coordinates_t, coordinates_t>() const { return std::make_tuple(x, y); }

    template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<vec2_t<coordinates_t>, type_t>
    operator type_t() const { return null::compatibility::data_type_converter_t<vec2_t<coordinates_t>, type_t>::convert(*this); }

public:
    //@todo: P0847
    auto& operator [](int i) const { return coordinates[i]; }
    auto& operator [](int i) { return coordinates[i]; }

    auto&& operator ++() { ++x; ++y; return *this; }
    auto operator ++(int) const { return vec2_t{ x++, y++ }; }
    auto&& operator --() { --x; --y; return *this; }
    auto operator --(int) const { return vec2_t{ x--, y-- }; }
    auto operator -() const { return vec2_t{ -x, -y }; }

#define fast_arithmetic_operators(op)                                                                                                                                                       \
	class_create_arithmetic_operators_template(vec, vec2_t<another_coordinates_t>, op, { return vec2_t<another_coordinates_t>(x op vec.x, y op vec.y); }, typename another_coordinates_t);  \
	class_create_arithmetic_operators_template(value, another_coordinates_t, op, { return vec2_t<coordinates_t>(x op value, y op value); }, typename another_coordinates_t);                \

    fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(*); fast_arithmetic_operators(/ ); fast_arithmetic_operators(%);

    template <typename another_coordinates_t> bool operator ==(const vec2_t<another_coordinates_t>& vec) const { return x == vec.x && y == vec.y; };
    template <typename another_t> requires std::is_arithmetic_v<another_t> bool operator ==(const another_t& value) const { return x == value && y == value; };

#define fast_logic_operators(op)                                                                                                                                                                        \
	class_create_logic_operators_template(vec, vec2_t<another_coordinates_t>, op, { return x op vec.x && y op vec.y; }, { return x op##= vec.x && y op##= vec.y; }, typename another_coordinates_t);    \
    class_create_logic_operators_template(value, another_coordinates_t, op, { return x op value && y op value; }, { return x op##= value && y op##= value; }, typename another_coordinates_t);          \

    fast_logic_operators(< ); fast_logic_operators(> );
};