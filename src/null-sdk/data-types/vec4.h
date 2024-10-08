#pragma once
#include <cmath>
#include "vec3.h"

template <typename coord_t>
struct vec4_t;

namespace ntl::sdk {
#define NULLSDK_FAST_DEFS__VEC4_GETTER(_x, _y, _z, _w) template <typename self_t> inline constexpr auto _x##_y##_z##_w(this self_t&& self) { return vec4_t<coord_t>(self. _x, self. _y, self. _z, self. _w); }

#define NULLSDK_FAST_DEFS__VEC4_SETTER(_x, _y, _z, _w)                                                                                                                                                                                                \
    template <typename self_t> inline constexpr auto&& _x##_y##_z##_w(this self_t&& self, coord_t rhs) { self. _x = self. _y = self. _z = self. _w = rhs; return self; }                                                                        \
    template <typename self_t> inline constexpr auto&& _x##_y##_z##_w(this self_t&& self, coord_t x_rhs, coord_t y_rhs, coord_t z_rhs, coord_t w_rhs) { self. _x = x_rhs; self. _y = y_rhs; self. _z = z_rhs; self. _w = w_rhs; return self; }  \
    template <typename self_t> inline constexpr auto&& _x##_y##_z##_w(this self_t&& self, const vec4_t<coord_t>& rhs) { self ._x = rhs.x; self. _y = rhs.y; self. _z = rhs.z; self. _w = rhs.w; return self; }                                  \

    //@todo: either change the compiler (msvc is not able to compile the implementation via BOOST_PP_SEQ_FOR_EACH_PRODUCT), or wait for its support to appear (I doubt that this will happen)
    template <typename coord_t>
    struct vec4_getter_t {
    public:
        NULLSDK_FAST_DEFS__VEC2_SETTER(x, y);
        NULLSDK_FAST_DEFS__VEC2_SETTER(x, z);
        NULLSDK_FAST_DEFS__VEC2_SETTER(x, w);
        NULLSDK_FAST_DEFS__VEC2_SETTER(y, x);
        NULLSDK_FAST_DEFS__VEC2_SETTER(y, z);
        NULLSDK_FAST_DEFS__VEC2_SETTER(y, w);
        NULLSDK_FAST_DEFS__VEC2_SETTER(z, x);
        NULLSDK_FAST_DEFS__VEC2_SETTER(z, y);
        NULLSDK_FAST_DEFS__VEC2_SETTER(z, w);
        NULLSDK_FAST_DEFS__VEC2_SETTER(w, x);
        NULLSDK_FAST_DEFS__VEC2_SETTER(w, y);
        NULLSDK_FAST_DEFS__VEC2_SETTER(w, z);

        NULLSDK_FAST_DEFS__VEC3_SETTER(x, y, z);
        NULLSDK_FAST_DEFS__VEC3_SETTER(x, y, w);
        NULLSDK_FAST_DEFS__VEC3_SETTER(x, z, y);
        NULLSDK_FAST_DEFS__VEC3_SETTER(x, z, w);
        NULLSDK_FAST_DEFS__VEC3_SETTER(x, w, y);
        NULLSDK_FAST_DEFS__VEC3_SETTER(x, w, z);
        NULLSDK_FAST_DEFS__VEC3_SETTER(y, x, z);
        NULLSDK_FAST_DEFS__VEC3_SETTER(y, x, w);
        NULLSDK_FAST_DEFS__VEC3_SETTER(y, z, x);
        NULLSDK_FAST_DEFS__VEC3_SETTER(y, z, w);
        NULLSDK_FAST_DEFS__VEC3_SETTER(y, w, x);
        NULLSDK_FAST_DEFS__VEC3_SETTER(y, w, z);
        NULLSDK_FAST_DEFS__VEC3_SETTER(z, x, y);
        NULLSDK_FAST_DEFS__VEC3_SETTER(z, x, w);
        NULLSDK_FAST_DEFS__VEC3_SETTER(z, y, x);
        NULLSDK_FAST_DEFS__VEC3_SETTER(z, y, w);
        NULLSDK_FAST_DEFS__VEC3_SETTER(z, w, x);
        NULLSDK_FAST_DEFS__VEC3_SETTER(z, w, y);
        NULLSDK_FAST_DEFS__VEC3_SETTER(w, x, y);
        NULLSDK_FAST_DEFS__VEC3_SETTER(w, x, z);
        NULLSDK_FAST_DEFS__VEC3_SETTER(w, y, x);
        NULLSDK_FAST_DEFS__VEC3_SETTER(w, y, z);
        NULLSDK_FAST_DEFS__VEC3_SETTER(w, z, x);
        NULLSDK_FAST_DEFS__VEC3_SETTER(w, z, y);

