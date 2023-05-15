#pragma once
#include <cmath>
#include <data-types/vec2.h>
#include <utils/fast_operators.h>

template <typename coordinates_t = float>
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

	vec3_t(const coordinates_t& value) : vec3_t{ value, value, value } { }
	vec3_t(const coordinates_t& _x, const coordinates_t& _y, const coordinates_t& _z) : x{ _x }, y{ _y }, z{ _z } { }
	
	vec3_t(const std::tuple<coordinates_t, coordinates_t, coordinates_t>& tuple) : x{ std::get<0>(tuple) }, y{ std::get<1>(tuple) }, z{ std::get<2>(tuple) } { }
	vec3_t(const std::tuple<coordinates_t, coordinates_t>& tuple, const coordinates_t& _z = { }) : x{ std::get<0>(tuple) }, y{ std::get<1>(tuple) }, z{ _z } { }
	vec3_t(const vec2_t<coordinates_t>& vec, const coordinates_t& _z = { }) : x{ vec.x }, y{ vec.y }, z{ _z } { }

	vec3_t(const std::array<coordinates_t, array_size>& _coordinates) : coordinates{ _coordinates } { }
	vec3_t(const std::vector<coordinates_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), array_size), coordinates.begin()); }

	template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<type_t, vec3_t<coordinates_t>>
	vec3_t(const type_t& value) { *this = null::compatibility::data_type_converter_t<type_t, vec3_t<coordinates_t>>::convert(value); }

public:
	float length() const { return std::hypot(x, y, z); }
	float dist_to(const vec3_t<coordinates_t>& vec) const { return vec3_t{ *this - vec }.length(); }
	float dot(const vec3_t<coordinates_t>& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
	vec3_t<coordinates_t> cross(const vec3_t<coordinates_t>& vec) const { return { y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x }; }

	template <typename self_t> vec3_t<coordinates_t> normalized(this self_t&& self) { return self / self.length(); }
	template <typename self_t> void normalize(this self_t&& self) { self /= self.length(); }

public:
	template <typename self_t> auto xy(this self_t&& self) { return vec2_t<coordinates_t>{ self.x, self.y }; }

public:
	template <typename another_coordinates_t>
	operator vec3_t<another_coordinates_t>() const { return vec3_t<another_coordinates_t>{ (another_coordinates_t)x, (another_coordinates_t)y, (another_coordinates_t)z }; }
	operator std::tuple<coordinates_t, coordinates_t, coordinates_t>() const { return std::make_tuple(x, y, z); }

	template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<vec3_t<coordinates_t>, type_t>
	operator type_t() const { return null::compatibility::data_type_converter_t<vec3_t<coordinates_t>, type_t>::convert(*this); }

	template <typename self_t> auto&& operator [](this self_t&& self, const int& i) { return self.coordinates[i]; }

	template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.x; ++self.y; ++self.z; return self; }
	template <typename self_t> auto operator ++(this self_t&& self, int) { return vec3_t{ self.x++, self.y++, self.z++ }; }
	template <typename self_t> auto&& operator --(this self_t&& self) { --self.x; --self.y; --self.z; return self; }
	template <typename self_t> auto operator --(this self_t&& self, int) { return vec3_t{ self.x--, self.y--, self.z-- }; }

	template <typename self_t> auto operator -(this self_t&& self) { return vec3_t{ -self.x, -self.y, -self.z }; }
#define fast_arithmetic_operators(op) class_create_arithmetic_operators(vec, vec3_t, op, { return vec3_t(self.x op vec.x, self.y op vec.y, self.z op vec.z); });
	fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(*); fast_arithmetic_operators(/); fast_arithmetic_operators(%);

	template <typename another_coordinates_t> bool operator ==(const vec3_t<another_coordinates_t>& vec) const { return x == vec.x && y == vec.y && z == vec.z; };
	template <typename another_t> requires std::is_arithmetic_v<another_t> bool operator ==(const another_t& value) const { return x == value && y == value && z == value; };
#define fast_logic_operators(op) class_create_logic_operators(vec, vec3_t, op, { return self.x op vec.x && self.y op vec.y && self.z op vec.z; }, { return self.x op##= vec.x && self.y op##= vec.y && self.z op##= vec.z; });
	fast_logic_operators(<); fast_logic_operators(>);
};