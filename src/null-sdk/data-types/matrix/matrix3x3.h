#pragma once
#include "matrix.h"
#include "../../math/geometry.h"

template <typename major_type_t>
class c_matrix3x3 : public ntl::sdk::i_matrix<major_type_t, float, 3, 3> {
public:
    static inline c_matrix3x3 rotation_x(radians_t angle, ntl::math::e_rotation direction = ntl::math::e_rotation::ccw) {
        const float cos = std::cosf(angle), sin = std::sinf(angle);
        return c_matrix3x3(
            vec3_t(1.f, 0.f,                                             0.f                                                 ),
            vec3_t(0.f, cos,                                             direction == ntl::math::e_rotation::ccw ? -sin : sin),
            vec3_t(0.f, direction == ntl::math::e_rotation::ccw ? sin : -sin, cos                                            )
        );
    }

    static inline c_matrix3x3 rotation_y(radians_t angle, ntl::math::e_rotation direction = ntl::math::e_rotation::ccw) {
        const float cos = std::cosf(angle), sin = std::sinf(angle);
        return c_matrix3x3(
            vec3_t(cos,                                             0.f, direction == ntl::math::e_rotation::ccw ? -sin : sin),
            vec3_t(0.f,                                             1.f, 0.f                                                 ),
            vec3_t(direction == ntl::math::e_rotation::ccw ? sin : -sin, 0.f, cos                                            )
        );
    }

    static inline c_matrix3x3 rotation_z(radians_t angle, ntl::math::e_rotation direction = ntl::math::e_rotation::ccw) {
        const float cos = std::cosf(angle), sin = std::sinf(angle);
        return c_matrix3x3(
            vec3_t(cos,                                             direction == ntl::math::e_rotation::ccw ? sin : -sin, 0.f),
            vec3_t(direction == ntl::math::e_rotation::ccw ? -sin : sin, cos,                                             0.f),
            vec3_t(0.f,                                             0.f,                                                  1.f)
        );
    }

    static inline c_matrix3x3 rotation_around_axis(const vec3_t<float>& axis, radians_t angle) {
        const float cos = std::cosf(angle), sin = std::sinf(angle);
        const vec3_t<float> normalized = axis.normalized();
        return c_matrix3x3(
            vec3_t(std::powf(normalized.x, 2) * (1.f - cos) + cos,                 normalized.x * normalized.y * (1.f - cos) - normalized.z * sin, normalized.x * normalized.z * (1.f - cos) + normalized.y * sin),
            vec3_t(normalized.y * normalized.x * (1.f - cos) + normalized.z * sin, std::powf(normalized.y, 2) * (1.f - cos) + cos,                 normalized.y * normalized.z * (1.f - cos) - normalized.x * sin),
            vec3_t(normalized.z * normalized.x * (1.f - cos) - normalized.y * sin, normalized.z * normalized.y * (1.f - cos) + normalized.x * sin, std::powf(normalized.z, 2) * (1.f - cos) + cos                )
        );
    }

public:
    using ntl::sdk::i_matrix<major_type_t, float, 3, 3>::i_matrix;
    inline c_matrix3x3(const ntl::sdk::i_matrix<major_type_t, float, 3, 3>& matrix) : ntl::sdk::i_matrix<major_type_t, float, 3, 3>(matrix) { }
};
using matrix3x3_t = c_matrix3x3<ntl::sdk::column_major_t>;