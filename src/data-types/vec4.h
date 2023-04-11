#pragma once
#include <cmath>
#include <span>
#include <data-types/vec2.h>
#include <utils/fast_operators.h>

template <typename coordinates_t = float>
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

	vec4_t(const coordinates_t& value) : vec4_t{ value, value, value, value } { }
	vec4_t(const coordinates_t& _x, const coordinates_t& _y, const coordinates_t& _z, const coordinates_t& _w) : x{ _x }, y{ _y }, z{ _z }, w{ _w } { }

	vec4_t(const std::array<coordinates_t, array_size>& _coordinates) : coordinates{ _coordinates } { }
	vec4_t(const std::vector<coordinates_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), array_size), coordinates.begin()); }
	
	template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<type_t, vec4_t<coordinates_t>>
	vec4_t(const type_t& value) { *this = null::compatibility::data_type_converter_t<type_t, vec4_t<coordinates_t>>::convert(value); }

public:
	float length() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2)); }
	float dist_to(const vec4_t& vec) const { return vec4_t{ *this - vec }.length(); }
	float dot(const vec4_t& vec) const { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; }

	template <typename self_t> vec4_t<coordinates_t> normalized(this self_t&& self) { return self / self.length(); }
	template <typename self_t> void normalize(this self_t&& self) { self /= self.length(); }

public:
	template <typename another_coordinates_t>
	operator vec4_t<another_coordinates_t>() const { return vec4_t<another_coordinates_t>{ (another_coordinates_t)x, (another_coordinates_t)y, (another_coordinates_t)z, (another_coordinates_t)w }; }

	template <typename type_t> requires null::compatibility::data_type_converter_defined_concept<vec4_t<coordinates_t>, type_t>
	operator type_t() const { return null::compatibility::data_type_converter_t<vec4_t<coordinates_t>, type_t>::convert(*this); }

	template <typename self_t> auto&& operator [](this self_t&& self, const int& i) { return self.coordinates[i]; }

	template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.x; ++self.y; ++self.z; ++self.w; return self; }
	template <typename self_t> auto operator ++(this self_t&& self, int) { return vec4_t{ self.x++, self.y++, self.z++, self.w++ }; }
	template <typename self_t> auto&& operator --(this self_t&& self) { --self.x; --self.y; --self.z; --self.w; return self; }
	template <typename self_t> auto operator --(this self_t&& self, int) { return vec4_t{ self.x--, self.y--, self.z--, self.w-- }; }

	template <typename self_t> auto operator -(this self_t&& self) { return vec4_t{ -self.x, -self.y, -self.z, -self.w }; }
#define fast_arithmetic_operators(op) class_create_arithmetic_operators(vec, vec4_t, op, { return vec4_t(self.x op vec.x, self.y op vec.y, self.z op vec.z, self.w op vec.w); });
	fast_arithmetic_operators(-); fast_arithmetic_operators(+); fast_arithmetic_operators(*); fast_arithmetic_operators(/); fast_arithmetic_operators(%);

	template <typename another_coordinates_t> bool operator ==(const vec4_t<another_coordinates_t>& vec) const { return x == vec.x && y == vec.y && z == vec.z && w == vec.w; };
	template <typename t> bool operator ==(const t& value) const { return x == value && y == value && z == value && w == value; };
#define fast_logic_operators(op) class_create_logic_operators(vec, vec4_t, op, { return self.x op vec.x && self.y op vec.y && self.z op vec.z && self.w op vec.w; }, { return self.x op##= vec.x && self.y op##= vec.y && self.z op##= vec.z && self.w op##= vec.w; });
	fast_logic_operators(<); fast_logic_operators(>);
};