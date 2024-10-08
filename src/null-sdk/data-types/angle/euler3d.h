#pragma once
#include "../../utils/fast-defines.h"
#include "../matrix/matrix2x2.h"
#include "../matrix/matrix3x3.h"
#include "angle.h"

namespace ntl::sdk {
    //@note: by default - x: pitch
    //                    y: yaw
    //                    z: roll
    enum class e_euler_sequence {
        //@note: i don't see much point in using true euler angles with two axes
        xyz, xzy, yxz,
        zyx, yzx, zxy,
        num,
    }; NULLSDK_ENUM_CREATE_CAST_OPERATOR(e_euler_sequence, -);
    static inline constexpr e_euler_sequence invert_euler_sequence(e_euler_sequence sequence) {
        int id = -sequence;
        constexpr int half_sequence = -e_euler_sequence::num / 2;
        return id < half_sequence ? e_euler_sequence(id + half_sequence) : e_euler_sequence(id - half_sequence);
    }

    enum class e_euler_up_axis { z, y };
    enum class e_euler_hand { left, right };
    enum class e_euler_construction { extrinsic, intrinsic };
    enum class e_euler_representation { active, pasive };

    enum class e_euler_boundires_behaviour {
        none,      //@note: the axis will not change
        normalize, //@note: The axis will be normalized between normalize_boundires
        clamp      //@note: The axis will be clamped between the clamp_boundires
    };

    struct euler_boundires_t {
    public:
        template <is_angle_type_t angle_value_t>
        static inline constexpr auto behaviour() { return e_euler_boundires_behaviour::none; }

        template <is_angle_type_t angle_value_t>
        static inline constexpr angle_value_t minimal() { return angle_t<angle_value_t>::minimal_boundires; }

        template <is_angle_type_t angle_value_t>
        static inline constexpr angle_value_t maximal() { return angle_t<angle_value_t>::maximal_boundires; };

    public:
        template <typename boundires_implementation_t, is_angle_type_t angle_value_t>
        static inline constexpr auto append(angle_t<angle_value_t>& val) {
            constexpr auto behaviour = boundires_implementation_t::template behaviour<angle_value_t>();
            constexpr auto minimal = boundires_implementation_t::template minimal<angle_value_t>();
            constexpr auto maximal = boundires_implementation_t::template maximal<angle_value_t>();

            if constexpr(behaviour == e_euler_boundires_behaviour::normalize)
                val.normalize<minimal, maximal>();
            else if constexpr(behaviour == e_euler_boundires_behaviour::clamp)
                val.clamp<minimal, maximal>();
        }
    };

    struct euler_description_t {
    public:
        static constexpr e_euler_sequence sequence = e_euler_sequence::xyz;

        //@note: or an understanding of e_construction and e_represents, see https://github.com/kam3k/euler?tab=readme-ov-file#active-vs-passive
        static constexpr e_euler_construction construction = e_euler_construction::extrinsic;
        static constexpr e_euler_representation representation = e_euler_representation::active;

        struct pitch_normalize_t : public euler_boundires_t {
        public:
            template <is_angle_type_t angle_value_t>
            static inline constexpr auto behaviour() { return e_euler_boundires_behaviour::normalize; }
        };

        struct pitch_clamp_t : public euler_boundires_t {
        public:
            template <is_angle_type_t angle_value_t>
            static inline constexpr auto behaviour() { return e_euler_boundires_behaviour::clamp; }
        };

        struct yaw_normalize_t : public euler_boundires_t {
        public:
            template <is_angle_type_t angle_value_t>
            static inline constexpr auto behaviour() { return e_euler_boundires_behaviour::normalize; }
        };

        struct yaw_clamp_t : public euler_boundires_t {
        public:
            template <is_angle_type_t angle_value_t>
            static inline constexpr auto behaviour() { return e_euler_boundires_behaviour::clamp; }
        };

        struct roll_normalize_t : public euler_boundires_t {
        public:
            template <is_angle_type_t angle_value_t>
            static inline constexpr auto behaviour() { return e_euler_boundires_behaviour::normalize; }
        };

        struct roll_clamp_t : public euler_boundires_t {
        public:
            template <is_angle_type_t angle_value_t>
            static inline constexpr auto behaviour() { return e_euler_boundires_behaviour::clamp; }
        };
    };

