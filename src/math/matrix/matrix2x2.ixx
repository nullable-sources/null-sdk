module;
#include <cmath>
export module null.sdk:math.matrix2x2;

import :math.matrix;
import :math.angle;
import :math.geometry;

export template <template <typename, typename, typename, size_t, size_t> class major_type_t>
class c_matrix2x2 : public null::sdk::i_matrix<major_type_t, float, 2, 2> {
public:
	static c_matrix2x2 rotation(radians_t angle, math::e_rotation direction = math::e_rotation::ccw) {
		const float cos{ std::cosf(angle) }, sin{ std::sinf(angle) };
		return { {
			{ cos,												direction == math::e_rotation::ccw ? -sin : sin },
			{ direction == math::e_rotation::ccw ? sin : -sin,	cos },
		} };
	}

public: using null::sdk::i_matrix<major_type_t, float, 3, 3>::i_matrix;
	c_matrix2x2(const null::sdk::i_matrix<major_type_t, float, 2, 2>& matrix) : null::sdk::i_matrix<major_type_t, float, 2, 2>{ matrix } { }
};
export using matrix2x2_t = c_matrix2x2<null::sdk::column_major_t>;