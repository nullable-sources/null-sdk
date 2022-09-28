#pragma once

template<size_t rows, size_t columns>
struct matrix_t {
public:
	float matrix[rows][columns]{ };
};

using matrix3x4_t = matrix_t<3, 4>;
using matrix4x4_t = matrix_t<4, 4>;