    struct default_euler_description_t final : public euler_description_t {
    public:
        //@note: currently not in use
        static constexpr e_euler_hand hand = e_euler_hand::right;
        static constexpr e_euler_up_axis up_axis = e_euler_up_axis::z;

        //@note: these vectors differ in different coordinate systems
        //       as ø understand it, there are only 4 variants of these vectors,
        //       they depend on the left/right handed and on the upper y/z axis.
        //       
        //       for example:
        //       unity:  left-handed y-up
        //          forward = 0 0 1
        //          right   = 1 0 0
        //          up      = 0 1 0
        //       ue:     left-handed z-up
        //          forward = 1 0 0
        //          right   = 0 1 0
        //          up      = 0 0 1
        //       source: right-handed z-up
        //          forward = -1  0 0
        //          right   =  0 -1 0
        //          up      =  0  0 1
        //
        //      adjust these vectors according to your tasks, or just use the standard version of the right-handed z-up
        static constexpr vec3_t<float> forward = vec3_t<float>(-1.f, 0.f, 0.f);
        static constexpr vec3_t<float> right = vec3_t<float>(0.f, -1.f, 0.f);
        static constexpr vec3_t<float> up = vec3_t<float>(0.f, 0.f, 1.f);
    };

    template <is_angle_type_t angle_value_t, typename description_t, typename memory_layout_t>
        requires std::is_base_of_v<euler_description_t, description_t>
    class c_euler3d : public memory_layout_t {
    public: using memory_layout_t::memory_layout_t;
    public:
        using used_description_t = description_t;
        using used_memory_layout_t = memory_layout_t;

        template <is_angle_type_t _angle_value_t>
        using self_euler_type_t = c_euler3d<_angle_value_t, description_t, memory_layout_t>;
        using self_euler_t = self_euler_type_t<angle_value_t>;

        static inline constexpr e_euler_sequence construction_sequence(e_euler_sequence sequence = description_t::sequence) {
            if constexpr(description_t::construction == e_euler_construction::extrinsic) return invert_euler_sequence(sequence);
            else return sequence;
        }

    public:
        template <is_angle_type_t angle_value_t>
        static c_euler3d from_strong_order(angle_value_t pitch, angle_value_t yaw, angle_value_t roll) {
            c_euler3d result{ };
            result.pitch = pitch;
            result.yaw = yaw;
            result.roll = roll;
            return result;
        }

    public:
        inline constexpr c_euler3d() { }
        inline constexpr c_euler3d(const memory_layout_t& _memory_layout) : memory_layout_t(_memory_layout) { }

        template <typename type_t> requires ntl::compatibility::data_type_convertertable<type_t, c_euler3d>
        inline constexpr c_euler3d(const type_t& value) : c_euler3d(ntl::compatibility::data_type_converter_t<type_t, c_euler3d>::convert(value)) { }

    public:
        template <e_euler_representation representation = description_t::representation, typename self_t>
        auto matrix(this self_t&& self, e_euler_sequence sequence = construction_sequence()) {
            matrix3x3_t matrix{ };
            switch(sequence) {
                case e_euler_sequence::xyz: matrix = matrix3x3_t::rotation_xyz(self.pitch, self.yaw, self.roll); break;
                case e_euler_sequence::xzy: matrix = matrix3x3_t::rotation_xzy(self.pitch, self.yaw, self.roll); break;
                case e_euler_sequence::yxz: matrix = matrix3x3_t::rotation_yxz(self.pitch, self.yaw, self.roll); break;
                case e_euler_sequence::zyx: matrix = matrix3x3_t::rotation_zyx(self.pitch, self.yaw, self.roll); break;
                case e_euler_sequence::yzx: matrix = matrix3x3_t::rotation_yzx(self.pitch, self.yaw, self.roll); break;
                case e_euler_sequence::zxy: matrix = matrix3x3_t::rotation_zxy(self.pitch, self.yaw, self.roll); break;
            }

            if constexpr(representation == e_euler_representation::pasive) return matrix.transpose();
            else return matrix;
        }

        template <typename self_t, typename point_t>
        vec3_t<point_t> rotate(this self_t&& self, const vec3_t<point_t>& point) {
            return self.matrix() * point;
        }

        template <typename self_t>
        std::tuple<vec3_t<float>, vec3_t<float>, vec3_t<float>> directions(this self_t&& self) {
            matrix3x3_t matrix = self.matrix();
            return std::tuple(
                vec3_t<float>(matrix * description_t::forward).normalized(),
                vec3_t<float>(matrix * description_t::right).normalized(),
                vec3_t<float>(matrix * description_t::up).normalized()
            );
        }

