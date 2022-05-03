export module null.sdk:data_types.rect;
import :data_types.vec2;

#include <fast_operators.h>

struct rect_t {
	vec2_t min{ }, max{ };

	rect_t() = default;
	template <typename t> rect_t(t _value) : min(_value), max(_value) { }
	template <typename t> rect_t(t _min, t _max) : min(_min), max(_max) { }

	vec2_t size() { return max - min; }
	vec2_t centre() { return (min + max) / 2; }

	class_create_operators(rect_t, -, { return rect_t(-min, -max); });
	class_create_arithmetic_operators(rect_t, +, { return rect_t(min + a.min, max + a.max); }, { min += a.min; max += a.max; return *this; });
	class_create_arithmetic_operators(rect_t, -, { return rect_t(min - a.min, max - a.max); }, { min -= a.min; max -= a.max; return *this; });
	class_create_arithmetic_operators(rect_t, *, { return rect_t(min * a.min, max * a.max); }, { min *= a.min; max *= a.max; return *this; });
	class_create_arithmetic_operators(rect_t, / , { return rect_t(min / a.min, max / a.max); }, { min /= a.min; max /= a.max; return *this; });

	class_create_spaceship_operator(rect_t);
};