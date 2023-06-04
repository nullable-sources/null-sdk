module;
#include <cmath>
#include <algorithm>
export module null.sdk:math;

import :math.vec2;
import :math.vec3;
import :math.vec4;
import :math.rect;

//@note: Yes, thrash code, yes shit, but what can I do? I'm fucked up trying to put i_vec2<x_t, y_t>/i_vec3<x_t, y_t, z_t>/i_vec4<x_t, y_t, z_t, w_t>/i_rect<x_t, y_t> in one argument to use only one impl_math_make_arg implementation.
#define impl_math_arg(arg) arg

#define impl_math_get_define(_1, _2, _3, _4, _5, name, ...) name
#define impl_math_make_args(...) impl_math_arg(impl_math_get_define(__VA_ARGS__, impl_math_make_arg_4, impl_math_make_arg_3, impl_math_make_arg_2, impl_math_make_arg_1, impl_math_make_arg)(__VA_ARGS__))
#define impl_math_make_arg_1(type, _arg)			type _arg
#define impl_math_make_arg_2(type, _1, _2)			impl_math_make_arg_1(type, _1),			impl_math_make_arg_1(type, _2)
#define impl_math_make_arg_3(type, _1, _2, _3)		impl_math_make_arg_2(type, _1, _2),		impl_math_make_arg_1(type, _3)
#define impl_math_make_arg_4(type, _1, _2, _3, _4)	impl_math_make_arg_3(type, _1, _2, _3),	impl_math_make_arg_1(type, _4)

#define impl_math_type_get_define(_1, _2, _3, _4, name, ...) name
#define impl_math_type_make_args(type_name, ...) impl_math_arg(impl_math_type_get_define(__VA_ARGS__, impl_math_make_##type_name##_arg_4, impl_math_make_##type_name##_arg_3, impl_math_make_##type_name##_arg_2, impl_math_make_##type_name##_arg_1, impl_math_make_arg)(__VA_ARGS__))
#define impl_math_make_vec2_arg_1(_arg)				const vec2_t<coordinates_t>& _arg
#define impl_math_make_vec2_arg_2(_1, _2)			impl_math_make_vec2_arg_1(_1),			impl_math_make_vec2_arg_1(_2)
#define impl_math_make_vec2_arg_3(_1, _2, _3)		impl_math_make_vec2_arg_2(_1, _2),		impl_math_make_vec2_arg_1(_3)

#define impl_math_make_vec3_arg_1(_arg)				const vec3_t<coordinates_t>& _arg
#define impl_math_make_vec3_arg_2(_1, _2)			impl_math_make_vec3_arg_1(_1),			impl_math_make_vec3_arg_1(_2)
#define impl_math_make_vec3_arg_3(_1, _2, _3)		impl_math_make_vec3_arg_2(_1, _2),		impl_math_make_vec3_arg_1(_3)

#define impl_math_make_vec4_arg_1(_arg)				const vec4_t<coordinates_t>& _arg
#define impl_math_make_vec4_arg_2(_1, _2)			impl_math_make_vec4_arg_1(_1),			impl_math_make_vec4_arg_1(_2)
#define impl_math_make_vec4_arg_3(_1, _2, _3)		impl_math_make_vec4_arg_2(_1, _2),		impl_math_make_vec4_arg_1(_3)
#define impl_math_make_vec4_arg_4(_1, _2, _3, _4)	impl_math_make_vec4_arg_3(_1, _2, _3),	impl_math_make_vec4_arg_1(_4)

#define impl_math_make_rect_arg_1(_arg)				const rect_t<corners_t>& _arg
#define impl_math_make_rect_arg_2(_1, _2)			impl_math_make_rect_arg_1(_1),			impl_math_make_rect_arg_1(_2)
#define impl_math_make_rect_arg_3(_1, _2, _3)		impl_math_make_rect_arg_2(_1, _2),		impl_math_make_rect_arg_1(_3)

