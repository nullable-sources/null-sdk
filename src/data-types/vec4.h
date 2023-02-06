#pragma once
#include <cmath>
#include <span>
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

	template <typename t> requires std::is_same_v<t, coordinates_t> || std::is_convertible_v<t, coordinates_t>
	vec4_t(const t& value) : vec4_t{ value, value, value, value } { }

	template <typename x_t, typename y_t, typename z_t, typename w_t>
	vec4_t(const x_t& _x, const y_t& _y, const z_t& _z, const w_t& _w) : x{ (const coordinates_t&)_x }, y{ (const coordinates_t&)_y }, z{ (const coordinates_t&)_z }, w{ (const coordinates_t&)_w } { }

	vec4_t(const std::array<coordinates_t, array_size>& _coordinates) : coordinates{ _coordinates } { }
	vec4_t(const std::vector<coordinates_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), array_size), coordinates.begin()); }

public:
	float length() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2)); }
	float dist_to(const vec4_t& vec) const { return vec4_t{ *this - vec }.length(); }
	float dot(const vec4_t& vec) const { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; }

	template <typename another_coordinates_t>
	vec4_t<another_coordinates_t> cast() const { return vec4_t<another_coordinates_t>{ x, y, z, w }; }

public:
	template <typename another_coordinates_t>
	operator vec4_t<another_coordinates_t>() const { return cast<another_coordinates_t>(); }

	template <typename self_t> auto&& operator [](this self_t&& self, const int& i) { return self.coordinates[i]; }

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

	template <typename another_coordinates_t> bool operator ==(const vec4_t<another_coordinates_t>& vec) const { return x == vec.x && y == vec.y && z == vec.z && w == vec.w; };
	template <typename t> bool operator ==(const t& value) const { return x == value && y == value && z == value && w == value; };
	class_create_logic_operators(vec, vec4_t, <, { return self.x < vec.x && self.y < vec.y && self.z < vec.z && self.w < vec.w; }, { return self.x <= vec.x && self.y <= vec.y && self.z <= vec.z && self.w <= vec.w; });
	class_create_logic_operators(vec, vec4_t, >, { return self.x > vec.x && self.y > vec.y && self.z > vec.z && self.w > vec.w; }, { return self.x >= vec.x && self.y >= vec.y && self.z >= vec.z && self.w >= vec.w; });
};