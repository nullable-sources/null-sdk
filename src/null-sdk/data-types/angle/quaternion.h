#pragma once
#include "euler3d.h"

struct quaternion_t : public vec4_t<float> {
public: using vec4_t::vec4_t;
public:
    static inline constexpr quaternion_t identity() { return quaternion_t(0.f, 0.f, 0.f, 1.f); }

    static inline quaternion_t axis_angle(const vec3_t<float>& axis, radians_t radians) {
        angle_t<radians_t> angle(radians * 0.5);
        return quaternion_t(axis * angle.sin(), angle.cos());
    }

    static inline quaternion_t from_to_rotation(vec3_t<float> from, vec3_t<float> to) {
        from.normalize(); to.normalize();
        radians_t half_angle = 0.5 * from.dot(to);
        return quaternion_t(from.cross(to).normalized() * std::sqrt(0.5 - half_angle), std::sqrt(0.5 + half_angle));
    }

    static inline quaternion_t look_rotation(vec3_t<float> forward, vec3_t<float> up) {
        ntl::math::orthonormalize(forward, up);
        vec3_t<float> right = up.cross(forward);

        float w = std::sqrt(1.f + right.x + up.y + forward.z) * 0.5f;
        return quaternion_t(vec3_t<float>(up.z - forward.y, forward.x - right.z, right.y - up.x) * (1.f / (4.f * w)), w);
    }

    template <typename euler_t>
    static inline quaternion_t euler(const euler_t& euler, ntl::sdk::e_euler_sequence sequence = euler_t::construction_sequence()) {
        switch(sequence) {
            case ntl::sdk::e_euler_sequence::xyz:
                return axis_angle(euler_t::used_description_t::right,   euler.pitch)
                     * axis_angle(euler_t::used_description_t::up,      euler.yaw)
                     * axis_angle(euler_t::used_description_t::forward, euler.roll);
            case ntl::sdk::e_euler_sequence::xzy:
                return axis_angle(euler_t::used_description_t::right,   euler.pitch)
                     * axis_angle(euler_t::used_description_t::forward, euler.roll)
                     * axis_angle(euler_t::used_description_t::up,      euler.yaw);
            case ntl::sdk::e_euler_sequence::yxz:
                return axis_angle(euler_t::used_description_t::up,      euler.yaw)
                     * axis_angle(euler_t::used_description_t::right,   euler.pitch)
                     * axis_angle(euler_t::used_description_t::forward, euler.roll);
            case ntl::sdk::e_euler_sequence::zyx:
                return axis_angle(euler_t::used_description_t::forward, euler.roll)
                     * axis_angle(euler_t::used_description_t::up,      euler.yaw)
                     * axis_angle(euler_t::used_description_t::right,   euler.pitch);
            case ntl::sdk::e_euler_sequence::yzx:
                return axis_angle(euler_t::used_description_t::up,      euler.yaw)
                     * axis_angle(euler_t::used_description_t::forward, euler.roll)
                     * axis_angle(euler_t::used_description_t::right,   euler.pitch);
            case ntl::sdk::e_euler_sequence::zxy:
                return axis_angle(euler_t::used_description_t::forward, euler.roll)
                     * axis_angle(euler_t::used_description_t::right,   euler.pitch)
                     * axis_angle(euler_t::used_description_t::up,      euler.yaw);
        }
    }

