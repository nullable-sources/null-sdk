#pragma once
#include "../matrix/matrix2x2.h"
#include "angle.h"

template <null::sdk::is_angle_type_t angle_value_t, math::e_rotation rotation = math::e_rotation::ccw>
struct euler2d_t {
public:
    angle_t<angle_value_t> angle{ };

public:
    euler2d_t() { }
    template <typename point_t>
    euler2d_t(const vec2_t<point_t>& point) { set_angle(point); }
    template <null::sdk::is_angle_type_t another_angle_value_t>
    euler2d_t(another_angle_value_t _angle) : angle(_angle) { }
    template <null::sdk::is_angle_type_t another_angle_value_t>
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
    fast_ops_structure_all_prefix_operators(inline constexpr, angle);
    fast_ops_structure_all_postfix_operators(inline constexpr, angle);

    fast_ops_structure_all_arithmetic_operators(inline constexpr, template <typename self_t>, const euler2d_t<angle_value_t>&, rhs_field, angle);
    fast_ops_structure_all_arithmetic_operators(inline constexpr, template <typename self_t>, const angle_t<angle_value_t>&, rhs_field, angle);
    fast_ops_structure_all_arithmetic_operators(inline constexpr, template <typename self_t>, angle_value_t, rhs_value, angle);

    inline constexpr auto operator<=>(const euler2d_t<angle_value_t, rotation>&) const = default;
    inline constexpr auto operator<=>(const angle_t<angle_value_t>& rhs) const { return angle <=> rhs.angle; }
    inline constexpr auto operator<=>(angle_value_t& rhs) const { return angle <=> rhs; }
};