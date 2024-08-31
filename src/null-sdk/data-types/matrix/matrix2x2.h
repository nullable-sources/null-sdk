#pragma once
#include "matrix.h"
#include "../../math/geometry.h"

template <typename major_type_t>
class c_matrix2x2 : public ntl::sdk::i_matrix<major_type_t, float, 2, 2> {
public:
    static inline c_matrix2x2 rotation(radians_t angle, ntl::math::e_rotation direction = ntl::math::e_rotation::ccw) {
        const float cos = std::cosf(angle), sin = std::sinf(angle);
        return c_matrix2x2(
            vec2_t(cos,                                                  direction == ntl::math::e_rotation::ccw ? -sin : sin),
            vec2_t(direction == ntl::math::e_rotation::ccw ? sin : -sin, cos)
        );
    }

public:
    using ntl::sdk::i_matrix<major_type_t, float, 2, 2>::i_matrix;
    inline c_matrix2x2(const ntl::sdk::i_matrix<major_type_t, float, 2, 2>& matrix) : ntl::sdk::i_matrix<major_type_t, float, 2, 2>(matrix) { }
};
using matrix2x2_t = c_matrix2x2<ntl::sdk::column_major_t>;