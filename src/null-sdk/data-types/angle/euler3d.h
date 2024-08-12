#pragma once
#include "../../utils/fast-defines.h"
#include "../matrix/matrix2x2.h"
#include "../matrix/matrix3x3.h"
#include "angle.h"

namespace null::sdk {
    enum class e_coordinate_system {
        left_handed, //@note: the value increases when turned clockwise
        right_handed //@note: the value increases when turned counterclockwise
    };

    enum class e_up_axis { y, z };

    enum class e_axis_boundires_behaviour {
        none,
        normalize,
        clamp
    };

    template <is_angle_type_t angle_value_t>
    struct axis_definition_t {
    public:
        e_axis_boundires_behaviour normalize_behaviour{ e_axis_boundires_behaviour::normalize }, clamp_behaviour{ e_axis_boundires_behaviour::clamp };
        angle_value_t normalize_boundires{ angle_t<angle_value_t>::default_boundires }, clamp_boundires{ angle_t<angle_value_t>::default_boundires };
    };
    
    template <is_angle_type_t angle_value_t,
        math::e_rotation rotation,
        e_coordinate_system coordinate_system,
        e_up_axis up_axis
    >
    class i_euler3d {
    public:
        using euler_t = i_euler3d<angle_value_t, rotation, coordinate_system, up_axis>;
        template <is_angle_type_t _angle_value_t>
        using euler_type_t = i_euler3d<_angle_value_t, rotation, coordinate_system, up_axis>;

    public:
        static constexpr axis_definition_t<angle_value_t> roll_definition{ }, pitch_definition{ }, yaw_definition{ };

        static constexpr inline math::e_rotation directions_rotation() {
            if constexpr(coordinate_system == e_coordinate_system::right_handed) return math::e_rotation::cw;
            else return math::e_rotation::ccw;
        }

    public:
        inline constexpr i_euler3d() { }

        template <typename type_t> requires null::compatibility::data_type_convertertable<type_t, euler_t>
        inline constexpr i_euler3d(const type_t& value) : i_euler3d(null::compatibility::data_type_converter_t<type_t, euler_t>::convert(value)) { }

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
            vector = matrix3x3_t::rotation_y(self.pitch, directions_rotation()) * vector;
            vector = matrix3x3_t::rotation_z(self.yaw, directions_rotation()) * vector;
            return vector.normalized();
        }

        template <typename self_t>
        vec3_t<float> right(this self_t&& self) {
            constexpr float direction = coordinate_system == e_coordinate_system::right_handed ? -1.f : 1.f;

            vec3_t<float> vector(0.f, 0.f, 0.f);
            if constexpr(up_axis == e_up_axis::z) vector.y = direction;
            else vector.z = direction;

            vector = matrix3x3_t::rotation_x(self.roll, directions_rotation()) * vector;
            vector = matrix3x3_t::rotation_z(self.yaw, directions_rotation()) * vector;
            return vector.normalized();
        }

        template <typename self_t>
        vec3_t<float> up(this self_t&& self) {
            vec3_t<float> vector(0.f, 0.f, 0.f);
            if constexpr(up_axis == e_up_axis::z) vector.z = 1.f;
            else vector.y = 1.f;

            vector = matrix3x3_t::rotation_x(self.roll, directions_rotation()) * vector;
            vector = matrix3x3_t::rotation_y(self.pitch, directions_rotation()) * vector;
            vector = matrix3x3_t::rotation_z(self.yaw, directions_rotation()) * vector;
            return vector.normalized();
        }

    public:
        template <typename self_t>
        auto&& roll_clamp(this self_t&& self) {
            if constexpr(std::decay_t<self_t>::roll_definition.clamp_behaviour == e_axis_boundires_behaviour::clamp)
                self.roll.clamp<std::decay_t<self_t>::roll_definition.clamp_boundires>();
            else if(std::decay_t<self_t>::roll_definition.clamp_behaviour == e_axis_boundires_behaviour::normalize)
                self.roll.normalize<std::decay_t<self_t>::roll_definition.clamp_boundires>();

            return self;
        }

        template <typename self_t>
        auto&& roll_normalize(this self_t&& self) {
            if constexpr(std::decay_t<self_t>::roll_definition.normalize_behaviour == e_axis_boundires_behaviour::normalize)
                self.roll.normalize<std::decay_t<self_t>::roll_definition.normalize_boundires>();
            else if(std::decay_t<self_t>::roll_definition.normalize_behaviour == e_axis_boundires_behaviour::clamp)
                self.roll.clamp<std::decay_t<self_t>::roll_definition.normalize_boundires>();

            return self;
        }

