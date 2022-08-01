#pragma once
#include <data-types/vec2.h>

struct rect_t {
	vec2_t min{ }, max{ };

	rect_t() = default;
	rect_t(auto _value) : min(_value), max(_value) { }
	rect_t(auto _min, auto _max) : min(_min), max(_max) { }
	rect_t(auto min_x, auto min_y, auto max_x, auto max_y) : min(min_x, min_y), max(max_x, max_y) { }

	bool contains(const vec2_t& point) const { return min <= point && max >= point; }
	bool contains(const rect_t& rect) const { return contains(rect.min) || contains(rect.max); }
	bool intersects(const rect_t& rect) const { return !((rect.max.y <= min.y || rect.max.x <= min.x) || (rect.min.y >= max.y || rect.min.x >= max.y)); }

	vec2_t size() const { return max - min; }
	vec2_t center() const { return (min + max) / 2.f; }

	class_create_operators(rect_t, -, { return rect_t(-min, -max); });
	class_create_arithmetic_operators(rect_t, +, { return rect_t(min + a.min, max + a.max); }, { min += a.min; max += a.max; return *this; });
	class_create_arithmetic_operators(rect_t, -, { return rect_t(min - a.min, max - a.max); }, { min -= a.min; max -= a.max; return *this; });
	class_create_arithmetic_operators(rect_t, *, { return rect_t(min * a.min, max * a.max); }, { min *= a.min; max *= a.max; return *this; });
	class_create_arithmetic_operators(rect_t, / , { return rect_t(min / a.min, max / a.max); }, { min /= a.min; max /= a.max; return *this; });

	bool operator==(const rect_t&) const = default;
	class_create_logic_operators(rect_t, <, { return min < a.min && max < a.max; }, { return min <= a.min && max <= a.max; });
	class_create_logic_operators(rect_t, >, { return min > a.min && max > a.max; }, { return min >= a.min && max >= a.max; });
};