        template <typename self_t>
        vec3_t<float> forward(this self_t&& self) {
            return vec3_t<float>(self.matrix() * description_t::forward).normalized();
        }

        template <typename self_t>
        vec3_t<float> right(this self_t&& self) {
            return vec3_t<float>(self.matrix() * description_t::right).normalized();
        }

        template <typename self_t>
        vec3_t<float> up(this self_t&& self) {
            return vec3_t<float>(self.matrix() * description_t::up).normalized();
        }

    public:
        template <typename self_t>
        auto&& roll_clamp(this self_t&& self) {
            euler_boundires_t::append<typename description_t::roll_clamp_t>(self.roll);
            return self;
        }

        template <typename self_t>
        auto&& roll_normalize(this self_t&& self) {
            euler_boundires_t::append<typename description_t::roll_normalize_t>(self.roll);
            return self;
        }

        template <typename self_t>
        auto&& pitch_clamp(this self_t&& self) {
            euler_boundires_t::append<typename description_t::pitch_clamp_t>(self.pitch);
            return self;
        }

        template <typename self_t>
        auto&& pitch_normalize(this self_t&& self) {
            euler_boundires_t::append<typename description_t::pitch_normalize_t>(self.pitch);
            return self;
        }

        template <typename self_t>
        auto&& yaw_clamp(this self_t&& self) {
            euler_boundires_t::append<typename description_t::yaw_clamp_t>(self.yaw);
            return self;
        }

        template <typename self_t>
        auto&& yaw_normalize(this self_t&& self) {
            euler_boundires_t::append<typename description_t::yaw_normalize_t>(self.yaw);
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
        auto&& look_rotation(this self_t&& self, vec3_t<direction_t> forward, vec3_t<direction_t> up = description_t::up) {
            forward.normalize();
            up.normalize();

            self.pitch = -angle_t<angle_value_t>::atan2(description_t::up.dot(forward), forward.xz().length());
            self.yaw = angle_t<angle_value_t>::atan2(description_t::right.dot(forward), description_t::forward.dot(forward));
            self.roll = -angle_t<angle_value_t>::atan2(description_t::forward.dot(up), up.xy().length());

            self.normalize();
            return self;
        }

    public:
        template <typename type_t> requires ntl::compatibility::data_type_convertertable<c_euler3d, type_t>
        inline constexpr operator type_t() const { return ntl::compatibility::data_type_converter_t<c_euler3d, type_t>::convert(*this); }

        template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.axes[i]; }

        NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, NULLSDK_FAST_OPS_ARGS_PACK(template <typename self_t, is_angle_type_t angle_other_t>), const self_euler_type_t<angle_other_t>&, RHS_FIELD, x, y, z);
        NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, angle_value_t, RHS_VALUE, x, y, z);
        NULLSDK_FAST_OPS_STRUCTURE_SELF_EQUAL_OPERATOR(inline constexpr, NULLSDK_FAST_OPS_ARGS_PACK(template <typename self_t, is_angle_type_t angle_other_t>), const self_euler_type_t<angle_other_t>&, RHS_FIELD, x, y, z);
        NULLSDK_FAST_OPS_STRUCTURE_SELF_EQUAL_OPERATOR(inline constexpr, template <typename self_t>, angle_value_t, RHS_VALUE, x, y, z);

        NULLSDK_FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, NULLSDK_FAST_OPS_ARGS_PACK(template <typename self_t, is_angle_type_t angle_other_t>), const self_euler_type_t<angle_other_t>&, RHS_FIELD, x, y, z);
        NULLSDK_FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, template <typename self_t>, angle_value_t, RHS_VALUE, x, y, z);
    };

    std::false_type is_euler3d_type_impl(...);
    template <is_angle_type_t angle_value_t, typename description_t, typename memory_layout_t>
    std::true_type is_euler3d_type_impl(c_euler3d<angle_value_t, description_t, memory_layout_t>);

    template <typename type_t>
    using is_euler3d_type_t = decltype(is_euler3d_type_impl(std::declval<type_t>()));
}

#define NULLSDK_FAST_DEFS__UNPACK_TUPLE_ELEMENT__EULER_RAW_CTOR(i, data, elem)              \
    angle_type_t BOOST_PP_CAT(_, NULLSDK_FAST_DEFS__UNPACK_TUPLE_ELEMENT__(i, data, elem))  \

