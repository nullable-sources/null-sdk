#pragma once
#include <numbers>
#include <cmath>
#include <array>
#include "../data-types/vec3.h"
#include "../data-types/vec4.h"
#include "../data-types/rect.h"

//@note: Yes, thrash code, yes shit, but what can I do? I'm fucked up trying to put i_vec2<x_t, y_t>/i_vec3<x_t, y_t, z_t>/i_vec4<x_t, y_t, z_t, w_t>/i_rect<x_t, y_t> in one argument to use only one impl_math_make_arg implementation.
#define FAST_DEFS__MATH_IMPL_MATH_GET_BODY(field, _1, _2, _3, name, ...) name
#define FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(...)                                                                                                                \
    BOOST_PP_EXPAND(                                                                                                                                            \
        FAST_DEFS__MATH_IMPL_MATH_GET_BODY(                                                                                                                     \
            __VA_ARGS__, FAST_DEFS__MATH_IMPL_MATH_BODY_3, FAST_DEFS__MATH_IMPL_MATH_BODY_2, FAST_DEFS__MATH_IMPL_MATH_BODY_1, FAST_DEFS__MATH_IMPL_MATH_BODY   \
        )(__VA_ARGS__)                                                                                                                                          \
    )                                                                                                                                                           \

#define FAST_DEFS__MATH_IMPL_MATH_BODY_1(field, variable)   variable.field
#define FAST_DEFS__MATH_IMPL_MATH_BODY_2(field, _1, _2)     FAST_DEFS__MATH_IMPL_MATH_BODY_1(field, _1),        FAST_DEFS__MATH_IMPL_MATH_BODY_1(field, _2)
#define FAST_DEFS__MATH_IMPL_MATH_BODY_3(field, _1, _2, _3) FAST_DEFS__MATH_IMPL_MATH_BODY_2(field, _1, _2),    FAST_DEFS__MATH_IMPL_MATH_BODY_1(field, _3)

#define FAST_DEFS__MATH_IMPL_MATH_GET_DEFINE(_1, _2, _3, _4, _5, name, ...) name
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARGS(...) BOOST_PP_EXPAND(FAST_DEFS__MATH_IMPL_MATH_GET_DEFINE(__VA_ARGS__, FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_4, FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_3, FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_2, FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_1, FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG)(__VA_ARGS__))
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_1(type, _arg)              type _arg
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_2(type, _1, _2)            FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_1(type, _1),           FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_1(type, _2)
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_3(type, _1, _2, _3)        FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_2(type, _1, _2),       FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_1(type, _3)
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_4(type, _1, _2, _3, _4)    FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_3(type, _1, _2, _3),   FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG_1(type, _4)

#define FAST_DEFS__MATH_IMPL_MATH_TYPE_GET_DEFINE(_1, _2, _3, _4, name, ...) name
#define FAST_DEFS__MATH_IMPL_MATH_TYPE_DEFINE_ARGS(type_name, ...) BOOST_PP_EXPAND(FAST_DEFS__MATH_IMPL_MATH_TYPE_GET_DEFINE(__VA_ARGS__, impl_math_define_##type_name##_arg_4, impl_math_define_##type_name##_arg_3, impl_math_define_##type_name##_arg_2, impl_math_define_##type_name##_arg_1, FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARG)(__VA_ARGS__))
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC2_ARG_1(_arg)       const vec2_t<coordinates_t>& _arg
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC2_ARG_2(_1, _2)     FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC2_ARG_1(_1),        FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC2_ARG_1(_2)
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC2_ARG_3(_1, _2, _3) FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC2_ARG_2(_1, _2),    FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC2_ARG_1(_3)

#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC3_ARG_1(_arg)       const vec3_t<coordinates_t>& _arg
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC3_ARG_2(_1, _2)     FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC3_ARG_1(_1),        FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC3_ARG_1(_2)
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC3_ARG_3(_1, _2, _3) FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC3_ARG_2(_1, _2),    FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC3_ARG_1(_3)

#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC4_ARG_1(_arg)           const vec4_t<coordinates_t>& _arg
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC4_ARG_2(_1, _2)         FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC4_ARG_1(_1),            FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC4_ARG_1(_2)
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC4_ARG_3(_1, _2, _3)     FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC4_ARG_2(_1, _2),        FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC4_ARG_1(_3)
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC4_ARG_4(_1, _2, _3, _4) FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC4_ARG_3(_1, _2, _3),    FAST_DEFS__MATH_IMPL_MATH_DEFINE_VEC4_ARG_1(_4)

#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_RECT_ARG_1(_arg)       const rect_t<corners_t>& _arg
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_RECT_ARG_2(_1, _2)     FAST_DEFS__MATH_IMPL_MATH_DEFINE_RECT_ARG_1(_1),        FAST_DEFS__MATH_IMPL_MATH_DEFINE_RECT_ARG_1(_2)
#define FAST_DEFS__MATH_IMPL_MATH_DEFINE_RECT_ARG_3(_1, _2, _3) FAST_DEFS__MATH_IMPL_MATH_DEFINE_RECT_ARG_2(_1, _2),    FAST_DEFS__MATH_IMPL_MATH_DEFINE_RECT_ARG_1(_3)