#define math_make_templates(data_name, ...) template <impl_math_arg(impl_math_make_args(typename, __VA_ARGS__)), typename data_t = data_name##<__VA_ARGS__>>
#define math_make_vec2_function(name, function, ...)													\
	math_make_templates(vec2_t, coordinates_t)																\
	vec2_t<coordinates_t> name##(impl_math_arg(impl_math_type_make_args(vec2, __VA_ARGS__))) function	\

#define math_make_vec3_function(name, function, ...)															\
	math_make_templates(vec3_t, coordinates_t)																	\
	vec3_t<coordinates_t> name##(impl_math_arg(impl_math_type_make_args(vec3, __VA_ARGS__))) function	\

#define math_make_vec4_function(name, function, ...)																\
	math_make_templates(vec4_t, coordinates_t)																	\
	vec4_t<coordinates_t> name##(impl_math_arg(impl_math_type_make_args(vec4, __VA_ARGS__))) function	\

#define math_make_rect_function(name, function, ...)													\
	math_make_templates(rect_t, corners_t)																\
	rect_t<corners_t> name##(impl_math_arg(impl_math_type_make_args(rect, __VA_ARGS__))) function	\

#define math_make_functions(name, vec2_function, vec3_function, vec4_function, rect_functiom, ...)	\
	math_make_vec2_function(name, vec2_function, __VA_ARGS__)										\
	math_make_vec3_function(name, vec3_function, __VA_ARGS__)										\
	math_make_vec4_function(name, vec4_function, __VA_ARGS__)										\
	math_make_rect_function(name, rect_functiom, __VA_ARGS__)										\

export namespace math {
	math_make_functions(abs,
		{ return data_t(std::abs(a.x), std::abs(a.y)); },
		{ return data_t(std::abs(a.x), std::abs(a.y), std::abs(a.z)); },
		{ return data_t(std::abs(a.x), std::abs(a.y), std::abs(a.z), std::abs(a.w)); },
		{ return data_t(abs(a.min), abs(a.max)); },
		a);

	math_make_functions(mod,
		{ return data_t(std::fmod(a.x, b.x), std::fmod(a.y, b.y)); },
		{ return data_t(std::fmod(a.x, b.x), std::fmod(a.y, b.y), std::fmod(a.z, b.z)); },
		{ return data_t(std::fmod(a.x, b.x), std::fmod(a.y, b.y), std::fmod(a.z, b.z), std::fmod(a.w, b.w)); },
		{ return data_t(mod(a.min, b.min), mod(a.max, b.max)); },
		a, b);

	math_make_functions(remainder,
		{ return data_t(std::remainder(a.x, b.x), std::remainder(a.y, b.y)); },
		{ return data_t(std::remainder(a.x, b.x), std::remainder(a.y, b.y), std::remainder(a.z, b.z)); },
		{ return data_t(std::remainder(a.x, b.x), std::remainder(a.y, b.y), std::remainder(a.z, b.z), std::remainder(a.w, b.w)); },
		{ return data_t(remainder(a.min, b.min), remainder(a.max, b.max)); },
		a, b);

	math_make_functions(fma,
		{ return data_t(std::fma(a.x, b.x, c.x), std::fma(a.y, b.y, c.y)); },
		{ return data_t(std::fma(a.x, b.x, c.x), std::fma(a.y, b.y, c.y), std::fma(a.z, b.z, c.z)); },
		{ return data_t(std::fma(a.x, b.x, c.x), std::fma(a.y, b.y, c.y), std::fma(a.z, b.z, c.z), std::fma(a.w, b.w, c.w)); },
		{ return data_t(fma(a.min, b.min, c.min), fma(a.max, b.max, c.max)); },
		a, b, c);

	math_make_functions(dim,
		{ return data_t(std::fdim(a.x, b.x), std::fdim(a.y, b.y)); },
		{ return data_t(std::fdim(a.x, b.x), std::fdim(a.y, b.y), std::fdim(a.z, b.z)); },
		{ return data_t(std::fdim(a.x, b.x), std::fdim(a.y, b.y), std::fdim(a.z, b.z), std::fdim(a.w, b.w)); },
		{ return data_t(dim(a.min, b.min), dim(a.max, b.max)); },
		a, b);