#define NULLSDK_FAST_DEFS__UNPACK_TUPLE_ELEMENT__EULER_TYPE_CTOR(i, data, elem)                             \
    const angle_t<angle_type_t>& BOOST_PP_CAT(_, NULLSDK_FAST_DEFS__UNPACK_TUPLE_ELEMENT__(i, data, elem))  \

#define NULLSDK_MAKE_EULER_MEMORY_LAYOUT(layout_name, ...)                                                          \
namespace ntl::sdk {                                                                                                \
    template <is_angle_type_t angle_value_t>                                                                        \
    struct euler_##layout_name##_memory_layout_t {                                                                  \
    public:                                                                                                         \
        template <is_angle_type_t angle_type_t>                                                                     \
        using order_t = vec3_t<angle_type_t>;                                                                       \
        template <is_angle_type_t angle_type_t>                                                                     \
        using angles_order_t = vec3_t<angle_t<angle_type_t>>;                                                       \
                                                                                                                    \
        union {                                                                                                     \
            struct { angle_t<angle_value_t> NULLSDK_FAST_DEFS__UNPACK_SEQ_ENUM(0, , __VA_ARGS__); };                \
            struct { angle_t<angle_value_t> NULLSDK_FAST_DEFS__UNPACK_SEQ_ENUM(1, , __VA_ARGS__); };                \
            angles_order_t<angle_value_t> axes{ };                                                                  \
        };                                                                                                          \
                                                                                                                    \
    public:                                                                                                         \
        euler_##layout_name##_memory_layout_t() { }                                                                 \
        template <is_angle_type_t angle_type_t>                                                                     \
        euler_##layout_name##_memory_layout_t(NULLSDK_FAST_DEFS__UNPACK_SEQ_ENUM(1, EULER_RAW_CTOR, __VA_ARGS__))   \
            : roll(_roll), pitch(_pitch), yaw(_yaw) { }                                                             \
        template <is_angle_type_t angle_type_t>                                                                     \
        euler_##layout_name##_memory_layout_t(NULLSDK_FAST_DEFS__UNPACK_SEQ_ENUM(1, EULER_TYPE_CTOR, __VA_ARGS__))  \
            : roll(_roll), pitch(_pitch), yaw(_yaw) { }                                                             \
        template <is_angle_type_t angle_type_t>                                                                     \
        euler_##layout_name##_memory_layout_t(const order_t<angle_type_t>& _axes) : axes(_axes) { }                 \
        template <is_angle_type_t angle_type_t>                                                                     \
        euler_##layout_name##_memory_layout_t(const angles_order_t<angle_type_t>& _axes) : axes(_axes) { }          \
    };                                                                                                              \
}                                                                                                                   \
                                                                                                                    \

#define NULLSDK_MAKE_EULER_MEMORY_LAYOUT_SHORTCAT(impl_name)                                                                                        \
    template <ntl::sdk::is_angle_type_t angle_value_t, typename description_t = ntl::sdk::default_euler_description_t>                              \
    using euler3d_##impl_name##_t = ntl::sdk::c_euler3d<angle_value_t, description_t, ntl::sdk::euler_##impl_name##_memory_layout_t<angle_value_t>>;\

//@note: For the standard description of the coordinate order, the coordinate system from aviation is used,
//       in which roll - x, pitch - y, yaw - z.

//@note: x      y     z  | standard order
//      roll, pitch, yaw |
// 
//       x      y     z  | the order of this implementation
//      roll, pitch, yaw |
NULLSDK_MAKE_EULER_MEMORY_LAYOUT(xyz, (x, roll), (y, pitch), (z, yaw));
//        y     z    x   | the order of this implementation
//      pitch, yaw, roll |
NULLSDK_MAKE_EULER_MEMORY_LAYOUT(yzx, (y, pitch), (z, yaw), (x, roll));


template <ntl::sdk::is_angle_type_t angle_value_t, typename description_t = ntl::sdk::default_euler_description_t>
using euler3d_t = ntl::sdk::c_euler3d<angle_value_t, description_t, ntl::sdk::euler_xyz_memory_layout_t<angle_value_t>>;

NULLSDK_MAKE_EULER_MEMORY_LAYOUT_SHORTCAT(yzx);