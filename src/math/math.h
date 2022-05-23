#pragma once
#include <data-types/rect.h>

namespace math {
	//if you want a vec2_t without changing the values use std::min/std::max
	static vec2_t min(vec2_t a, vec2_t b) { return { std::min(a.x, b.x), std::min(a.y, b.y) }; }
	static vec2_t max(vec2_t a, vec2_t b) { return { std::max(a.x, b.x), std::max(a.y, b.y) }; }

	//if you want a rect_t without changing the values use std::min/std::max
	static rect_t min(rect_t a, rect_t b) { return { min(a.min, b.min), min(a.max, b.max) }; }
	static rect_t max(rect_t a, rect_t b) { return { max(a.min, b.min), max(a.max, b.max) }; }
}