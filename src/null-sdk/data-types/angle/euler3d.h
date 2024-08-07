#pragma once
#include "../../utils/fast-defines.h"
#include "../matrix/matrix2x2.h"
#include "angle.h"

namespace null::sdk {
    template <is_angle_type_t angle_value_t, math::e_rotation rotation>
    class i_euler3d {
    public:
        template <is_angle_type_t _angle_value_t>
        using euler_rotation_t = i_euler3d<_angle_value_t, rotation>;

    public:
        inline constexpr i_euler3d() { }
        template <typename direction_t>
        inline constexpr i_euler3d(const vec3_t<direction_t>& direction) { set_angles(direction); }

        template <typename type_t> requires null::compatibility::data_type_convertertable<type_t, i_euler3d<angle_value_t, rotation>>
        inline constexpr i_euler3d(const type_t& value) : i_euler3d(null::compatibility::data_type_converter_t<type_t, i_euler3d<angle_value_t, rotation>>::convert(value)) { }

    public:
        template <typename self_t, typename point_t>
        vec3_t<point_t> rotate(this self_t&& self, vec3_t<point_t> rotation_point) {
            rotation_point = matrix3x3_t::rotation_x(self.roll, rotation) * rotation_point;
            rotation_point = matrix3x3_t::rotation_y(self.pitch, rotation) * rotation_point;
            return matrix3x3_t::rotation_z(self.yaw, rotation) * rotation_point;
        }

        template <typename self_t>
        std::tuple<vec3_t<float>, vec3_t<float>, vec3_t<float>> directions(this self_t&& self) {
            return std::tuple(self.forward(), self.right(), self.up());
        }

        template <typename self_t>
        vec3_t<float> forward(this self_t&& self) {
            vec3_t<float> vector(1.f, 0.f, 0.f);
            vector = matrix3x3_t::rotation_y(self.pitch, rotation) * vector;
            vector = matrix3x3_t::rotation_z(self.yaw, rotation) * vector;
            return vector.normalized();
        }

        template <typename self_t>
        vec3_t<float> right(this self_t&& self) {
            vec3_t<float> vector(0.f, 1.f, 0.f);
            vector = matrix3x3_t::rotation_x(self.roll, rotation) * vector;
            vector = matrix3x3_t::rotation_z(self.yaw, rotation) * vector;
            return vector.normalized();
        }

        template <typename self_t>
        vec3_t<float> up(this self_t&& self) {
            vec3_t<float> vector(0.f, 0.f, 1.f);
            vector = matrix3x3_t::rotation_x(self.roll, rotation) * vector;
            vector = matrix3x3_t::rotation_y(self.pitch, rotation) * vector;
            return vector.normalized();
        }

    public:
        template <typename self_t, typename direction_t>
        auto&& set_angles(this self_t&& self, const vec3_t<direction_t>& direction) {
            self.roll = angle_value_t{ };
            self.pitch = angle_t<radians_t>::atan2(direction.xy().length(), direction.y);
            self.yaw = angle_t<radians_t>::atan2(direction.x, direction.z);
            return self;
        }

    public:
        template <typename type_t> requires null::compatibility::data_type_convertertable<i_euler3d<angle_value_t, rotation>, type_t>
        inline constexpr operator type_t() const { return null::compatibility::data_type_converter_t<i_euler3d<angle_value_t, rotation>, type_t>::convert(*this); }

        template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.axies[i]; }

        fast_ops_structure_all_arithmetic_operators(inline constexpr, fast_ops_args_pack(template <typename self_t, is_angle_type_t angle_other_t>), const euler_rotation_t<angle_other_t>&, rhs_field, x, y, z);
        fast_ops_structure_all_arithmetic_operators(inline constexpr, template <typename self_t>, angle_value_t, rhs_value, x, y, z);

        fast_ops_structure_all_comparison_operators(inline constexpr, fast_ops_args_pack(template <typename self_t, is_angle_type_t angle_other_t>), const euler_rotation_t<angle_other_t>&, rhs_field, x, y, z);
        fast_ops_structure_all_comparison_operators(inline constexpr, template <typename self_t>, angle_value_t, rhs_value, x, y, z);
    };

