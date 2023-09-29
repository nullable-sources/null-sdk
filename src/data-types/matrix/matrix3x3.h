#pragma once
#include "data-types/matrix/matrix.h"
#include "math/geometry.h"

template <template <typename, typename, typename, size_t, size_t> class major_type_t>
class c_matrix3x3 : public null::sdk::i_matrix<major_type_t, float, 3, 3> {
public:
	static c_matrix3x3 rotation_x(radians_t angle, math::e_rotation direction = math::e_rotation::ccw) {
		const float cos{ std::cosf(angle) }, sin{ std::sinf(angle) };
		return { {
			{ 1.f, 0.f,												0.f,											},
			{ 0.f, cos,												direction == math::e_rotation::ccw ? -sin : sin },
			{ 0.f, direction == math::e_rotation::ccw ? sin : -sin,	cos												}
		} };
	}

	static c_matrix3x3 rotation_y(radians_t angle, math::e_rotation direction = math::e_rotation::ccw) {
		const float cos{ std::cosf(angle) }, sin{ std::sinf(angle) };
		return { {
			{ cos,												0.f, direction == math::e_rotation::ccw ? sin : -sin	},
			{ 0.f,												1.f, 0.f												},
			{ direction == math::e_rotation::ccw ? -sin : sin,	0.f, cos												}
		} };
	}

	static c_matrix3x3 rotation_z(radians_t angle, math::e_rotation direction = math::e_rotation::ccw) {
		const float cos{ std::cosf(angle) }, sin{ std::sinf(angle) };
		return { {
			{ cos,												direction == math::e_rotation::ccw ? -sin : sin,	0.f },
			{ direction == math::e_rotation::ccw ? sin : -sin,	cos,												0.f },
			{ 0.f,												0.f,												1.f	}
		} };
	}

	static c_matrix3x3 rotation_around_axis(const vec3_t<float>& axis, radians_t angle) {
		const float cos{ std::cosf(angle) }, sin{ std::sinf(angle) };
		const vec3_t<float> normalized{ axis.normalized() };
		return { {
			{ std::powf(normalized.x, 2) * (1.f - cos) + cos,					normalized.x * normalized.y * (1.f - cos) - normalized.z * sin, normalized.x * normalized.z * (1.f - cos) + normalized.y * sin	},
			{ normalized.y * normalized.x * (1.f - cos) + normalized.z * sin,	std::powf(normalized.y, 2) * (1.f - cos) + cos,					normalized.y * normalized.z * (1.f - cos) - normalized.x * sin	},
			{ normalized.z * normalized.x * (1.f - cos) - normalized.y * sin,	normalized.z * normalized.y * (1.f - cos) + normalized.x * sin,	std::powf(normalized.z, 2) * (1.f - cos) + cos					}
		} };
	}

public:
	using null::sdk::i_matrix<major_type_t, float, 3, 3>::i_matrix;
	c_matrix3x3(const null::sdk::i_matrix<major_type_t, float, 3, 3>& matrix) : null::sdk::i_matrix<major_type_t, float, 3, 3>{ matrix } { }
};
using matrix3x3_t = c_matrix3x3<null::sdk::column_major_t>;