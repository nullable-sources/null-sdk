#pragma once
#include <cmath>

#include <utils/fast_operators.h>

namespace null::sdk {
	template <typename x_t, typename y_t, typename z_t>
	concept vec3_concept = vec2_concept<x_t, y_t> && std::is_arithmetic_v<z_t>;

	template <typename x_t, typename y_t = x_t, typename z_t = x_t>
		requires vec3_concept<x_t, y_t, z_t>
	class i_vec3 {
	public:
		x_t x{ }; y_t y{ }; z_t z{ };

	public:
		i_vec3() { }

		template <typename t> requires std::is_arithmetic_v<t>
		i_vec3(const t& value) : i_vec3{ value, value, value } { }

		template <typename another_x_t, typename another_y_t, typename another_z_t>  requires vec3_concept<another_x_t, another_y_t, another_z_t>
		i_vec3(const another_x_t& _x, const another_y_t& _y, const another_z_t& _z) : x{ (x_t)_x }, y{ (y_t)_y }, z{ (z_t)_z } { }

	public:
		float length() const { return std::hypot(x, y, z); }
		float dist_to(const i_vec3& vec) const { return i_vec3{ *this - vec }.length(); }
		i_vec3 normalized() const { return { std::isfinite((double)x) ? std::remainder(x, 360.f) : 0.f, std::isfinite((double)y) ? std::remainder(y, 360.f) : 0.f, 0.f }; }
		i_vec3& normalize() { return *this = normalized(); }
		float dot(const i_vec3& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
		i_vec3 cross(const i_vec3& vec) const { return { y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x }; }

		template <typename another_x_t, typename another_y_t, typename another_z_t>
		i_vec3<another_x_t, another_y_t, another_z_t> cast() const { return i_vec3<another_x_t, another_y_t, another_z_t>{ x, y, z }; }

	public:
		template <typename another_x_t, typename another_y_t, typename another_z_t>
		operator i_vec3<another_x_t, another_y_t, another_z_t>() const { return cast<another_x_t, another_y_t, another_z_t>(); }

		template <typename self_t> auto&& operator ++(this self_t&& self) { ++self.x; ++self.y; ++self.z; return self; }
		template <typename self_t> auto operator ++(this self_t&& self, int) { return i_vec3{ self.x++, self.y++, self.z++ }; }
		template <typename self_t> auto&& operator --(this self_t&& self) { --self.x; --self.y; --self.z; return self; }
		template <typename self_t> auto operator --(this self_t&& self, int) { return i_vec3{ self.x--, self.y--, self.z-- }; }

		template <typename self_t> auto operator -(this self_t&& self) { return i_vec3{ -self.x, -self.y, -self.z }; }
		class_create_arithmetic_operators(vec, i_vec3, -, { return i_vec3(self.x - vec.x, self.y - vec.y, self.z - vec.z); });
		class_create_arithmetic_operators(vec, i_vec3, +, { return i_vec3(self.x + vec.x, self.y + vec.y, self.z + vec.z); });
		class_create_arithmetic_operators(vec, i_vec3, *, { return i_vec3(self.x * vec.x, self.y * vec.y, self.z * vec.z); });
		class_create_arithmetic_operators(vec, i_vec3, /, { return i_vec3(self.x / vec.x, self.y / vec.y, self.z / vec.z); });
		class_create_arithmetic_operators(vec, i_vec3, %, { return i_vec3(self.x % vec.x, self.y % vec.y, self.z % vec.z); });

		template <typename another_x_t, typename another_y_t, typename another_z_t> bool operator ==(const i_vec3<another_x_t, another_y_t, another_z_t>& vec) const { return x == vec.x && y == vec.y && z == vec.z; };
		template <typename another_t> requires vec2_concept<another_t, another_t> bool operator ==(const another_t& value) const { return x == value && y == value && z == value; };
		class_create_logic_operators(vec, i_vec3, <, { return self.x < vec.x && self.y < vec.y && self.z < vec.z; }, { return self.x <= vec.x && self.y <= vec.y && self.z <= vec.z; });
		class_create_logic_operators(vec, i_vec3, >, { return self.x > vec.x && self.y > vec.y && self.z > vec.z; }, { return self.x >= vec.x && self.y >= vec.y && self.z >= vec.z; });
	};
}

using vec3_t = null::sdk::i_vec3<float>;