module;
#include <fast_operators.h>
export module null.sdk:data_types.vec2;

export struct vec2_t {
	float x{ }, y{ };

	vec2_t() = default;
	template <typename t> vec2_t(t _value) : x(_value), y(_value) { }
	template <typename t> vec2_t(t _x, t _y) : x(_x), y(_y) { }

	class_create_operators(vec2_t, -, { return vec2_t(-x, -y); });
	class_create_arithmetic_operators(vec2_t, +, { return vec2_t(x + a.x, y + a.y); }, { x += a.x; y += a.y; return *this; });
	class_create_arithmetic_operators(vec2_t, -, { return vec2_t(x - a.x, y - a.y); }, { x -= a.x; y -= a.y; return *this; });
	class_create_arithmetic_operators(vec2_t, *, { return vec2_t(x * a.x, y * a.y); }, { x *= a.x; y *= a.y; return *this; });
	class_create_arithmetic_operators(vec2_t, / , { return vec2_t(x / a.x, y / a.y); }, { x /= a.x; y /= a.y; return *this; });

	class_create_spaceship_operator(vec2_t);
};