    static inline quaternion_t matrix(const matrix3x3_t& matrix) {
        quaternion_t quat{ };
        float r = matrix[0][0] + matrix[1][1] + matrix[2][2];
        if(r > 0) {
            quat.w = std::sqrt(r + 1.f) * 0.5f;
            float inv4w = 1.f / (4.f * quat.w);
            quat.x = (matrix[1][2] - matrix[2][1]) * inv4w;
            quat.y = (matrix[2][0] - matrix[0][2]) * inv4w;
            quat.z = (matrix[0][1] - matrix[1][0]) * inv4w;
        } else if(matrix[0][0] > matrix[1][1] && matrix[0][0] > matrix[2][2]) {
            quat.x = std::sqrt(1.f + matrix[0][0] - matrix[1][1] - matrix[2][2]) * 0.5f;
            const float x4 = 1.f / (4.f * quat.x);
            quat.y = (matrix[1][0] + matrix[0][1]) * x4;
            quat.z = (matrix[2][0] + matrix[0][2]) * x4;
            quat.w = (matrix[1][2] - matrix[2][1]) * x4;
        } else if(matrix[1][1] > matrix[2][2]) {
            quat.y = std::sqrt(1.f + matrix[1][1] - matrix[0][0] - matrix[2][2]) * 0.5f;
            const float y4 = 1.f / (4.f * quat.y);
            quat.x = (matrix[1][0] + matrix[0][1]) * y4;
            quat.z = (matrix[2][1] + matrix[1][2]) * y4;
            quat.w = (matrix[2][0] - matrix[0][2]) * y4;
        } else {
            quat.z = std::sqrt(1.f + matrix[2][2] - matrix[0][0] - matrix[1][1]) * 0.5f;
            const float z4 = 1.f / (4.f * quat.z);
            quat.x = (matrix[2][0] + matrix[0][2]) * z4;
            quat.y = (matrix[2][1] + matrix[1][2]) * z4;
            quat.w = (matrix[0][1] - matrix[1][0]) * z4;
        }
        return quat;
    }

public:
    inline constexpr quaternion_t() { }

public:
    inline quaternion_t normalized(this auto&& self) { return self / self.length(); }
    template <typename self_t> inline auto&& normalize(this self_t&& self) { self /= self.length(); return self; }

    inline quaternion_t conjugated() const { return quaternion_t(-x, -y, -z, w); }
    template <typename self_t> inline auto&& conjugate(this self_t&& self) { self = self.conjugated(); return self; }

    vec3_t<float> axis(this auto&& self) { return self.xyz() * (1.f / std::sqrt(1.f - std::pow(self.w, 2))); }
    radians_t angle(this auto&& self) { return angle_t<radians_t>(self.w).acos() * 2.; }
    radians_t angle_between(this auto&& self, const quaternion_t& quat) { return (quat / self).normalized().angle(); }
    vec3_t<float> axis_from_to(this auto&& self, const quaternion_t& quat) { return (quat / self).normalized().axis(); }

    quaternion_t slerp(this auto&& self, const quaternion_t& quat, double t) {
        angle_t<radians_t> angle = radians_t(self.dot(quat));
        float sign = 1;
        if(angle < 0.) {
            angle = -angle;
            sign = -1;
        }

        float a{ }, b{ };
        if(angle < 0.999) {
            angle = angle.acos();
            angle_t<radians_t> ta = angle * angle_t<radians_t>(t);
            a = angle_t<radians_t>(angle - ta).sin() * sign;
            b = ta.sin();
        } else {
            a = (1.f - t) * sign;
            b = t;
        }
        
        return (self * a + quat * b).normalized();
    }

    matrix3x3_t matrix(this auto&& self) {
        auto [forward, right, up] = self.directions();
        return matrix3x3_t(
            vec3_t<float>(right.x, up.x, forward.x),
            vec3_t<float>(right.y, up.y, forward.y),
            vec3_t<float>(right.z, up.z, forward.z)
        );
    }

    vec3_t<radians_t> forward(this auto&& self) { return vec3_t<radians_t>(2 * (self.x * self.z + self.y * self.w),     2 * (self.y * self.z - self.x * self.w),     1 - 2 * (self.x * self.x + self.y * self.y)); }
    vec3_t<radians_t> right(this auto&& self)   { return vec3_t<radians_t>(1 - 2 * (self.y * self.y + self.z * self.z), 2 * (self.x * self.y + self.z * self.w),     2 * (self.x * self.z - self.y * self.w)); }
    vec3_t<radians_t> up(this auto&& self)      { return vec3_t<radians_t>(2 * (self.x * self.y - self.z * self.w),     1 - 2 * (self.x * self.x + self.z * self.z), 2 * (self.y * self.z + self.x * self.w)); }
    std::tuple<vec3_t<radians_t>, vec3_t<radians_t>, vec3_t<radians_t>> directions() const { return std::tuple(forward(), right(), up()); }