	math_make_functions(ceil,
		{ return data_t(std::ceil(a.x), std::ceil(a.y)); },
		{ return data_t(std::ceil(a.x), std::ceil(a.y), std::ceil(a.z)); },
		{ return data_t(std::ceil(a.x), std::ceil(a.y), std::ceil(a.z), std::ceil(a.w)); },
		{ return data_t(ceil(a.min), ceil(a.max)); },
		a);

	math_make_functions(floor,
		{ return data_t(std::floor(a.x), std::floor(a.y)); },
		{ return data_t(std::floor(a.x), std::floor(a.y), std::floor(a.z)); },
		{ return data_t(std::floor(a.x), std::floor(a.y), std::floor(a.z), std::floor(a.w)); },
		{ return data_t(floor(a.min), floor(a.max)); },
		a);

	math_make_functions(trunc,
		{ return data_t(std::trunc(a.x), std::trunc(a.y)); },
		{ return data_t(std::trunc(a.x), std::trunc(a.y), std::trunc(a.z)); },
		{ return data_t(std::trunc(a.x), std::trunc(a.y), std::trunc(a.z), std::trunc(a.w)); },
		{ return data_t(trunc(a.min), trunc(a.max)); },
		a);

	math_make_functions(round,
		{ return data_t(std::round(a.x), std::round(a.y)); },
		{ return data_t(std::round(a.x), std::round(a.y), std::round(a.z)); },
		{ return data_t(std::round(a.x), std::round(a.y), std::round(a.z), std::round(a.w)); },
		{ return data_t(round(a.min), round(a.max)); },
		a);

	math_make_functions(nearbyint,
		{ return data_t(std::nearbyint(a.x), std::nearbyint(a.y)); },
		{ return data_t(std::nearbyint(a.x), std::nearbyint(a.y), std::nearbyint(a.z)); },
		{ return data_t(std::nearbyint(a.x), std::nearbyint(a.y), std::nearbyint(a.z), std::nearbyint(a.w)); },
		{ return data_t(nearbyint(a.min), nearbyint(a.max)); },
		a);

	math_make_functions(rint,
		{ return data_t(std::rint(a.x), std::rint(a.y)); },
		{ return data_t(std::rint(a.x), std::rint(a.y), std::rint(a.z)); },
		{ return data_t(std::rint(a.x), std::rint(a.y), std::rint(a.z), std::rint(a.w)); },
		{ return data_t(rint(a.min), rint(a.max)); },
		a);

	math_make_functions(clamp,
		{ return data_t(std::clamp(a.x, min.x, max.x), std::clamp(a.y, min.y, max.y)); },
		{ return data_t(std::clamp(a.x, min.x, max.x), std::clamp(a.y, min.y, max.y), std::clamp(a.z, min.z, max.z)); },
		{ return data_t(std::clamp(a.x, min.x, max.x), std::clamp(a.y, min.y, max.y), std::clamp(a.z, min.z, max.z), std::clamp(a.w, min.w, max.w)); },
		{ return data_t(clamp(a.min, min.min, max.min), clamp(a.max, min.max, max.max)); },
		a, min, max);

	math_make_functions(min,
		{ return data_t(std::min(a.x, b.x), std::min(a.y, b.y)); },
		{ return data_t(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)); },
		{ return data_t(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w)); },
		{ return data_t(min(a.min, b.min), min(a.max, b.max)); },
		a, b);

	math_make_functions(max,
		{ return data_t(std::max(a.x, b.x), std::max(a.y, b.y)); },
		{ return data_t(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)); },
		{ return data_t(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w)); },
		{ return data_t(max(a.min, b.min), max(a.max, b.max)); },
		a, b);

	//@note: std::lerp does not support non-arithmetic types
	auto lerp(auto a, auto b, auto t) { return a + t * (b - a); }
}