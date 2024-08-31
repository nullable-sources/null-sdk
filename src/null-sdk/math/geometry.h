#pragma once
#include <numbers>
#include <cmath>
#include <array>
#include "../data-types/angle/angle.h"

namespace ntl::math {
    enum class e_rotation {
        ccw,    //@not: counter-clockwise
        cw      //@note: clockwise
    };

    template <typename coordinates_t>
    static inline radians_t angle_between(const vec2_t<coordinates_t>& point1, const vec2_t<coordinates_t>& point2) {
        return std::atan2(point2.y, point2.x) - std::atan2(point1.y, point1.x);
    }

    //@note: rotates the vector by 90 degrees
    template <typename coordinates_t>
    static inline constexpr vec2_t<coordinates_t> invert_vector_axis(const vec2_t<coordinates_t>& src, e_rotation rotation = e_rotation::ccw) {
        return vec2_t<coordinates_t>(
            rotation == e_rotation::ccw ? src.y : -src.y,
            rotation == e_rotation::ccw ? -src.x : src.x
        );
    }

    template <typename coordinates_t>
    static inline vec2_t<coordinates_t> vectors_bisector(const vec2_t<coordinates_t>& point1, const vec2_t<coordinates_t>& point2, e_rotation rotation = e_rotation::ccw) {
        return vec2_t(invert_vector_axis(point1, rotation) + invert_vector_axis(point2, rotation)).normalized();
    }
}