        NULLSDK_FAST_DEFS__VEC4_SETTER(x, y, z, w);
        NULLSDK_FAST_DEFS__VEC4_SETTER(x, y, w, z);
        NULLSDK_FAST_DEFS__VEC4_SETTER(x, z, y, w);
        NULLSDK_FAST_DEFS__VEC4_SETTER(x, z, w, y);
        NULLSDK_FAST_DEFS__VEC4_SETTER(x, w, y, z);
        NULLSDK_FAST_DEFS__VEC4_SETTER(x, w, z, y);
        NULLSDK_FAST_DEFS__VEC4_SETTER(y, x, z, w);
        NULLSDK_FAST_DEFS__VEC4_SETTER(y, x, w, z);
        NULLSDK_FAST_DEFS__VEC4_SETTER(y, z, x, w);
        NULLSDK_FAST_DEFS__VEC4_SETTER(y, z, w, x);
        NULLSDK_FAST_DEFS__VEC4_SETTER(y, w, x, z);
        NULLSDK_FAST_DEFS__VEC4_SETTER(y, w, z, x);
        NULLSDK_FAST_DEFS__VEC4_SETTER(z, x, y, w);
        NULLSDK_FAST_DEFS__VEC4_SETTER(z, x, w, y);
        NULLSDK_FAST_DEFS__VEC4_SETTER(z, y, x, w);
        NULLSDK_FAST_DEFS__VEC4_SETTER(z, y, w, x);
        NULLSDK_FAST_DEFS__VEC4_SETTER(z, w, x, y);
        NULLSDK_FAST_DEFS__VEC4_SETTER(z, w, y, x);
        NULLSDK_FAST_DEFS__VEC4_SETTER(w, x, y, z);
        NULLSDK_FAST_DEFS__VEC4_SETTER(w, x, z, y);
        NULLSDK_FAST_DEFS__VEC4_SETTER(w, y, x, z);
        NULLSDK_FAST_DEFS__VEC4_SETTER(w, y, z, x);
        NULLSDK_FAST_DEFS__VEC4_SETTER(w, z, x, y);
        NULLSDK_FAST_DEFS__VEC4_SETTER(w, z, y, x);

        NULLSDK_FAST_DEFS__VEC2_GETTER(x, x);
        NULLSDK_FAST_DEFS__VEC2_GETTER(x, y);
        NULLSDK_FAST_DEFS__VEC2_GETTER(x, z);
        NULLSDK_FAST_DEFS__VEC2_GETTER(x, w);
        NULLSDK_FAST_DEFS__VEC2_GETTER(y, x);
        NULLSDK_FAST_DEFS__VEC2_GETTER(y, y);
        NULLSDK_FAST_DEFS__VEC2_GETTER(y, z);
        NULLSDK_FAST_DEFS__VEC2_GETTER(y, w);
        NULLSDK_FAST_DEFS__VEC2_GETTER(z, x);
        NULLSDK_FAST_DEFS__VEC2_GETTER(z, y);
        NULLSDK_FAST_DEFS__VEC2_GETTER(z, z);
        NULLSDK_FAST_DEFS__VEC2_GETTER(z, w);
        NULLSDK_FAST_DEFS__VEC2_GETTER(w, x);
        NULLSDK_FAST_DEFS__VEC2_GETTER(w, y);
        NULLSDK_FAST_DEFS__VEC2_GETTER(w, z);
        NULLSDK_FAST_DEFS__VEC2_GETTER(w, w);

        NULLSDK_FAST_DEFS__VEC3_GETTER(x, x, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, x, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, x, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, x, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, y, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, y, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, y, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, y, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, z, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, z, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, z, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, z, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, w, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, w, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, w, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, w, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, x, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, x, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, x, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, x, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, y, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, y, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, y, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, y, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, z, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, z, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, z, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, z, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, w, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, w, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, w, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, w, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, x, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, x, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, x, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, x, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, y, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, y, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, y, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, y, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, z, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, z, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, z, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, z, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, w, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, w, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, w, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, w, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, x, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, x, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, x, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, x, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, y, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, y, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, y, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, y, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, z, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, z, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, z, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, z, w);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, w, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, w, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, w, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(w, w, w);

        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, x, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, y, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, z, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(x, w, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, x, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, y, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, z, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(y, w, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, x, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, y, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, z, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(z, w, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, x, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, y, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, z, w, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, x, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, x, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, x, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, x, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, y, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, y, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, y, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, y, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, z, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, z, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, z, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, z, w);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, w, x);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, w, y);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, w, z);
        NULLSDK_FAST_DEFS__VEC4_GETTER(w, w, w, w);
    };
}

