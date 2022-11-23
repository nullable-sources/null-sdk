#pragma once
#include <cmath>

#include <utils/fast_operators.h>

struct vec3_t {
public:
	float x{ }, y{ }, z{ };

public:
	vec3_t() { }
	template <typename t>
		requires std::is_arithmetic_v<t>
	vec3_t(t _value) : vec3_t{ _value, _value, _value } { }
	template <typename t>
		requires std::is_arithmetic_v<t>
	vec3_t(t _x, t _y, t _z) : x{ _x }, y{ _y }, z{ _z } { }

public:
	float length() const { return std::hypot(x, y, z); }
	float dist_to(const vec3_t& vec) { return vec3_t{ *this - vec }.length(); }
	vec3_t& normalize() { return *this = { std::isfinite(x) ? std::remainder(x, 360.f) : 0.f, std::isfinite(y) ? std::remainder(y, 360.f) : 0.f, 0.f }; }
	float dot(const vec3_t& vec) const { return x * vec.x + y * vec.y + z * vec.z; }

public:
	class_create_operators(vec3_t, -, { return vec3_t(-x, -y, -z); }, ());
	class_create_arithmetic_operators(vec, vec3_t, +, { return vec3_t(x + vec.x, y + vec.y, z + vec.z); });
	class_create_arithmetic_operators(vec, vec3_t, -, { return vec3_t(x - vec.x, y - vec.y, z - vec.z); });
	class_create_arithmetic_operators(vec, vec3_t, *, { return vec3_t(x * vec.x, y * vec.y, z * vec.z); });
	class_create_arithmetic_operators(vec, vec3_t, /, { return vec3_t(x / vec.x, y / vec.y, z / vec.z); });

	bool operator==(const vec3_t&) const = default;
	class_create_logic_operators(vec, vec3_t, <, { return x < vec.x && y < vec.y && z < vec.z; });
	class_create_logic_operators(vec, vec3_t, >, { return x > vec.x && y > vec.y && z > vec.z; });
};