#define __fast_defs__unpack_tuple_element__euler_raw_ctor(i, data, elem)                        \
    another_angle_value_t BOOST_PP_CAT(_, __fast_defs__unpack_tuple_element__(i, data, elem))   \

#define __fast_defs__unpack_tuple_element__euler_type_ctor(i, data, elem)                                       \
    const angle_t<another_angle_value_t>& BOOST_PP_CAT(_, __fast_defs__unpack_tuple_element__(i, data, elem))   \

#define __make_euler_implementation(implementation_name, ...)                                                                                                                   \
    template <is_angle_type_t angle_value_t, math::e_rotation rotation>                                                                                                         \
    class i_##implementation_name##_euler3d : public i_euler3d<angle_value_t, rotation> {                                                                                       \
    public: using i_euler3d<angle_value_t, rotation>::i_euler3d;                                                                                                                \
    public:                                                                                                                                                                     \
        union {                                                                                                                                                                 \
            struct { angle_t<angle_value_t> __fast_defs__unpack_seq(0, , __VA_ARGS__); };                                                                                       \
            struct { angle_t<angle_value_t> __fast_defs__unpack_seq(1, , __VA_ARGS__); };                                                                                       \
            std::array<angle_t<angle_value_t>, 3> axises{ };                                                                                                                    \
        };                                                                                                                                                                      \
                                                                                                                                                                                \
    public:                                                                                                                                                                     \
        i_##implementation_name##_euler3d() { }                                                                                                                                 \
        template <null::sdk::is_angle_type_t another_angle_value_t>                                                                                                             \
        i_##implementation_name##_euler3d(__fast_defs__unpack_seq(1, euler_raw_ctor, __VA_ARGS__))                                                                              \
            : roll(_roll), pitch(_pitch), yaw(_yaw) { }                                                                                                                         \
        template <null::sdk::is_angle_type_t another_angle_value_t>                                                                                                             \
        i_##implementation_name##_euler3d(__fast_defs__unpack_seq(1, euler_type_ctor, __VA_ARGS__))                                                                             \
            : roll(_roll), pitch(_pitch), yaw(_yaw) { }                                                                                                                         \
                                                                                                                                                                                \
public:                                                                                                                                                                         \
        fast_ops_structure_equal_operator(inline constexpr, template <is_angle_type_t angle_other_t>, const i_euler3d::euler_rotation_t<angle_other_t>&, rhs_field, x, y, z);   \
        fast_ops_structure_equal_operator(inline constexpr, , angle_value_t, rhs_value, x, y, z);                                                                               \
    };                                                                                                                                                                          \

#define __make_euler_implementation_shortcat(implementation_name)                                                       \
    template <null::sdk::is_angle_type_t angle_value_t, math::e_rotation rotation = math::e_rotation::ccw>              \
    using euler3d_##implementation_name##_t = null::sdk::i_##implementation_name##_euler3d<angle_value_t, rotation>;    \

    //@note: For the standard description of the coordinate order, the coordinate system from aviation is used,
    //       in which roll - x, pitch - y, yaw - z.

    //@note: x      y     z  | standard order
    //      roll, pitch, yaw |
    // 
    //       x      y     z  | the order of this implementation
    //      roll, pitch, yaw |
    __make_euler_implementation(xyz, (x, roll), (y, pitch),(z, yaw))

    //@note: x      y     z  | standard order
    //      roll, pitch, yaw |
    // 
    //        y     z    x   | the order of this implementation
    //      pitch, yaw, roll |
    __make_euler_implementation(yzx, (y, pitch), (z, yaw), (x, roll))
}

template <null::sdk::is_angle_type_t angle_value_t, math::e_rotation rotation = math::e_rotation::ccw>
using euler3d_t = null::sdk::i_xyz_euler3d<angle_value_t, rotation>;

__make_euler_implementation_shortcat(yzx)