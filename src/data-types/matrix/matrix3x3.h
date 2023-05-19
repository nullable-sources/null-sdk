#pragma once
#include <data-types/matrix/matrix.h>
#include <math/geometry.h>

template <template <typename, typename, typename, size_t, size_t> class major_type_t>
class c_matrix3x3 : public null::sdk::i_matrix<major_type_t, float, 3, 3> {
public: using null::sdk::i_matrix<major_type_t, float, 3, 3>::i_matrix;
	  static c_matrix3x3 rotation_x(const radians_t& angle, const math::e_rotation& direction = math::e_rotation::ccw) {
		  const float cos{ std::cos(angle) }, sin{ std::sin(angle) };
		  return { {
			  { 1.f, 0.f,												0.f,											},
			  { 0.f, cos,												direction == math::e_rotation::ccw ? -sin : sin },
			  { 0.f, direction == math::e_rotation::ccw ? sin : -sin,	cos												}
		  } };
	  }

	  static c_matrix3x3 rotation_y(const radians_t& angle, const math::e_rotation& direction = math::e_rotation::ccw) {
		  const float cos{ std::cos(angle) }, sin{ std::sin(angle) };
		  return { {
			  { cos,												0.f, direction == math::e_rotation::ccw ? sin : -sin	},
			  { 0.f,												1.f, 0.f												},
			  { direction == math::e_rotation::ccw ? -sin : sin,	0.f, cos												}
		  } };
	  }

	  static c_matrix3x3 rotation_z(const radians_t& angle, const math::e_rotation& direction = math::e_rotation::ccw) {
		  const float cos{ std::cos(angle) }, sin{ std::sin(angle) };
		  return { {
			  { cos,												direction == math::e_rotation::ccw ? -sin : sin,	0.f },
			  { direction == math::e_rotation::ccw ? sin : -sin,	cos,												0.f },
			  { 0.f,												0.f,												1.f	}
		  } };
	  }

public:
	c_matrix3x3(const null::sdk::i_matrix<major_type_t, float, 3, 3>& matrix) : null::sdk::i_matrix<major_type_t, float, 3, 3>{ matrix } { }
};
using matrix3x3_t = c_matrix3x3<null::sdk::column_major_t>;