template <typename coord_t>
struct vec4_t : public ntl::sdk::vec4_getter_t<coord_t> {
public:
    static constexpr size_t array_size = 4; //@note: size array{ x, y, z, w }

public:
    union {
        struct { coord_t x, y, z, w; };
        std::array<coord_t, array_size> coordinates{ };
    };

public:
    inline constexpr vec4_t() { }

    inline constexpr vec4_t(coord_t value) : vec4_t(value, value, value, value) { }
    inline constexpr vec4_t(coord_t _x, coord_t _y, coord_t _z, coord_t _w) : x(_x), y(_y), z(_z), w(_w) { }

    inline constexpr vec4_t(const vec3_t<coord_t>& vec, coord_t _w = { }) : x(vec.x), y(vec.y), z(vec.z), w(_w) { }
    inline constexpr vec4_t(const vec2_t<coord_t>& vec, coord_t _z = { }, coord_t _w = { }) : x(vec.x), y(vec.y), z(_z), w(_w) { }

    inline vec4_t(const std::array<coord_t, array_size>& _coordinates) : coordinates(_coordinates) { }
    inline vec4_t(const std::vector<coord_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), std::min(_coordinates.size(), array_size)), coordinates.begin()); }
    inline vec4_t(const std::tuple<coord_t, coord_t, coord_t, coord_t>& tuple) : coordinates(std::apply([](auto... n) { return std::array(n...); }, tuple)) { }
    inline vec4_t(const std::tuple<coord_t, coord_t, coord_t>& tuple, coord_t _w = { }) : coordinates(std::apply([&](auto... n) { return std::array(n..., _w); }, tuple)) { }
    inline vec4_t(const std::tuple<coord_t, coord_t>& tuple, coord_t _z = { }, coord_t _w = { }) : coordinates(std::apply([&](auto... n) { return std::array(n..., _z, _w); }, tuple)) { }

    template <typename type_t> requires ntl::compatibility::data_type_convertertable<type_t, vec4_t<coord_t>>
    inline constexpr vec4_t(const type_t& value) : vec4_t(ntl::compatibility::data_type_converter_t<type_t, vec4_t<coord_t>>::convert(value)) { }

public:
    inline float length() const { return std::sqrt(length()); }
    inline float length_sqrt() const { return std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2); }
    inline float dist_to(const vec4_t& vec) const { return vec4_t(*this - vec).length(); }
    inline constexpr float dot(const vec4_t& vec) const { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; }

    vec4_t<coord_t> normalized(this auto&& self) { return self / self.length(); }
    inline void normalize(this auto&& self) { self /= self.length(); }

public:
    NULLSDK_FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, template <typename other_t>, vec4_t<other_t>() const, vec4_t<other_t>, (other_t), x, y, z, w);
    NULLSDK_FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, , NULLSDK_FAST_OPS_ARGS_PACK(std::tuple<coord_t, coord_t, coord_t, coord_t>)() const, std::make_tuple, , x, y, z, w);

    template <typename type_t> requires ntl::compatibility::data_type_convertertable<vec4_t<coord_t>, type_t>
    inline constexpr operator type_t() const { return ntl::compatibility::data_type_converter_t<vec4_t<coord_t>, type_t>::convert(*this); }

    template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.coordinates[i]; }

    NULLSDK_FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(inline constexpr, x, y, z, w);
    NULLSDK_FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(inline constexpr, x, y, z, w);

    NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, NULLSDK_FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const vec4_t<other_t>&, RHS_FIELD, x, y, z, w);
    NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, coord_t, RHS_VALUE, x, y, z, w);

    NULLSDK_FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, template <typename other_t>, const vec4_t<other_t>&, RHS_FIELD, x, y, z, w);
    NULLSDK_FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, , coord_t, RHS_VALUE, x, y, z, w);

    NULLSDK_FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, NULLSDK_FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const vec4_t<other_t>&, RHS_FIELD, x, y, z, w);
    NULLSDK_FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, template <typename self_t>, coord_t, RHS_VALUE, x, y, z, w);
};