#pragma once
#include <cmath>

#include <utils/fast_operators.h>

struct vec2_t {
public:
	float x{ }, y{ };

public:
	vec2_t() { }

	template <typename t>
		requires std::is_arithmetic_v<t>
	vec2_t(t _value) : vec2_t{ (float)_value, (float)_value } { }

	template <typename t>
		requires std::is_arithmetic_v<t>
	vec2_t(t _x, t _y) : x{ (float)_x }, y{ (float)_y } { }

public:
	float length() const { return std::hypot(x, y); }
	float dot(const vec2_t& vec) const { return x * vec.x + y * vec.y; }

public:
	class_create_operators(vec2_t, -, { return vec2_t(-x, -y); });
	class_create_arithmetic_operators(vec2_t, +, { return vec2_t(x + a.x, y + a.y); }, { x += a.x; y += a.y; return *this; });
	class_create_arithmetic_operators(vec2_t, -, { return vec2_t(x - a.x, y - a.y); }, { x -= a.x; y -= a.y; return *this; });
	class_create_arithmetic_operators(vec2_t, *, { return vec2_t(x * a.x, y * a.y); }, { x *= a.x; y *= a.y; return *this; });
	class_create_arithmetic_operators(vec2_t, /, { return vec2_t(x / a.x, y / a.y); }, { x /= a.x; y /= a.y; return *this; });

	bool operator==(const vec2_t& a) const = default;
	class_create_logic_operators(vec2_t, <, { return x < a.x && y < a.y; }, { return x <= a.x && y <= a.y; });
	class_create_logic_operators(vec2_t, >, { return x > a.x && y > a.y; }, { return x >= a.x && y >= a.y; });
};