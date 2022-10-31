#pragma once
#include <numbers>
#include <cmath>
#include <data-types/vec3.h>
#include <data-types/rect.h>
#include <data-types/matrix.h>

namespace math {
	static vec2_t ceil(const vec2_t& a) { return { std::ceil(a.x), std::ceil(a.y) }; }
	static vec3_t ceil(const vec3_t& a) { return { std::ceil(a.x), std::ceil(a.y), std::ceil(a.z) }; }
	static rect_t ceil(const rect_t& a) { return { ceil(a.min), ceil(a.max) }; }

	static vec2_t floor(const vec2_t& a) { return { std::floor(a.x), std::floor(a.y) }; }
	static vec3_t floor(const vec3_t& a) { return { std::floor(a.x), std::floor(a.y), std::floor(a.z) }; }
	static rect_t floor(const rect_t& a) { return { floor(a.min), floor(a.max) }; }

	static vec2_t trunc(const vec2_t& a) { return { std::trunc(a.x), std::trunc(a.y) }; }
	static vec3_t trunc(const vec3_t& a) { return { std::trunc(a.x), std::trunc(a.y), std::trunc(a.z) }; }
	static rect_t trunc(const rect_t& a) { return { trunc(a.min), trunc(a.max) }; }

	static vec2_t round(const vec2_t& a) { return { std::round(a.x), std::round(a.y) }; }
	static vec3_t round(const vec3_t& a) { return { std::round(a.x), std::round(a.y), std::round(a.z) }; }
	static rect_t round(const rect_t& a) { return { round(a.min), round(a.max) }; }

	static vec2_t nearbyint(const vec2_t& a) { return { std::nearbyint(a.x), std::nearbyint(a.y) }; }
	static vec3_t nearbyint(const vec3_t& a) { return { std::nearbyint(a.x), std::nearbyint(a.y), std::nearbyint(a.z) }; }
	static rect_t nearbyint(const rect_t& a) { return { nearbyint(a.min), nearbyint(a.max) }; }

	static vec2_t rint(const vec2_t& a) { return { std::rint(a.x), std::rint(a.y) }; }
	static vec3_t rint(const vec3_t& a) { return { std::rint(a.x), std::rint(a.y), std::rint(a.z) }; }
	static rect_t rint(const rect_t& a) { return { rint(a.min), rint(a.max) }; }

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

	static float degrees_to_radians(float degrees) {
		static constexpr float pi{ std::numbers::pi_v<float> / 180.f };
		return degrees * pi;
	}

	static float radians_to_degrees(float radians) {
		static constexpr float pi{ 180.f / std::numbers::pi_v<float> };
		return radians * pi;
	}
}