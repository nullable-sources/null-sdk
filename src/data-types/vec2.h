#pragma once
#include <cmath>

#include <utils/fast_operators.h>

struct vec2_t {
public:
	float x{ }, y{ };

public:
	vec2_t() = default;
	vec2_t(auto _value) : x(_value), y(_value) { }
	vec2_t(auto _x, auto _y) : x(_x), y(_y) { }

public:
	float length() const { return std::hypot(x, y); }

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