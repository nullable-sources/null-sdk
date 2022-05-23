#pragma once
#include <data-types/vec2.h>

struct rect_t {
	vec2_t min{ }, max{ };

	rect_t() = default;
	template <typename t> rect_t(t _value) : min(_value), max(_value) { }
	template <typename t1, typename t2> rect_t(t1 _min, t2 _max) : min(_min), max(_max) { }
	template <typename t1, typename t2, typename t3, typename t4> rect_t(t1 min_x, t2 min_y, t3 max_x, t4 max_y) : min(min_x, min_y), max(max_x, max_y) { }

	vec2_t size() { return max - min; }
	vec2_t center() { return (min + max) / 2.f; }

	class_create_operators(rect_t, -, { return rect_t(-min, -max); });
	class_create_arithmetic_operators(rect_t, +, { return rect_t(min + a.min, max + a.max); }, { min += a.min; max += a.max; return *this; });
	class_create_arithmetic_operators(rect_t, -, { return rect_t(min - a.min, max - a.max); }, { min -= a.min; max -= a.max; return *this; });
	class_create_arithmetic_operators(rect_t, *, { return rect_t(min * a.min, max * a.max); }, { min *= a.min; max *= a.max; return *this; });
	class_create_arithmetic_operators(rect_t, / , { return rect_t(min / a.min, max / a.max); }, { min /= a.min; max /= a.max; return *this; });

	class_create_spaceship_operator(rect_t);
};