        template <typename self_t>
        auto&& pitch_clamp(this self_t&& self) {
            if constexpr(std::decay_t<self_t>::pitch_definition.clamp_behaviour == e_axis_boundires_behaviour::clamp)
                self.pitch.clamp<std::decay_t<self_t>::pitch_definition.clamp_boundires>();
            else if(std::decay_t<self_t>::pitch_definition.clamp_behaviour == e_axis_boundires_behaviour::normalize)
                self.pitch.normalize<std::decay_t<self_t>::pitch_definition.clamp_boundires>();

            return self;
        }

        template <typename self_t>
        auto&& pitch_normalize(this self_t&& self) {
            if constexpr(std::decay_t<self_t>::pitch_definition.normalize_behaviour == e_axis_boundires_behaviour::normalize)
                self.pitch.normalize<std::decay_t<self_t>::pitch_definition.normalize_boundires>();
            else if(std::decay_t<self_t>::pitch_definition.normalize_behaviour == e_axis_boundires_behaviour::clamp)
                self.pitch.clamp<std::decay_t<self_t>::pitch_definition.normalize_boundires>();

            return self;
        }

        template <typename self_t>
        auto&& yaw_clamp(this self_t&& self) {
            if constexpr(std::decay_t<self_t>::yaw_definition.clamp_behaviour == e_axis_boundires_behaviour::clamp)
                self.yaw.clamp<std::decay_t<self_t>::yaw_definition.clamp_boundires>();
            else if(std::decay_t<self_t>::yaw_definition.clamp_behaviour == e_axis_boundires_behaviour::normalize)
                self.yaw.normalize<std::decay_t<self_t>::yaw_definition.clamp_boundires>();

            return self;
        }

        template <typename self_t>
        auto&& yaw_normalize(this self_t&& self) {
            if constexpr(std::decay_t<self_t>::yaw_definition.normalize_behaviour == e_axis_boundires_behaviour::normalize)
                self.yaw.normalize<std::decay_t<self_t>::yaw_definition.normalize_boundires>();
            else if(std::decay_t<self_t>::yaw_definition.normalize_behaviour == e_axis_boundires_behaviour::clamp)
                self.yaw.clamp<std::decay_t<self_t>::yaw_definition.normalize_boundires>();

            return self;
        }

        template <typename self_t>
        self_t clamped(this self_t self) { return self.roll_clamp().pitch_clamp().yaw_clamp(); }

        template <typename self_t>
        auto&& clamp(this self_t&& self) { self = self.clamped(); return self; }

        template <typename self_t>
        self_t normalized(this self_t self) { return self.roll_normalize().pitch_normalize().yaw_normalize(); }

        template <typename self_t>
        auto&& normalize(this self_t&& self) { self = self.normalized(); return self; }

        template <typename self_t, typename direction_t>
        auto&& set_angles(this self_t&& self, const vec3_t<direction_t>& direction) {
            self.roll = angle_value_t{ };

            const float length{ };
            if constexpr(up_axis == e_up_axis::z) {
                self.pitch = angle_t<radians_t>::atan2(direction.z, direction.xy().length());
                self.yaw = -angle_t<radians_t>::atan2(direction.y, direction.x);
            } else {
                self.pitch = angle_t<radians_t>::atan2(direction.y, direction.xz().length());
                self.yaw = -angle_t<radians_t>::atan2(direction.z, direction.x);
            }

            if constexpr(coordinate_system == e_coordinate_system::right_handed) {
                self.pitch *= -1.f;
                self.yaw *= -1.f;
            }
            return self;
        }

    public:
        template <typename type_t> requires null::compatibility::data_type_convertertable<euler_t, type_t>
        inline constexpr operator type_t() const { return null::compatibility::data_type_converter_t<euler_t, type_t>::convert(*this); }

        template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.axies[i]; }

        fast_ops_structure_all_arithmetic_operators(inline constexpr, fast_ops_args_pack(template <typename self_t, is_angle_type_t angle_other_t>), const euler_type_t<angle_other_t>&, rhs_field, x, y, z);
        fast_ops_structure_all_arithmetic_operators(inline constexpr, template <typename self_t>, angle_value_t, rhs_value, x, y, z);

        fast_ops_structure_all_comparison_operators(inline constexpr, fast_ops_args_pack(template <typename self_t, is_angle_type_t angle_other_t>), const euler_type_t<angle_other_t>&, rhs_field, x, y, z);
        fast_ops_structure_all_comparison_operators(inline constexpr, template <typename self_t>, angle_value_t, rhs_value, x, y, z);
    };