    template <typename euler_t> 
    euler_t euler(this auto&& self, ntl::sdk::e_euler_sequence sequence = euler_t::construction_sequence()) {
        auto [forward, right, up] = self.directions();
        switch(sequence) {
            case ntl::sdk::e_euler_sequence::xyz: {
                if(forward.x >= 1.f)  return euler_t::from_strong_order(std::atan2(right.y, up.y), std::numbers::pi / 2., 0.);
                if(forward.x <= -1.f) return euler_t::from_strong_order(-std::atan2(right.y, up.y), -std::numbers::pi / 2., 0.);

                return euler_t::from_strong_order(
                    std::atan2(-forward.y, forward.z),
                    std::asin(forward.x),
                    std::atan2(-up.x, right.x)
                );
            };
            case ntl::sdk::e_euler_sequence::xzy: {
                if(up.x >= 1.f)  return euler_t::from_strong_order(std::atan2(-right.z, forward.z), 0., -std::numbers::pi / 2.);
                if(up.x <= -1.f) return euler_t::from_strong_order(-std::atan2(-right.z, forward.z), 0., std::numbers::pi / 2.);

                return euler_t::from_strong_order(
                    std::atan2(up.z, up.y),
                    std::atan2(forward.x, right.x),
                    std::asin(-up.x)
                );
            };
            case ntl::sdk::e_euler_sequence::yxz: {
                if(forward.y >= 1.f)  return euler_t::from_strong_order(-std::numbers::pi / 2., std::atan2(-up.x, right.x), 0.);
                if(forward.y <= -1.f) return euler_t::from_strong_order(std::numbers::pi / 2., -std::atan2(-up.x, right.x), 0.);

                return euler_t::from_strong_order(
                    std::asin(-forward.y),
                    std::atan2(forward.x, forward.z),
                    std::atan2(right.y, up.y)
                );
            };
            case ntl::sdk::e_euler_sequence::zyx: {
                if(right.z >= 1.f)  return euler_t::from_strong_order(0., -std::numbers::pi / 2., std::atan2(-forward.y, up.y));
                if(right.z <= -1.f) return euler_t::from_strong_order(0., std::numbers::pi / 2., -std::atan2(-forward.y, up.y));

                return euler_t::from_strong_order(
                    std::atan2(up.z, forward.z),
                    std::asin(-right.z),
                    std::atan2(right.y, right.x)
                );
            };
            case ntl::sdk::e_euler_sequence::yzx: {
                if(right.y >= 1.f)  return euler_t::from_strong_order(0., std::atan2(up.z, forward.z), std::numbers::pi / 2.);
                if(right.y <= -1.f) return euler_t::from_strong_order(0., -std::atan2(up.z, forward.z), -std::numbers::pi / 2.);

                return euler_t::from_strong_order(
                    std::atan2(-forward.y, up.y),
                    std::atan2(-right.z, right.x),
                    std::asin(right.y)
                );
            };
            case ntl::sdk::e_euler_sequence::zxy: {
                if(up.z >= 1.f)  return euler_t::from_strong_order(std::numbers::pi / 2., 0., std::atan2(forward.x, right.x));
                if(up.z <= -1.f) return euler_t::from_strong_order(-std::numbers::pi / 2., 0., -std::atan2(forward.x, right.x));

                return euler_t::from_strong_order(
                    std::asin(up.z),
                    std::atan2(-right.z, forward.z),
                    std::atan2(-up.x, up.y)
                );
            };
        }
    }

public:
    template <typename self_t>
    inline constexpr auto operator *(this self_t&& self, const quaternion_t& rhs) {
        return quaternion_t(
            self.x * rhs.w + self.y * rhs.z - self.z * rhs.y + self.w * rhs.x,
           -self.x * rhs.z + self.y * rhs.w + self.z * rhs.x + self.w * rhs.y,
            self.x * rhs.y - self.y * rhs.x + self.z * rhs.w + self.w * rhs.z,
           -self.x * rhs.x - self.y * rhs.y - self.z * rhs.z + self.w * rhs.w
        );
    }

    template <typename self_t>
    inline constexpr auto operator /(this self_t&& self, const quaternion_t& rhs) {
        return quaternion_t(
            self.x * rhs.w - self.y * rhs.z + self.z * rhs.y - self.w * rhs.x,
            self.x * rhs.z + self.y * rhs.w - self.z * rhs.x - self.w * rhs.y,
           -self.x * rhs.y + self.y * rhs.x + self.z * rhs.w - self.w * rhs.z,
            self.x * rhs.x + self.y * rhs.y + self.z * rhs.z + self.w * rhs.w
        );
    }

    template <typename self_t>
    inline constexpr auto operator /(this self_t&& self, double rhs) {
        return self * (1. / rhs);
    }

    template <typename self_t, typename euler_t> requires ntl::sdk::is_euler3d_type_t<euler_t>::value
    inline operator euler_t(this self_t&& self) { return self.euler<euler_t>(); }
};