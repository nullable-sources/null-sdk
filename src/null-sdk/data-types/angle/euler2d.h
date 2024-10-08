#pragma once
#include "../matrix/matrix2x2.h"
#include "angle.h"

template <ntl::sdk::is_angle_type_t angle_value_t, ntl::math::e_rotation rotation = ntl::math::e_rotation::ccw>
struct euler2d_t {
public:
    angle_t<angle_value_t> angle{ };

public:
    euler2d_t() { }
    template <typename point_t>
    euler2d_t(const vec2_t<point_t>& point) { set_angle(point); }
    template <ntl::sdk::is_angle_type_t another_angle_value_t>
    euler2d_t(another_angle_value_t _angle) : angle(_angle) { }
    template <ntl::sdk::is_angle_type_t another_angle_value_t>
    euler2d_t(const angle_t<another_angle_value_t>& _angle) : angle(_angle) { }

public:
    template <typename point_t>
    vec2_t<point_t> rotate(const vec2_t<point_t>& rotation_point) const { return matrix() * rotation_point; }

public:
    template <typename self_t>
    auto&& matrix(this self_t&& self) { return matrix2x2_t::rotation(self.angle, rotation); }

    template <typename self_t, typename point_t>
    auto&& set_angle(this self_t&& self, const vec2_t<point_t>& point) { self.angle = angle_t<radians_t>((radians_t)std::atan2(point.y, point.x)); return self; }

public:
    NULLSDK_FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(inline constexpr, angle);
    NULLSDK_FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(inline constexpr, angle);

    NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, const euler2d_t<angle_value_t>&, RHS_FIELD, angle);
    NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, const angle_t<angle_value_t>&, RHS_FIELD, angle);
    NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, angle_value_t, RHS_VALUE, angle);

    inline constexpr auto operator<=>(const euler2d_t<angle_value_t, rotation>&) const = default;
    inline constexpr auto operator<=>(const angle_t<angle_value_t>& rhs) const { return angle <=> rhs.angle; }
    inline constexpr auto operator<=>(angle_value_t& rhs) const { return angle <=> rhs; }
};