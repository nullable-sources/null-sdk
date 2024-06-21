#pragma once
#include <numbers>
#include <cmath>
#include <array>
#include "../data-types/vec3.h"
#include "../data-types/vec4.h"
#include "../data-types/rect.h"

//@note: Yes, thrash code, yes shit, but what can I do? I'm fucked up trying to put i_vec2<x_t, y_t>/i_vec3<x_t, y_t, z_t>/i_vec4<x_t, y_t, z_t, w_t>/i_rect<x_t, y_t> in one argument to use only one impl_math_make_arg implementation.
#define impl_math_arg(arg) arg

#define impl_math_get_body(field, _1, _2, _3, name, ...) name
#define impl_math_make_body(...)																\
	impl_math_arg(																				\
		impl_math_get_body(																		\
			__VA_ARGS__, impl_math_body_3, impl_math_body_2, impl_math_body_1, impl_math_body	\
		)(__VA_ARGS__)																			\
	)																							\

#define impl_math_body_1(field, variable)	variable.field
#define impl_math_body_2(field, _1, _2)		impl_math_body_1(field, _1),		impl_math_body_1(field, _2)
#define impl_math_body_3(field, _1, _2, _3)	impl_math_body_2(field, _1, _2),	impl_math_body_1(field, _3)

#define impl_math_get_define(_1, _2, _3, _4, _5, name, ...) name
#define impl_math_define_args(...) impl_math_arg(impl_math_get_define(__VA_ARGS__, impl_math_define_arg_4, impl_math_define_arg_3, impl_math_define_arg_2, impl_math_define_arg_1, impl_math_define_arg)(__VA_ARGS__))
#define impl_math_define_arg_1(type, _arg)				type _arg
#define impl_math_define_arg_2(type, _1, _2)			impl_math_define_arg_1(type, _1),			impl_math_define_arg_1(type, _2)
#define impl_math_define_arg_3(type, _1, _2, _3)		impl_math_define_arg_2(type, _1, _2),		impl_math_define_arg_1(type, _3)
#define impl_math_define_arg_4(type, _1, _2, _3, _4)	impl_math_define_arg_3(type, _1, _2, _3),	impl_math_define_arg_1(type, _4)

#define impl_math_type_get_define(_1, _2, _3, _4, name, ...) name
#define impl_math_type_define_args(type_name, ...) impl_math_arg(impl_math_type_get_define(__VA_ARGS__, impl_math_define_##type_name##_arg_4, impl_math_define_##type_name##_arg_3, impl_math_define_##type_name##_arg_2, impl_math_define_##type_name##_arg_1, impl_math_define_arg)(__VA_ARGS__))
#define impl_math_define_vec2_arg_1(_arg)		const vec2_t<coordinates_t>& _arg
#define impl_math_define_vec2_arg_2(_1, _2)		impl_math_define_vec2_arg_1(_1),		impl_math_define_vec2_arg_1(_2)
#define impl_math_define_vec2_arg_3(_1, _2, _3)	impl_math_define_vec2_arg_2(_1, _2),	impl_math_define_vec2_arg_1(_3)

#define impl_math_define_vec3_arg_1(_arg)		const vec3_t<coordinates_t>& _arg
#define impl_math_define_vec3_arg_2(_1, _2)		impl_math_define_vec3_arg_1(_1),		impl_math_define_vec3_arg_1(_2)
#define impl_math_define_vec3_arg_3(_1, _2, _3)	impl_math_define_vec3_arg_2(_1, _2),	impl_math_define_vec3_arg_1(_3)

#define impl_math_define_vec4_arg_1(_arg)			const vec4_t<coordinates_t>& _arg
#define impl_math_define_vec4_arg_2(_1, _2)			impl_math_define_vec4_arg_1(_1),			impl_math_define_vec4_arg_1(_2)
#define impl_math_define_vec4_arg_3(_1, _2, _3)		impl_math_define_vec4_arg_2(_1, _2),		impl_math_define_vec4_arg_1(_3)
#define impl_math_define_vec4_arg_4(_1, _2, _3, _4)	impl_math_define_vec4_arg_3(_1, _2, _3),	impl_math_define_vec4_arg_1(_4)

