#pragma once
#include <cmath>
#include <span>
#include <utils/fast_operators.h>

template <typename x_t = float, typename y_t = x_t, typename z_t = x_t, typename w_t = x_t>
struct vec4_t {
public:
	x_t x{ }; y_t y{ }; z_t z{ }; w_t w{ };

public:
	vec4_t() { }

	template <typename t> requires std::is_arithmetic_v<t>
	vec4_t(const t& value) : vec4_t{ value, value, value, value } { }

	template <typename another_x_t, typename another_y_t, typename another_z_t, typename another_w_t>
	vec4_t(const another_x_t& _x, const another_y_t& _y, const another_z_t& _z, const another_w_t _w) : x{ (x_t)_x }, y{ (y_t)_y }, z{ (z_t)_z }, w{ (w_t)_w } { }

public:
	float length() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2)); }
	float dist_to(const vec4_t& vec) const { return vec4_t{ *this - vec }.length(); }
	float dot(const vec4_t& vec) const { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; }

	template <typename another_x_t, typename another_y_t, typename another_z_t, typename another_w_t>
	vec4_t<another_x_t, another_y_t, another_z_t, another_w_t> cast() const { return vec4_t<another_x_t, another_y_t, another_z_t, another_w_t>{ x, y, z, w }; }

public:
	template <typename another_x_t, typename another_y_t, typename another_z_t, typename another_w_t>
	operator vec4_t<another_x_t, another_y_t, another_z_t, another_w_t>() const { return cast<another_x_t, another_y_t, another_z_t, another_w_t>(); }

	template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.x; ++self.y; ++self.z; ++self.w; return self; }
	template <typename self_t> auto operator ++(this self_t&& self, int) { return vec4_t{ self.x++, self.y++, self.z++, self.w++ }; }
	template <typename self_t> auto&& operator --(this self_t&& self) { --self.x; --self.y; --self.z; --self.w; return self; }
	template <typename self_t> auto operator --(this self_t&& self, int) { return vec4_t{ self.x--, self.y--, self.z--, self.w-- }; }

	template <typename self_t> auto operator -(this self_t&& self) { return vec4_t{ -self.x, -self.y, -self.z, -self.w }; }
	class_create_arithmetic_operators(vec, vec4_t, -, { return vec4_t(self.x - vec.x, self.y - vec.y, self.z - vec.z, self.w - vec.w); });
	class_create_arithmetic_operators(vec, vec4_t, +, { return vec4_t(self.x + vec.x, self.y + vec.y, self.z + vec.z, self.w + vec.w); });
	class_create_arithmetic_operators(vec, vec4_t, *, { return vec4_t(self.x * vec.x, self.y * vec.y, self.z * vec.z, self.w * vec.w); });
	class_create_arithmetic_operators(vec, vec4_t, /, { return vec4_t(self.x / vec.x, self.y / vec.y, self.z / vec.z, self.w / vec.w); });
	class_create_arithmetic_operators(vec, vec4_t, %, { return vec4_t(self.x % vec.x, self.y % vec.y, self.z % vec.z, self.w % vec.w); });

	template <typename another_x_t, typename another_y_t, typename another_z_t, typename another_w_t> bool operator ==(const vec4_t<another_x_t, another_y_t, another_z_t, another_w_t>& vec) const { return x == vec.x && y == vec.y && z == vec.z && w == vec.w; };
	template <typename another_t> requires std::is_arithmetic_v<another_t> bool operator ==(const another_t& value) const { return x == value && y == value && z == value && w == value; };
	class_create_logic_operators(vec, vec4_t, <, { return self.x < vec.x && self.y < vec.y && self.z < vec.z && self.w < vec.w; }, { return self.x <= vec.x && self.y <= vec.y && self.z <= vec.z && self.w <= vec.w; });
	class_create_logic_operators(vec, vec4_t, >, { return self.x > vec.x && self.y > vec.y && self.z > vec.z && self.w > vec.w; }, { return self.x >= vec.x && self.y >= vec.y && self.z >= vec.z && self.w >= vec.w; });
};