#pragma once
#include <numbers>
#include <cmath>
#include <array>
#include <data-types/vec3.h>
#include <data-types/rect.h>
#include <data-types/matrix.h>

namespace math {
	//@note: it would be nice to shorten all of this via #define
	static vec2_t abs(const vec2_t& a) { return { std::abs(a.x), std::abs(a.y) }; }
	static vec3_t abs(const vec3_t& a) { return { std::abs(a.x), std::abs(a.y), std::abs(a.z) }; }
	static rect_t abs(const rect_t& a) { return { abs(a.min), abs(a.max) }; }

	static vec2_t mod(const vec2_t& a, const vec2_t& b) { return { std::fmod(a.x, b.x), std::fmod(a.y, b.y) }; }
	static vec3_t mod(const vec3_t& a, const vec3_t& b) { return { std::fmod(a.x, b.x), std::fmod(a.y, b.y), std::fmod(a.z, b.z) }; }
	static rect_t mod(const rect_t& a, const rect_t& b) { return { mod(a.min, b.min), mod(a.max, b.max) }; }

	static vec2_t remainder(const vec2_t& a, const vec2_t& b) { return { std::remainder(a.x, b.x), std::remainder(a.y, b.y) }; }
	static vec3_t remainder(const vec3_t& a, const vec3_t& b) { return { std::remainder(a.x, b.x), std::remainder(a.y, b.y), std::remainder(a.z, b.z) }; }
	static rect_t remainder(const rect_t& a, const rect_t& b) { return { remainder(a.min, b.min), remainder(a.max, b.max) }; }

	static vec2_t fma(const vec2_t& a, const vec2_t& b, const vec2_t& c) { return { std::fma(a.x, b.x, c.x), std::fma(a.y, b.y, c.y) }; }
	static vec3_t fma(const vec3_t& a, const vec3_t& b, const vec3_t& c) { return { std::fma(a.x, b.x, c.x), std::fma(a.y, b.y, c.y), std::fma(a.z, b.z, c.z) }; }
	static rect_t fma(const rect_t& a, const rect_t& b, const rect_t& c) { return { fma(a.min, b.min, c.min), fma(a.max, b.max, c.max) }; }

	static vec2_t dim(const vec2_t& a, const vec2_t& b) { return { std::fdim(a.x, b.x), std::fdim(a.y, b.y) }; }
	static vec3_t dim(const vec3_t& a, const vec3_t& b) { return { std::fdim(a.x, b.x), std::fdim(a.y, b.y), std::fdim(a.z, b.z) }; }
	static rect_t dim(const rect_t& a, const rect_t& b) { return { dim(a.min, b.min), dim(a.max, b.max) }; }

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

	static vec2_t clamp(const vec2_t& a, const vec2_t& min, const vec2_t& max) { return { std::clamp(a.x, min.x, max.x), std::clamp(a.y, min.y, max.y) }; }
	static vec3_t clamp(const vec3_t& a, const vec3_t& min, const vec3_t& max) { return { std::clamp(a.x, min.x, max.x), std::clamp(a.y, min.y, max.y), std::clamp(a.z, min.z, max.z) }; }
	static rect_t clamp(const rect_t& a, const rect_t& min, const rect_t& max) { return { clamp(a.min, min.min, max.min), clamp(a.max, min.max, max.max) }; }

	//@note: if you want a vec2_t/vec3_t/rect_t without changing the values use std::min/std::max
	static vec2_t min(const vec2_t& a, const vec2_t& b) { return { std::min(a.x, b.x), std::min(a.y, b.y) }; }
	static vec3_t min(const vec3_t& a, const vec3_t& b) { return { std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z) }; }
	static rect_t min(const rect_t& a, const rect_t& b) { return { min(a.min, b.min), min(a.max, b.max) }; }
	
	static vec2_t max(const vec2_t& a, const vec2_t& b) { return { std::max(a.x, b.x), std::max(a.y, b.y) }; }
	static vec3_t max(const vec3_t& a, const vec3_t& b) { return { std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z) }; }
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

	namespace triangles {
		static std::array<vec2_t, 3> arbitrary(float a, float c) { return { vec2_t{ -std::cos(degrees_to_radians(a)), 0.f }, vec2_t{ 0.f, std::sin(degrees_to_radians(180.f - a - c)) }, vec2_t{ std::cos(degrees_to_radians(c)), 0.f } }; }
		static std::array<vec2_t, 3> isosceles(float angle) { return arbitrary(angle, angle); }
		inline const std::array<vec2_t, 3> equilateral{ isosceles(60.f) };
	}

	static void rotate_polygon(std::vector<vec2_t>& points, const vec2_t& origin, float angle) {
		vec2_t sin_cos{ std::sin(math::degrees_to_radians(angle)), std::cos(math::degrees_to_radians(angle)) };
		for(vec2_t& point : points) {
			vec2_t delta{ point - origin };
			point = origin + vec2_t{ delta.cross(sin_cos), delta.dot(sin_cos) };
		}
	}

	static std::vector<vec2_t> rotate_polygon(const std::vector<vec2_t>& points, const vec2_t& origin, float angle) {
		std::vector<vec2_t> result{ points };
		rotate_polygon(result, origin, angle);
		return result;
	}

	static void rotate_polygon(std::vector<vec2_t>& points, float angle) {
		rotate_polygon(points, std::accumulate(points.begin(), points.end(), vec2_t{ }) / points.size(),angle);
	}

	static std::vector<vec2_t> rotate_polygon(const std::vector<vec2_t>& points, float angle) {
		std::vector<vec2_t> result{ points };
		rotate_polygon(result, angle);
		return result;
	}
}