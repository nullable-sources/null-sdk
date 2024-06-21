#pragma once
#include "matrix.h"
#include "../../math/geometry.h"

template <typename major_type_t>
class c_matrix2x2 : public null::sdk::i_matrix<major_type_t, float, 2, 2> {
public:
    static inline c_matrix2x2 rotation(radians_t angle, math::e_rotation direction = math::e_rotation::ccw) {
        const float cos = std::cosf(angle), sin = std::sinf(angle);
        return c_matrix2x2(
            vec2_t(cos,                                             direction == math::e_rotation::ccw ? -sin : sin),
            vec2_t(direction == math::e_rotation::ccw ? sin : -sin, cos)
        );
    }

public:
    using null::sdk::i_matrix<major_type_t, float, 2, 2>::i_matrix;
    inline c_matrix2x2(const null::sdk::i_matrix<major_type_t, float, 2, 2>& matrix) : null::sdk::i_matrix<major_type_t, float, 2, 2>(matrix) { }
};
using matrix2x2_t = c_matrix2x2<null::sdk::column_major_t>;