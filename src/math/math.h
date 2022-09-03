#pragma once
#include <numbers>
#include <data-types/vec3.h>
#include <data-types/rect.h>

namespace math {
	//@note: if you want a vec2_t without changing the values use std::min/std::max
	static vec2_t min(const vec2_t& a, const vec2_t& b) { return { std::min(a.x, b.x), std::min(a.y, b.y) }; }
	static vec2_t max(const vec2_t& a, const vec2_t& b) { return { std::max(a.x, b.x), std::max(a.y, b.y) }; }

	static vec3_t min(const vec3_t& a, const vec3_t& b) { return { std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z) }; }
	static vec3_t max(const vec3_t& a, const vec3_t& b) { return { std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z) }; }

	//@note: if you want a rect_t without changing the values use std::min/std::max
	static rect_t min(const rect_t& a, const rect_t& b) { return { min(a.min, b.min), min(a.max, b.max) }; }
	static rect_t max(const rect_t& a, const rect_t& b) { return { max(a.min, b.min), max(a.max, b.max) }; }

	//@note: std::lerp does not support non-arithmetic types
	static auto lerp(auto a, auto b, auto t) { return a + t * (b - a); }
}