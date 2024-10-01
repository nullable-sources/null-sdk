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

    static inline c_matrix3x3 rotation_xyz(radians_t x, radians_t y, radians_t z) {
        const float cx = std::cosf(x), sx = std::sinf(x);
        const float cy = std::cosf(y), sy = std::sinf(y);
        const float cz = std::cosf(z), sz = std::sinf(z);
        return c_matrix3x3(
            vec3_t( cy * cz,                -cy * sz,                     sy),
            vec3_t( cz * sx * sy + cx * sz, cx * cz - sx * sy * sz, -cy * sx),
            vec3_t(-cx * cz * sy + sx * sz, cz * sx + cx * sy * sz,  cx * cy)
        );
    }

    static inline c_matrix3x3 rotation_yzx(radians_t x, radians_t y, radians_t z) {
        const float cx = std::cosf(x), sx = std::sinf(x);
        const float cy = std::cosf(y), sy = std::sinf(y);
        const float cz = std::cosf(z), sz = std::sinf(z);
        return c_matrix3x3(
            vec3_t(cy * cz,  sx * sy - cx * cy * sz, cx * sy + cy * sx * sz),
            vec3_t(sz,       cx * cz,                              -cz * sx),
            vec3_t(-cz * sy, cy * sx + cx * sy * sz, cx * cy - sx * sy * sz)
        );
    }

    static inline c_matrix3x3 rotation_zxy(radians_t x, radians_t y, radians_t z) {
        const float cx = std::cosf(x), sx = std::sinf(x);
        const float cy = std::cosf(y), sy = std::sinf(y);
        const float cz = std::cosf(z), sz = std::sinf(z);
        return c_matrix3x3(
            vec3_t(cy * cz - sx * sy * sz, -cx * sz, cz * sy + cy * sx * sz),
            vec3_t(cz * sx * sy + cy * sz, cx * cz,  -cy * cz * sx + sy * sz),
            vec3_t(-cx * sy,               sx,                       cx * cy)
        );
    }

    static inline c_matrix3x3 rotation_zyx(radians_t x, radians_t y, radians_t z) {
        const float cx = std::cosf(x), sx = std::sinf(x);
        const float cy = std::cosf(y), sy = std::sinf(y);
        const float cz = std::cosf(z), sz = std::sinf(z);
        return c_matrix3x3(
            vec3_t(cy * cz, cz * sx * sy - cx * sz, cx * cz * sy + sx * sz),
            vec3_t(cy * sz, cx * cz + sx * sy * sz, -cz * sx + cx * sy * sz),
            vec3_t(-sy,     cy * sx,                                cx * cy)
        );
    }

    static inline c_matrix3x3 rotation_yxz(radians_t x, radians_t y, radians_t z) {
        const float cx = std::cosf(x), sx = std::sinf(x);
        const float cy = std::cosf(y), sy = std::sinf(y);
        const float cz = std::cosf(z), sz = std::sinf(z);
        return c_matrix3x3(
            vec3_t(cy * cz + sx * sy * sz,  cz * sx * sy - cy * sz, cx * sy),
            vec3_t(cx * sz,                 cx * cz,                    -sx),
            vec3_t(-cz * sy + cy * sx * sz, cy * cz * sx + sy * sz, cx * cy)
       );
    }

    static inline c_matrix3x3 rotation_xzy(radians_t x, radians_t y, radians_t z) {
        const float cx = std::cosf(x), sx = std::sinf(x);
        const float cy = std::cosf(y), sy = std::sinf(y);
        const float cz = std::cosf(z), sz = std::sinf(z);
        return c_matrix3x3(
            vec3_t(cy * cz,                 -sz,                     cz * sy),
            vec3_t(sx * sy + cx * cy * sz,  cx * cz, -cy * sx + cx * sy * sz),
            vec3_t(-cx * sy + cy * sx * sz, cz * sx, cx * cy + sx * sy * sz)
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