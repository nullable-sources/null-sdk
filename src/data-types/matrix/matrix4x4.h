#pragma once
#include <data-types/matrix/matrix.h>

template <template <typename, typename, typename, size_t, size_t> class major_type_t>
class c_matrix4x4 : public null::sdk::i_matrix<major_type_t, float, 4, 4> {
public: using null::sdk::i_matrix<major_type_t, float, 4, 4>::i_matrix;
	  static c_matrix4x4 projection_ortho(const float& left, const float& right, const float& bottom, const float& top, const float& near_plane, const float& far_plane) {
		  return { {
			  { 2.f / (right - left),	0.f,					0.f,							-(right + left) / (right - left)						},
			  { 0.f,					2.f / (top - bottom),	0.f,							-(top + bottom) / (top - bottom)						},
			  { 0.f,					0.f,					2 / (far_plane - near_plane),	-(far_plane + near_plane) / (far_plane - near_plane)	},
			  { 0.f,					0.f,					0.f,							1.f														}
		  } };
	  }

	  static c_matrix4x4 projection_perspective(const float& left, const float& right, const float& bottom, const float& top, const float& near_plane, const float& far_plane) {
		  return { {
			  { 2.f * near_plane / (right - left),	0.f,								(right + left) / (right - left),						0.f															},
			  { 0.f,								2.f * near_plane / (top - bottom),	(top + bottom) / (top - bottom),						0.f															},
			  { 0.f,								0.f,								-(far_plane + near_plane) / (far_plane - near_plane),	-(2.f * far_plane * near_plane) / (far_plane - near_plane)	},
			  { 0.f,								0.f,								-1.f,													0.f															}
		  } };
	  }
};
using matrix4x4_t = c_matrix4x4<null::sdk::column_major_t>;