#pragma once
#include <cmath>
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

	template <typename t> requires std::is_same_v<t, coordinates_t> || std::is_convertible_v<t, coordinates_t>
	vec3_t(const t& value) : vec3_t{ value, value, value } { }

	template <typename x_t, typename y_t, typename z_t>
	vec3_t(const x_t& _x, const y_t& _y, const z_t& _z) : x{ (coordinates_t)_x }, y{ (coordinates_t)_y }, z{ (coordinates_t)_z } { }

	vec3_t(const std::array<coordinates_t, array_size>& _coordinates) : coordinates{ _coordinates } { }
	vec3_t(const std::vector<coordinates_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), array_size), coordinates.begin()); }

public:
	float length() const { return std::hypot(x, y, z); }
	float dist_to(const vec3_t& vec) const { return vec3_t{ *this - vec }.length(); }
	vec3_t normalized() const { return { std::isfinite((double)x) ? std::remainder(x, 360.f) : 0.f, std::isfinite((double)y) ? std::remainder(y, 360.f) : 0.f, 0.f }; }
	vec3_t& normalize() { return *this = normalized(); }
	float dot(const vec3_t& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
	vec3_t cross(const vec3_t& vec) const { return { y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x }; }

	template <typename another_coordinates_t>
	vec3_t<another_coordinates_t> cast() const { return vec3_t<another_coordinates_t>{ x, y, z }; }

public:
	template <typename another_coordinates_t>
	operator vec3_t<another_coordinates_t>() const { return cast<another_coordinates_t>(); }

	template <typename self_t> auto&& operator [](this self_t&& self, const int& i) { return self.coordinates[i]; }

	template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.x; ++self.y; ++self.z; return self; }
	template <typename self_t> auto operator ++(this self_t&& self, int) { return vec3_t{ self.x++, self.y++, self.z++ }; }
	template <typename self_t> auto&& operator --(this self_t&& self) { --self.x; --self.y; --self.z; return self; }
	template <typename self_t> auto operator --(this self_t&& self, int) { return vec3_t{ self.x--, self.y--, self.z-- }; }

	template <typename self_t> auto operator -(this self_t&& self) { return vec3_t{ -self.x, -self.y, -self.z }; }
	class_create_arithmetic_operators(vec, vec3_t, -, { return vec3_t(self.x - vec.x, self.y - vec.y, self.z - vec.z); });
	class_create_arithmetic_operators(vec, vec3_t, +, { return vec3_t(self.x + vec.x, self.y + vec.y, self.z + vec.z); });
	class_create_arithmetic_operators(vec, vec3_t, *, { return vec3_t(self.x * vec.x, self.y * vec.y, self.z * vec.z); });
	class_create_arithmetic_operators(vec, vec3_t, /, { return vec3_t(self.x / vec.x, self.y / vec.y, self.z / vec.z); });
	class_create_arithmetic_operators(vec, vec3_t, %, { return vec3_t(self.x % vec.x, self.y % vec.y, self.z % vec.z); });

	template <typename another_coordinates_t> bool operator ==(const vec3_t<another_coordinates_t>& vec) const { return x == vec.x && y == vec.y && z == vec.z; };
	template <typename another_t> requires std::is_arithmetic_v<another_t> bool operator ==(const another_t& value) const { return x == value && y == value && z == value; };
	class_create_logic_operators(vec, vec3_t, <, { return self.x < vec.x && self.y < vec.y && self.z < vec.z; }, { return self.x <= vec.x && self.y <= vec.y && self.z <= vec.z; });
	class_create_logic_operators(vec, vec3_t, >, { return self.x > vec.x && self.y > vec.y && self.z > vec.z; }, { return self.x >= vec.x && self.y >= vec.y && self.z >= vec.z; });
};