#define impl_math_define_rect_arg_1(_arg)		const rect_t<corners_t>& _arg
#define impl_math_define_rect_arg_2(_1, _2)		impl_math_define_rect_arg_1(_1),		impl_math_define_rect_arg_1(_2)
#define impl_math_define_rect_arg_3(_1, _2, _3)	impl_math_define_rect_arg_2(_1, _2),	impl_math_define_rect_arg_1(_3)

#define math_define_templates(data_name, ...) template <impl_math_arg(impl_math_define_args(typename, __VA_ARGS__)), typename data_t = data_name##<__VA_ARGS__>>

#define math_define_vec2_function(name, function, ...)																	\
	math_define_templates(vec2_t, coordinates_t)																		\
	static inline vec2_t<coordinates_t> name##(impl_math_arg(impl_math_type_define_args(vec2, __VA_ARGS__))) function	\

#define math_define_vec3_function(name, function, ...)																	\
	math_define_templates(vec3_t, coordinates_t)																		\
	static inline vec3_t<coordinates_t> name##(impl_math_arg(impl_math_type_define_args(vec3, __VA_ARGS__))) function	\

#define math_define_vec4_function(name, function, ...)																	\
	math_define_templates(vec4_t, coordinates_t)																		\
	static inline vec4_t<coordinates_t> name##(impl_math_arg(impl_math_type_define_args(vec4, __VA_ARGS__))) function	\

#define math_define_rect_function(name, function, ...)																\
	math_define_templates(rect_t, corners_t)																		\
	static inline rect_t<corners_t> name##(impl_math_arg(impl_math_type_define_args(rect, __VA_ARGS__))) function	\

#define math_make_vec2_function(name, ...) { return data_t(name##(impl_math_make_body(x, __VA_ARGS__)), name##(impl_math_make_body(y, __VA_ARGS__))); }
#define math_make_vec3_function(name, ...) { return data_t(name##(impl_math_make_body(x, __VA_ARGS__)), name##(impl_math_make_body(y, __VA_ARGS__)), name##(impl_math_make_body(z, __VA_ARGS__))); }
#define math_make_vec4_function(name, ...) { return data_t(name##(impl_math_make_body(x, __VA_ARGS__)), name##(impl_math_make_body(y, __VA_ARGS__)), name##(impl_math_make_body(z, __VA_ARGS__)), name##(impl_math_make_body(w, __VA_ARGS__))); }
#define math_make_rect_function(name, ...) { return data_t(name##(impl_math_make_body(min, __VA_ARGS__)), name##(impl_math_make_body(max, __VA_ARGS__))); }

#define math_define_functions(name, std_name, ...)													\
	math_define_vec2_function(name, math_make_vec2_function(std_name, __VA_ARGS__), __VA_ARGS__)	\
	math_define_vec3_function(name, math_make_vec3_function(std_name, __VA_ARGS__), __VA_ARGS__)	\
	math_define_vec4_function(name, math_make_vec4_function(std_name, __VA_ARGS__), __VA_ARGS__)	\
	math_define_rect_function(name, math_make_rect_function(name, __VA_ARGS__), __VA_ARGS__)		\

namespace math {
    math_define_functions(abs, std::abs, a);
    math_define_functions(mod, std::fmod, a, b);
    math_define_functions(remainder, std::remainder, a, b);
    math_define_functions(fma, std::fma, a, b, c);
    math_define_functions(dim, std::fdim, a, b);

    math_define_functions(ceil, std::ceil, a);
    math_define_functions(floor, std::floor, a);
    math_define_functions(trunc, std::trunc, a);
    math_define_functions(round, std::round, a);
    math_define_functions(nearbyint, std::nearbyint, a);
    math_define_functions(rint, std::rint, a);

    math_define_functions(clamp, std::clamp, a, min, max);
    math_define_functions(min, std::min, a, b);
    math_define_functions(max, std::max, a, b);

    //@note: std::lerp does not support non-arithmetic types
    static inline constexpr auto lerp(auto a, auto b, auto t) { return a + t * (b - a); }
}