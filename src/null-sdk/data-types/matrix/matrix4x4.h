#pragma once
#include "matrix.h"

template <typename major_type_t>
class c_matrix4x4 : public null::sdk::i_matrix<major_type_t, float, 4, 4> {
public:
    static inline c_matrix4x4 projection_ortho(float left, float right, float bottom, float top, float near_plane, float far_plane) {
        return c_matrix4x4{
            vec4_t(2.f / (right - left), 0.f,                  0.f,                          -(right + left) / (right - left)                    ),
            vec4_t(0.f,                  2.f / (top - bottom), 0.f,                          -(top + bottom) / (top - bottom)                    ),
            vec4_t(0.f,                  0.f,                  2 / (far_plane - near_plane), -(far_plane + near_plane) / (far_plane - near_plane)),
            vec4_t(0.f,                  0.f,                  0.f,                          1.f                                                 )
        };
    }

    static inline c_matrix4x4 projection_perspective(float left, float right, float bottom, float top, float near_plane, float far_plane) {
        return c_matrix4x4(
            vec4_t(2.f * near_plane / (right - left), 0.f,                               (right + left) / (right - left),                      0.f                                                       ),
            vec4_t(0.f,                               2.f * near_plane / (top - bottom), (top + bottom) / (top - bottom),                      0.f                                                       ),
            vec4_t(0.f,                               0.f,                               -(far_plane + near_plane) / (far_plane - near_plane), -(2.f * far_plane * near_plane) / (far_plane - near_plane)),
            vec4_t(0.f,                               0.f,                               -1.f,                                                 0.f                                                       )
        );
    }

public:
    using null::sdk::i_matrix<major_type_t, float, 4, 4>::i_matrix;
    inline c_matrix4x4(const null::sdk::i_matrix<major_type_t, float, 4, 4>& matrix) : null::sdk::i_matrix<major_type_t, float, 4, 4>(matrix) { }
};
using matrix4x4_t = c_matrix4x4<null::sdk::column_major_t>;