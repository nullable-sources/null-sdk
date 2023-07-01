module;
#include <array>
#include <vector>
#include <cmath>

#include <utils/fast_operators.h>
export module null.sdk:math.vec3;

import :utils.compatibility_type_converter;
import :math.vec2;

export template <typename coordinates_t>
struct vec3_t {
public:
	static constexpr size_t array_size{ 3 }; //@note: size array{ x, y, z }

public:
	union {
		struct { coordinates_t x, y, z; };
		std::array<coordinates_t, array_size> coordinates;
	};

public:
	vec3_t() { }

	vec3_t(coordinates_t value) : vec3_t{ value, value, value } { }
	vec3_t(coordinates_t _x, coordinates_t _y, coordinates_t _z = { }) : x{ _x }, y{ _y }, z{ _z } { }

	vec3_t(const std::tuple<coordinates_t, coordinates_t, coordinates_t>& tuple) : x{ std::get<0>(tuple) }, y{ std::get<1>(tuple) }, z{ std::get<2>(tuple) } { }
	vec3_t(const std::tuple<coordinates_t, coordinates_t>& tuple, coordinates_t _z = { }) : x{ std::get<0>(tuple) }, y{ std::get<1>(tuple) }, z{ _z } { }
	vec3_t(const vec2_t<coordinates_t>& vec, coordinates_t _z = { }) : x{ vec.x }, y{ vec.y }, z{ _z } { }

	vec3_t(const std::array<coordinates_t, array_size>& _coordinates) : coordinates{ _coordinates } { }
	vec3_t(const std::vector<coordinates_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), array_size), coordinates.begin()); }

	template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<type_t, vec3_t<coordinates_t>>
	vec3_t(const type_t& value) { *this = null::compatibility::data_type_converter_t<type_t, vec3_t<coordinates_t>>::convert(value); }

public:
	float length() const { return std::hypot(x, y, z); }
	float dist_to(const vec3_t<coordinates_t>& vec) const { return vec3_t{ *this - vec }.length(); }
	float dot(const vec3_t<coordinates_t>& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
	vec3_t<coordinates_t> cross(const vec3_t<coordinates_t>& vec) const { return { y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x }; }

	vec3_t<coordinates_t> normalized() const { return *this / vec3_t<float>{ length() }; }
	void normalize() { *this /= length(); }

public: //@note: converter opereators and methods
	auto xy() const { return vec2_t<coordinates_t>{ x, y }; }

	template <typename another_coordinates_t> operator vec3_t<another_coordinates_t>() const { return vec3_t<another_coordinates_t>{ (another_coordinates_t)x, (another_coordinates_t)y, (another_coordinates_t)z }; }
	template <typename another_coordinates_t> operator vec2_t<another_coordinates_t>() const { return vec2_t<another_coordinates_t>{ (another_coordinates_t)x, (another_coordinates_t)y }; }
	operator std::tuple<coordinates_t, coordinates_t, coordinates_t>() const { return std::make_tuple(x, y, z); }

	template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<vec3_t<coordinates_t>, type_t>
	operator type_t() const { return null::compatibility::data_type_converter_t<vec3_t<coordinates_t>, type_t>::convert(*this); }

public:
	//@todo: P0847
	auto& operator [](const int& i) const { return coordinates[i]; }
	auto& operator [](const int& i) { return coordinates[i]; }

	auto& operator ++() { ++x; ++y; ++z; return *this; }
	auto operator ++(int) const { return vec3_t<coordinates_t>{ x++, y++, z++ }; }
	auto& operator --() { --x; --y; --z; return *this; }
	auto operator --(int) const { return vec3_t<coordinates_t>{ x--, y--, z-- }; }
	auto operator -() const { return vec3_t<coordinates_t>{ -x, -y, -z }; }

#define fast_arithmetic_operators(op)																																									\
	class_create_arithmetic_operators_template(vec, vec3_t<another_coordinates_t>, op, { return vec3_t<another_coordinates_t>(x op vec.x, y op vec.y, z op vec.z); }, typename another_coordinates_t);	\
	class_create_arithmetic_operators_template(value, another_coordinates_t, op, { return vec3_t<coordinates_t>(x op value, y op value, z op value); }, typename another_coordinates_t);				\

	fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(*); fast_arithmetic_operators(/ ); fast_arithmetic_operators(%);

	template <typename another_coordinates_t> bool operator ==(const vec3_t<another_coordinates_t>& vec) const { return x == vec.x && y == vec.y && z == vec.z; };
	template <typename another_t> requires std::is_arithmetic_v<another_t> bool operator ==(const another_t& value) const { return x == value && y == value && z == value; };

#define fast_logic_operators(op)																																																	\
	class_create_logic_operators_template(vec, vec3_t<another_coordinates_t>, op, { return x op vec.x && y op vec.y && z op vec.z; }, { return x op##= vec.x && y op##= vec.y && z op##= vec.z; }, typename another_coordinates_t);	\
	class_create_logic_operators_template(value, another_coordinates_t, op, { return x op value && y op value && z op value; }, { return x op## = value && y op## = value && z op## = value; }, typename another_coordinates_t);	\

	fast_logic_operators(< ); fast_logic_operators(> );
};