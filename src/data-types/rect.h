#pragma once
#include <data-types/vec2.h>

struct rect_t {
public:
	vec2_t min{ }, max{ };

public:
	rect_t() { }

	template <typename t>
		requires std::is_arithmetic_v<t> || std::is_same_v<std::remove_cv_t<t>, vec2_t>
	rect_t(t _value) : rect_t{ _value, _value } { }
	template <typename t>
		requires std::is_arithmetic_v<t> || std::is_same_v<std::remove_cv_t<t>, vec2_t>
	rect_t(t _min, t _max) : min{ _min }, max{ _max } { }
	template <typename t>
		requires std::is_arithmetic_v<t>
	rect_t(t min_x, t min_y, t max_x, t max_y) : min{ min_x, min_y }, max{ max_x, max_y } { }

public:
	template <typename t>
		requires std::is_aggregate_v<t>
	rect_t& from_min(t size) { max = min + size; return *this; }
	
	template <typename t>
		requires std::is_aggregate_v<t>
	rect_t& from_max(t size) { min = max - size; return *this; }

	bool contains(const vec2_t& point) const { return min <= point && max >= point; }
	bool contains(const rect_t& rect) const { return contains(rect.min) || contains(rect.max); }
	bool intersects(const rect_t& rect) const { 
		if((rect.min.x <= min.x && rect.max.x <= min.x) || (rect.min.x >= max.x && rect.max.x >= max.x)) return false;
		if((rect.min.y <= min.y && rect.max.y <= min.y) || (rect.min.y >= max.y && rect.max.y >= max.y)) return false;
		return true;
	}

	vec2_t size() const { return max - min; }
	vec2_t center() const { return (min + max) / 2.f; }

public:
	class_create_operators(rect_t, -, { return rect_t(-min, -max); }, ());
	class_create_arithmetic_operators(rect, rect_t, +, { return rect_t(min + rect.min, max + rect.max); });
	class_create_arithmetic_operators(rect, rect_t, -, { return rect_t(min - rect.min, max - rect.max); });
	class_create_arithmetic_operators(rect, rect_t, *, { return rect_t(min * rect.min, max * rect.max); });
	class_create_arithmetic_operators(rect, rect_t, /, { return rect_t(min / rect.min, max / rect.max); });

	bool operator==(const rect_t&) const = default;
	class_create_logic_operators(rect, rect_t, <, { return min < rect.min && max < rect.max; });
	class_create_logic_operators(rect, rect_t, >, { return min > rect.min && max > rect.max; });
};