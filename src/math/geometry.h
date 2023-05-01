#pragma once
#include <numbers>
#include <cmath>
#include <array>
#include <data-types/angle/angle.h>
#include <data-types/matrix.h>

namespace math {
	enum class e_rotation {
		ccw, //@not: counter-clockwise
		cw //@note: clockwise
	};

	template <typename coordinates_t>
	static radians_t angle_between(const vec2_t<coordinates_t>& point1, const vec2_t<coordinates_t>& point2) {
		return std::atan2(point2.y, point2.x) - std::atan2(point1.y, point1.x);
	}

	static matrix_t<radians_t, vec2_t, vec2_t> rotation_matrix(const radians_t& angle, const e_rotation& rotation = e_rotation::ccw) {
		return matrix_t<radians_t, vec2_t, vec2_t>{ std::array{
			std::array{ std::cos(angle), std::sin(rotation == e_rotation::ccw ? -angle : angle) },
			std::array{ std::sin(rotation == e_rotation::ccw ? -angle : angle), std::cos(angle) }
		} };
	}

	template <typename coordinates_t>
	static vec2_t<coordinates_t> rotate_vector(const vec2_t<coordinates_t>& src, const matrix_t<radians_t, vec2_t, vec2_t>& matrix) {
		return matrix_t<radians_t, vec2_t, vec2_t>{ matrix * matrix_t<radians_t, vec2_t, vec2_t>{ src } }.get_row(0);
	}

	template <typename coordinates_t>
	static vec2_t<coordinates_t> rotate_vector(const vec2_t<coordinates_t>& src, const radians_t& angle, const e_rotation& rotation = e_rotation::ccw) {
		if(angle == std::numbers::pi * 0.5) {
			vec2_t<coordinates_t> result{ src };
			std::swap(result.x, result.y);

			if(rotation == e_rotation::ccw) result.y *= -1;
			else result.x *= -1;

			return result;
		} else return rotate_vector(src, rotation_matrix(angle, rotation));
	}

	template <typename coordinates_t>
	static vec2_t<coordinates_t> vectors_bisector(const vec2_t<coordinates_t>& point1, const vec2_t<coordinates_t>& point2, const e_rotation& rotation = e_rotation::ccw) {
		static const angle_t<radians_t> angle{ 90.f };
		return vec2_t{ rotate_vector(point1, angle, rotation) + rotate_vector(point2, angle, rotation) }.normalized();
	}
}