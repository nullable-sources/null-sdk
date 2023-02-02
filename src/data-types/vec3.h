#pragma once
#include <cmath>
#include <utils/fast_operators.h>

template <typename x_t = float, typename y_t = x_t, typename z_t = x_t>
struct vec3_t {
public:
	x_t x{ }; y_t y{ }; z_t z{ };

public:
	vec3_t() { }

	template <typename t> requires std::is_arithmetic_v<t>
	vec3_t(const t& value) : vec3_t{ value, value, value } { }

	template <typename another_x_t, typename another_y_t, typename another_z_t>
	vec3_t(const another_x_t& _x, const another_y_t& _y, const another_z_t& _z) : x{ (x_t)_x }, y{ (y_t)_y }, z{ (z_t)_z } { }

public:
	float length() const { return std::hypot(x, y, z); }
	float dist_to(const vec3_t& vec) const { return vec3_t{ *this - vec }.length(); }
	vec3_t normalized() const { return { std::isfinite((double)x) ? std::remainder(x, 360.f) : 0.f, std::isfinite((double)y) ? std::remainder(y, 360.f) : 0.f, 0.f }; }
	vec3_t& normalize() { return *this = normalized(); }
	float dot(const vec3_t& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
	vec3_t cross(const vec3_t& vec) const { return { y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x }; }

	template <typename another_x_t, typename another_y_t, typename another_z_t>
	vec3_t<another_x_t, another_y_t, another_z_t> cast() const { return vec3_t<another_x_t, another_y_t, another_z_t>{ x, y, z }; }

public:
	template <typename another_x_t, typename another_y_t, typename another_z_t>
	operator vec3_t<another_x_t, another_y_t, another_z_t>() const { return cast<another_x_t, another_y_t, another_z_t>(); }

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

	template <typename another_x_t, typename another_y_t, typename another_z_t> bool operator ==(const vec3_t<another_x_t, another_y_t, another_z_t>& vec) const { return x == vec.x && y == vec.y && z == vec.z; };
	template <typename another_t> requires std::is_arithmetic_v<another_t> bool operator ==(const another_t& value) const { return x == value && y == value && z == value; };
	class_create_logic_operators(vec, vec3_t, <, { return self.x < vec.x && self.y < vec.y && self.z < vec.z; }, { return self.x <= vec.x && self.y <= vec.y && self.z <= vec.z; });
	class_create_logic_operators(vec, vec3_t, >, { return self.x > vec.x && self.y > vec.y && self.z > vec.z; }, { return self.x >= vec.x && self.y >= vec.y && self.z >= vec.z; });
};