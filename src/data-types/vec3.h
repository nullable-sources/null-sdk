#pragma once
#include <cmath>

#include <utils/fast_operators.h>

struct vec3_t {
public:
	float x{ }, y{ }, z{ };

public:
	vec3_t() = default;
	vec3_t(auto _value) : x(_value), y(_value), z(_value) { }
	vec3_t(auto _x, auto _y, auto _z) : x(_x), y(_y), z(_z) { }

public:
	float length() const { return std::hypot(x, y, z); }
	float dist_to(const vec3_t& a) { return vec3_t{ *this - a }.length(); }
	vec3_t& normalize() { return *this = { std::isfinite(x) ? std::remainder(x, 360.f) : 0.f, std::isfinite(y) ? std::remainder(y, 360.f) : 0.f, 0.f }; }

public:
	class_create_operators(vec3_t, -, { return vec3_t(-x, -y, -z); });
	class_create_arithmetic_operators(vec3_t, +, { return vec3_t(x + a.x, y + a.y, z + a.z); }, { x += a.x; y += a.y; z += a.z; return *this; });
	class_create_arithmetic_operators(vec3_t, -, { return vec3_t(x - a.x, y - a.y, z - a.z); }, { x -= a.x; y -= a.y; z -= a.z; return *this; });
	class_create_arithmetic_operators(vec3_t, *, { return vec3_t(x * a.x, y * a.y, z * a.z); }, { x *= a.x; y *= a.y; z *= a.z; return *this; });
	class_create_arithmetic_operators(vec3_t, /, { return vec3_t(x / a.x, y / a.y, z / a.z); }, { x /= a.x; y /= a.y; z /= a.z; return *this; });

	bool operator==(const vec3_t& a) const = default;
	class_create_logic_operators(vec3_t, <, { return x < a.x && y < a.y && z < a.z; }, { return x <= a.x && y <= a.y && z <= a.z; });
	class_create_logic_operators(vec3_t, >, { return x > a.x && y > a.y && z > a.z; }, { return x >= a.x && y >= a.y && z >= a.z; });
};