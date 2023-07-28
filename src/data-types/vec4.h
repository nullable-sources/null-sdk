#pragma once
#include <cmath>
#include <data-types/vec3.h>
#include <utils/fast_operators.h>

template <typename coordinates_t>
struct vec4_t {
public:
	static constexpr size_t array_size{ 4 }; //@note: size array{ x, y, z, w }

public:
	union {
		struct { coordinates_t x, y, z, w; };
		std::array<coordinates_t, array_size> coordinates{ };
	};

public:
	vec4_t() { }

	vec4_t(coordinates_t value) : vec4_t{ value, value, value, value } { }
	vec4_t(coordinates_t _x, coordinates_t _y, coordinates_t _z, coordinates_t _w) : x{ _x }, y{ _y }, z{ _z }, w{ _w } { }
	
	vec4_t(const std::tuple<coordinates_t, coordinates_t, coordinates_t, coordinates_t>& tuple) : x{ std::get<0>(tuple) }, y{ std::get<1>(tuple) }, z{ std::get<2>(tuple) }, w{ std::get<3>(tuple) } { }
	vec4_t(const std::tuple<coordinates_t, coordinates_t, coordinates_t>& tuple, coordinates_t _w = { }) : x{ std::get<0>(tuple) }, y{ std::get<1>(tuple) }, z{ std::get<2>(tuple) }, w{ _w } { }
	vec4_t(const std::tuple<coordinates_t, coordinates_t>& tuple, coordinates_t _z = { }, coordinates_t _w = { }) : x{ std::get<0>(tuple) }, y{ std::get<1>(tuple) }, z{ _z }, w{ _w } { }
	vec4_t(const vec3_t<coordinates_t>& vec, coordinates_t _w = { }) : x{ vec.x }, y{ vec.y }, z{ vec.z }, w{ _w } { }
	vec4_t(const vec2_t<coordinates_t>& vec, coordinates_t _z = { }, coordinates_t _w = { }) : x{ vec.x }, y{ vec.y }, z{ _z }, w{ _w } { }

	vec4_t(const std::array<coordinates_t, array_size>& _coordinates) : coordinates{ _coordinates } { }
	vec4_t(const std::vector<coordinates_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), array_size), coordinates.begin()); }
	
	template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<type_t, vec4_t<coordinates_t>>
	vec4_t(const type_t& value) { *this = null::compatibility::data_type_converter_t<type_t, vec4_t<coordinates_t>>::convert(value); }

public:
	float length() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2)); }
	float dist_to(const vec4_t& vec) const { return vec4_t{ *this - vec }.length(); }
	float dot(const vec4_t& vec) const { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; }

	vec4_t<coordinates_t> normalized(this auto&& self) { return self / self.length(); }
	void normalize(this auto&& self) { self /= self.length(); }

public:
	auto xy(this auto&& self) { return vec2_t<coordinates_t>{ self.x, self.y }; }
	auto xyz(this auto&& self) { return vec3_t<coordinates_t>{ self.x, self.y, self.z }; }

public:
	template <typename another_coordinates_t> operator vec4_t<another_coordinates_t>() const { return vec4_t<another_coordinates_t>{ (another_coordinates_t)x, (another_coordinates_t)y, (another_coordinates_t)z, (another_coordinates_t)w }; }
	template <typename another_coordinates_t> operator vec3_t<another_coordinates_t>() const { return vec3_t<another_coordinates_t>{ (another_coordinates_t)x, (another_coordinates_t)y, (another_coordinates_t)z }; }
	template <typename another_coordinates_t> operator vec2_t<another_coordinates_t>() const { return vec2_t<another_coordinates_t>{ (another_coordinates_t)x, (another_coordinates_t)y }; }	
	operator std::tuple<coordinates_t, coordinates_t, coordinates_t, coordinates_t>() const { return std::make_tuple(x, y, z, w); }

	template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<vec4_t<coordinates_t>, type_t>
	operator type_t() const { return null::compatibility::data_type_converter_t<vec4_t<coordinates_t>, type_t>::convert(*this); }

	auto&& operator [](this auto&& self, const int& i) { return self.coordinates[i]; }

	auto&& operator ++(this auto&& self) { ++self.x; ++self.y; ++self.z; ++self.w; return self; }
	auto operator ++(this auto&& self, int) { return vec4_t{ self.x++, self.y++, self.z++, self.w++ }; }
	auto&& operator --(this auto&& self) { --self.x; --self.y; --self.z; --self.w; return self; }
	auto operator --(this auto&& self, int) { return vec4_t{ self.x--, self.y--, self.z--, self.w-- }; }

	auto operator -(this auto&& self) { return vec4_t{ -self.x, -self.y, -self.z, -self.w }; }
#define fast_arithmetic_operators(op)																																																					\
	class_create_arithmetic_operators_template(vec, vec4_t, op, { return vec4_t<coordinates_t>(self.x op vec.x, self.y op vec.y, self.z op vec.z, self.w op vec.w); }, typename another_coordinates_t);													\
	class_create_arithmetic_operators_template(coordinates, another_coordinates_t, op, { return vec4_t<coordinates_t>(self.x op coordinates, self.y op coordinates, self.z op coordinates, self.w op coordinates); }, typename another_coordinates_t);	\

	fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(*); fast_arithmetic_operators(/); fast_arithmetic_operators(%);

	template <typename another_coordinates_t> bool operator ==(const vec4_t<another_coordinates_t>& vec) const { return x == vec.x && y == vec.y && z == vec.z && w == vec.w; };
	template <typename t> bool operator ==(const t& value) const { return x == value && y == value && z == value && w == value; };
#define fast_logic_operators(op)																																																																															\
	class_create_logic_operators_template(vec, vec4_t<another_coordinates_t>, op, { return self.x op vec.x && self.y op vec.y && self.z op vec.z && self.w op vec.w; }, { return self.x op##= vec.x && self.y op##= vec.y && self.z op##= vec.z && self.w op##= vec.w; }, typename another_coordinates_t);													\
	class_create_logic_operators_template(coordinates, another_coordinates_t, op, { return self.x op coordinates && self.y op coordinates && self.z op coordinates && self.w op coordinates; }, { return self.x op##= coordinates && self.y op##= coordinates && self.z op##= coordinates && self.w op##= coordinates; }, typename another_coordinates_t);	\

	fast_logic_operators(<); fast_logic_operators(>);
};