#define __fast_defs__unpack_tuple_element__euler_raw_ctor(i, data, elem)                        \
    another_angle_value_t BOOST_PP_CAT(_, __fast_defs__unpack_tuple_element__(i, data, elem))   \

#define __fast_defs__unpack_tuple_element__euler_type_ctor(i, data, elem)                                       \
    const angle_t<another_angle_value_t>& BOOST_PP_CAT(_, __fast_defs__unpack_tuple_element__(i, data, elem))   \

#define __make_euler_implementation(implementation_name, ...)                                                                                                                   \
    template <is_angle_type_t angle_value_t,                                                                                                                                    \
        math::e_rotation rotation,                                                                                                                                              \
        e_coordinate_system coordinate_system,                                                                                                                                  \
        e_up_axis up_axis                                                                                                                                                       \
    >                                                                                                                                                                           \
    class i_##implementation_name##_euler3d : public i_euler3d<angle_value_t, rotation, coordinate_system, up_axis> {                                                           \
    public: using i_euler3d<angle_value_t, rotation, coordinate_system, up_axis>::i_euler3d;                                                                                    \
    public:                                                                                                                                                                     \
        using euler_interface_t = i_euler3d<angle_value_t, rotation, coordinate_system, up_axis>;                                                                               \
                                                                                                                                                                                \
    public:                                                                                                                                                                     \
        union {                                                                                                                                                                 \
            struct { angle_t<angle_value_t> __fast_defs__unpack_seq_enum(0, , __VA_ARGS__); };                                                                                  \
            struct { angle_t<angle_value_t> __fast_defs__unpack_seq_enum(1, , __VA_ARGS__); };                                                                                  \
            std::array<angle_t<angle_value_t>, 3> axises{ };                                                                                                                    \
        };                                                                                                                                                                      \
                                                                                                                                                                                \
    public:                                                                                                                                                                     \
        inline constexpr i_##implementation_name##_euler3d() { }                                                                                                                \
        template <null::sdk::is_angle_type_t another_angle_value_t>                                                                                                             \
        inline constexpr i_##implementation_name##_euler3d(__fast_defs__unpack_seq_enum(1, euler_raw_ctor, __VA_ARGS__))                                                        \
            : roll(_roll), pitch(_pitch), yaw(_yaw) { }                                                                                                                         \
        template <null::sdk::is_angle_type_t another_angle_value_t>                                                                                                             \
        inline constexpr i_##implementation_name##_euler3d(__fast_defs__unpack_seq_enum(1, euler_type_ctor, __VA_ARGS__))                                                       \
            : roll(_roll), pitch(_pitch), yaw(_yaw) { }                                                                                                                         \
        template <typename direction_t>                                                                                                                                         \
        inline i_##implementation_name##_euler3d(const vec3_t<direction_t>& direction) { euler_interface_t::set_angles(direction); }                                            \
                                                                                                                                                                                \
    public:                                                                                                                                                                     \
        fast_ops_structure_equal_operator(inline constexpr, template <is_angle_type_t angle_other_t>, const i_euler3d::euler_type_t<angle_other_t>&, rhs_field, x, y, z);       \
        fast_ops_structure_equal_operator(inline constexpr, , angle_value_t, rhs_value, x, y, z);                                                                               \
    };                                                                                                                                                                          \

#define __make_euler_implementation_shortcat(implementation_name)                                                                                   \
    template <null::sdk::is_angle_type_t angle_value_t,                                                                                             \
        math::e_rotation rotation = math::e_rotation::ccw,                                                                                          \
        null::sdk::e_coordinate_system coordinate_system = null::sdk::e_coordinate_system::right_handed,                                            \
        null::sdk::e_up_axis up_axis = null::sdk::e_up_axis::z                                                                                      \
    >                                                                                                                                               \
    using euler3d_##implementation_name##_t = null::sdk::i_##implementation_name##_euler3d<angle_value_t, rotation, coordinate_system, up_axis>;    \

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

template <null::sdk::is_angle_type_t angle_value_t,
    math::e_rotation rotation = math::e_rotation::ccw,
    null::sdk::e_coordinate_system coordinate_system = null::sdk::e_coordinate_system::right_handed,
    null::sdk::e_up_axis up_axis = null::sdk::e_up_axis::z
>
using euler3d_t = null::sdk::i_xyz_euler3d<angle_value_t, rotation, coordinate_system, up_axis>;

__make_euler_implementation_shortcat(yzx)