#define FAST_DEFS__MATH_DEFINE_TEMPLATES(data_name, ...) template <BOOST_PP_EXPAND(FAST_DEFS__MATH_IMPL_MATH_DEFINE_ARGS(typename, __VA_ARGS__)), typename data_t = data_name##<__VA_ARGS__>>

#define FAST_DEFS__MATH_DEFINE_VEC2_FUNCTION(name, function, ...)                                                                       \
    FAST_DEFS__MATH_DEFINE_TEMPLATES(vec2_t, coordinates_t)                                                                             \
    static inline vec2_t<coordinates_t> name##(BOOST_PP_EXPAND(FAST_DEFS__MATH_IMPL_MATH_TYPE_DEFINE_ARGS(vec2, __VA_ARGS__))) function \

#define FAST_DEFS__MATH_DEFINE_VEC3_FUNCTION(name, function, ...)                                                                       \
    FAST_DEFS__MATH_DEFINE_TEMPLATES(vec3_t, coordinates_t)                                                                             \
    static inline vec3_t<coordinates_t> name##(BOOST_PP_EXPAND(FAST_DEFS__MATH_IMPL_MATH_TYPE_DEFINE_ARGS(vec3, __VA_ARGS__))) function \

#define FAST_DEFS__MATH_DEFINE_VEC4_FUNCTION(name, function, ...)                                                                       \
    FAST_DEFS__MATH_DEFINE_TEMPLATES(vec4_t, coordinates_t)                                                                             \
    static inline vec4_t<coordinates_t> name##(BOOST_PP_EXPAND(FAST_DEFS__MATH_IMPL_MATH_TYPE_DEFINE_ARGS(vec4, __VA_ARGS__))) function \

#define FAST_DEFS__MATH_DEFINE_RECT_FUNCTION(name, function, ...)                                                                   \
    FAST_DEFS__MATH_DEFINE_TEMPLATES(rect_t, corners_t)                                                                             \
    static inline rect_t<corners_t> name##(BOOST_PP_EXPAND(FAST_DEFS__MATH_IMPL_MATH_TYPE_DEFINE_ARGS(rect, __VA_ARGS__))) function \

#define FAST_DEFS__MATH_MAKE_VEC2_FUNCTION(name, ...) { return data_t(name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(x, __VA_ARGS__)), name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(y, __VA_ARGS__))); }
#define FAST_DEFS__MATH_MAKE_VEC3_FUNCTION(name, ...) { return data_t(name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(x, __VA_ARGS__)), name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(y, __VA_ARGS__)), name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(z, __VA_ARGS__))); }
#define FAST_DEFS__MATH_MAKE_VEC4_FUNCTION(name, ...) { return data_t(name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(x, __VA_ARGS__)), name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(y, __VA_ARGS__)), name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(z, __VA_ARGS__)), name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(w, __VA_ARGS__))); }
#define FAST_DEFS__MATH_MAKE_RECT_FUNCTION(name, ...) { return data_t(name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(min, __VA_ARGS__)), name##(FAST_DEFS__MATH_IMPL_MATH_MAKE_BODY(max, __VA_ARGS__))); }

#define FAST_DEFS__MATH_DEFINE_FUNCTIONS(name, std_name, ...)                                                           \
    FAST_DEFS__MATH_DEFINE_VEC2_FUNCTION(name, FAST_DEFS__MATH_MAKE_VEC2_FUNCTION(std_name, __VA_ARGS__), __VA_ARGS__)  \
    FAST_DEFS__MATH_DEFINE_VEC3_FUNCTION(name, FAST_DEFS__MATH_MAKE_VEC3_FUNCTION(std_name, __VA_ARGS__), __VA_ARGS__)  \
    FAST_DEFS__MATH_DEFINE_VEC4_FUNCTION(name, FAST_DEFS__MATH_MAKE_VEC4_FUNCTION(std_name, __VA_ARGS__), __VA_ARGS__)  \
    FAST_DEFS__MATH_DEFINE_RECT_FUNCTION(name, FAST_DEFS__MATH_MAKE_RECT_FUNCTION(name, __VA_ARGS__), __VA_ARGS__)      \

namespace ntl::math {
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(abs, std::abs, a);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(mod, std::fmod, a, b);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(remainder, std::remainder, a, b);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(fma, std::fma, a, b, c);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(dim, std::fdim, a, b);

    FAST_DEFS__MATH_DEFINE_FUNCTIONS(ceil, std::ceil, a);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(floor, std::floor, a);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(trunc, std::trunc, a);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(round, std::round, a);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(nearbyint, std::nearbyint, a);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(rint, std::rint, a);

    FAST_DEFS__MATH_DEFINE_FUNCTIONS(clamp, std::clamp, a, min, max);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(min, std::min, a, b);
    FAST_DEFS__MATH_DEFINE_FUNCTIONS(max, std::max, a, b);

    //@note: std::lerp does not support non-arithmetic types
    static inline constexpr auto lerp(auto a, auto b, auto t) { return a + t * (b - a); }
}