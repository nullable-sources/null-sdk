#pragma once
#include <cmath>
#include "vec3.h"

template <typename coord_t>
struct vec4_t;

namespace ntl::sdk {
#define FAST_DEFS__VEC4_GETTER(_x, _y, _z, _w) template <typename self_t> inline constexpr auto _x##_y##_z##_w(this self_t&& self) { return vec4_t<coord_t>(self. _x, self. _y, self. _z, self. _w); }

#define FAST_DEFS__VEC4_SETTER(_x, _y, _z, _w)                                                                                                                                                                                                \
    template <typename self_t> inline constexpr auto&& _x##_y##_z##_w(this self_t&& self, coord_t rhs) { self. _x = self. _y = self. _z = self. _w = rhs; return self; }                                                                        \
    template <typename self_t> inline constexpr auto&& _x##_y##_z##_w(this self_t&& self, coord_t x_rhs, coord_t y_rhs, coord_t z_rhs, coord_t w_rhs) { self. _x = x_rhs; self. _y = y_rhs; self. _z = z_rhs; self. _w = w_rhs; return self; }  \
    template <typename self_t> inline constexpr auto&& _x##_y##_z##_w(this self_t&& self, const vec4_t<coord_t>& rhs) { self ._x = rhs.x; self. _y = rhs.y; self. _z = rhs.z; self. _w = rhs.w; return self; }                                  \

    //@todo: either change the compiler (msvc is not able to compile the implementation via BOOST_PP_SEQ_FOR_EACH_PRODUCT), or wait for its support to appear (I doubt that this will happen)
    template <typename coord_t>
    struct vec4_getter_t {
    public:
        FAST_DEFS__VEC2_SETTER(x, y);
        FAST_DEFS__VEC2_SETTER(x, z);
        FAST_DEFS__VEC2_SETTER(x, w);
        FAST_DEFS__VEC2_SETTER(y, x);
        FAST_DEFS__VEC2_SETTER(y, z);
        FAST_DEFS__VEC2_SETTER(y, w);
        FAST_DEFS__VEC2_SETTER(z, x);
        FAST_DEFS__VEC2_SETTER(z, y);
        FAST_DEFS__VEC2_SETTER(z, w);
        FAST_DEFS__VEC2_SETTER(w, x);
        FAST_DEFS__VEC2_SETTER(w, y);
        FAST_DEFS__VEC2_SETTER(w, z);

        FAST_DEFS__VEC3_SETTER(x, y, z);
        FAST_DEFS__VEC3_SETTER(x, y, w);
        FAST_DEFS__VEC3_SETTER(x, z, y);
        FAST_DEFS__VEC3_SETTER(x, z, w);
        FAST_DEFS__VEC3_SETTER(x, w, y);
        FAST_DEFS__VEC3_SETTER(x, w, z);
        FAST_DEFS__VEC3_SETTER(y, x, z);
        FAST_DEFS__VEC3_SETTER(y, x, w);
        FAST_DEFS__VEC3_SETTER(y, z, x);
        FAST_DEFS__VEC3_SETTER(y, z, w);
        FAST_DEFS__VEC3_SETTER(y, w, x);
        FAST_DEFS__VEC3_SETTER(y, w, z);
        FAST_DEFS__VEC3_SETTER(z, x, y);
        FAST_DEFS__VEC3_SETTER(z, x, w);
        FAST_DEFS__VEC3_SETTER(z, y, x);
        FAST_DEFS__VEC3_SETTER(z, y, w);
        FAST_DEFS__VEC3_SETTER(z, w, x);
        FAST_DEFS__VEC3_SETTER(z, w, y);
        FAST_DEFS__VEC3_SETTER(w, x, y);
        FAST_DEFS__VEC3_SETTER(w, x, z);
        FAST_DEFS__VEC3_SETTER(w, y, x);
        FAST_DEFS__VEC3_SETTER(w, y, z);
        FAST_DEFS__VEC3_SETTER(w, z, x);
        FAST_DEFS__VEC3_SETTER(w, z, y);

        FAST_DEFS__VEC4_SETTER(x, y, z, w);
        FAST_DEFS__VEC4_SETTER(x, y, w, z);
        FAST_DEFS__VEC4_SETTER(x, z, y, w);
        FAST_DEFS__VEC4_SETTER(x, z, w, y);
        FAST_DEFS__VEC4_SETTER(x, w, y, z);
        FAST_DEFS__VEC4_SETTER(x, w, z, y);
        FAST_DEFS__VEC4_SETTER(y, x, z, w);
        FAST_DEFS__VEC4_SETTER(y, x, w, z);
        FAST_DEFS__VEC4_SETTER(y, z, x, w);
        FAST_DEFS__VEC4_SETTER(y, z, w, x);
        FAST_DEFS__VEC4_SETTER(y, w, x, z);
        FAST_DEFS__VEC4_SETTER(y, w, z, x);
        FAST_DEFS__VEC4_SETTER(z, x, y, w);
        FAST_DEFS__VEC4_SETTER(z, x, w, y);
        FAST_DEFS__VEC4_SETTER(z, y, x, w);
        FAST_DEFS__VEC4_SETTER(z, y, w, x);
        FAST_DEFS__VEC4_SETTER(z, w, x, y);
        FAST_DEFS__VEC4_SETTER(z, w, y, x);
        FAST_DEFS__VEC4_SETTER(w, x, y, z);
        FAST_DEFS__VEC4_SETTER(w, x, z, y);
        FAST_DEFS__VEC4_SETTER(w, y, x, z);
        FAST_DEFS__VEC4_SETTER(w, y, z, x);
        FAST_DEFS__VEC4_SETTER(w, z, x, y);
        FAST_DEFS__VEC4_SETTER(w, z, y, x);

        FAST_DEFS__VEC2_GETTER(x, x);
        FAST_DEFS__VEC2_GETTER(x, y);
        FAST_DEFS__VEC2_GETTER(x, z);
        FAST_DEFS__VEC2_GETTER(x, w);
        FAST_DEFS__VEC2_GETTER(y, x);
        FAST_DEFS__VEC2_GETTER(y, y);
        FAST_DEFS__VEC2_GETTER(y, z);
        FAST_DEFS__VEC2_GETTER(y, w);
        FAST_DEFS__VEC2_GETTER(z, x);
        FAST_DEFS__VEC2_GETTER(z, y);
        FAST_DEFS__VEC2_GETTER(z, z);
        FAST_DEFS__VEC2_GETTER(z, w);
        FAST_DEFS__VEC2_GETTER(w, x);
        FAST_DEFS__VEC2_GETTER(w, y);
        FAST_DEFS__VEC2_GETTER(w, z);
        FAST_DEFS__VEC2_GETTER(w, w);

        FAST_DEFS__VEC3_GETTER(x, x, x);
        FAST_DEFS__VEC3_GETTER(x, x, y);
        FAST_DEFS__VEC3_GETTER(x, x, z);
        FAST_DEFS__VEC3_GETTER(x, x, w);
        FAST_DEFS__VEC3_GETTER(x, y, x);
        FAST_DEFS__VEC3_GETTER(x, y, y);
        FAST_DEFS__VEC3_GETTER(x, y, z);
        FAST_DEFS__VEC3_GETTER(x, y, w);
        FAST_DEFS__VEC3_GETTER(x, z, x);
        FAST_DEFS__VEC3_GETTER(x, z, y);
        FAST_DEFS__VEC3_GETTER(x, z, z);
        FAST_DEFS__VEC3_GETTER(x, z, w);
        FAST_DEFS__VEC3_GETTER(x, w, x);
        FAST_DEFS__VEC3_GETTER(x, w, y);
        FAST_DEFS__VEC3_GETTER(x, w, z);
        FAST_DEFS__VEC3_GETTER(x, w, w);
        FAST_DEFS__VEC3_GETTER(y, x, x);
        FAST_DEFS__VEC3_GETTER(y, x, y);
        FAST_DEFS__VEC3_GETTER(y, x, z);
        FAST_DEFS__VEC3_GETTER(y, x, w);
        FAST_DEFS__VEC3_GETTER(y, y, x);
        FAST_DEFS__VEC3_GETTER(y, y, y);
        FAST_DEFS__VEC3_GETTER(y, y, z);
        FAST_DEFS__VEC3_GETTER(y, y, w);
        FAST_DEFS__VEC3_GETTER(y, z, x);
        FAST_DEFS__VEC3_GETTER(y, z, y);
        FAST_DEFS__VEC3_GETTER(y, z, z);
        FAST_DEFS__VEC3_GETTER(y, z, w);
        FAST_DEFS__VEC3_GETTER(y, w, x);
        FAST_DEFS__VEC3_GETTER(y, w, y);
        FAST_DEFS__VEC3_GETTER(y, w, z);
        FAST_DEFS__VEC3_GETTER(y, w, w);
        FAST_DEFS__VEC3_GETTER(z, x, x);
        FAST_DEFS__VEC3_GETTER(z, x, y);
        FAST_DEFS__VEC3_GETTER(z, x, z);
        FAST_DEFS__VEC3_GETTER(z, x, w);
        FAST_DEFS__VEC3_GETTER(z, y, x);
        FAST_DEFS__VEC3_GETTER(z, y, y);
        FAST_DEFS__VEC3_GETTER(z, y, z);
        FAST_DEFS__VEC3_GETTER(z, y, w);
        FAST_DEFS__VEC3_GETTER(z, z, x);
        FAST_DEFS__VEC3_GETTER(z, z, y);
        FAST_DEFS__VEC3_GETTER(z, z, z);
        FAST_DEFS__VEC3_GETTER(z, z, w);
        FAST_DEFS__VEC3_GETTER(z, w, x);
        FAST_DEFS__VEC3_GETTER(z, w, y);
        FAST_DEFS__VEC3_GETTER(z, w, z);
        FAST_DEFS__VEC3_GETTER(z, w, w);
        FAST_DEFS__VEC3_GETTER(w, x, x);
        FAST_DEFS__VEC3_GETTER(w, x, y);
        FAST_DEFS__VEC3_GETTER(w, x, z);
        FAST_DEFS__VEC3_GETTER(w, x, w);
        FAST_DEFS__VEC3_GETTER(w, y, x);
        FAST_DEFS__VEC3_GETTER(w, y, y);
        FAST_DEFS__VEC3_GETTER(w, y, z);
        FAST_DEFS__VEC3_GETTER(w, y, w);
        FAST_DEFS__VEC3_GETTER(w, z, x);
        FAST_DEFS__VEC3_GETTER(w, z, y);
        FAST_DEFS__VEC3_GETTER(w, z, z);
        FAST_DEFS__VEC3_GETTER(w, z, w);
        FAST_DEFS__VEC3_GETTER(w, w, x);
        FAST_DEFS__VEC3_GETTER(w, w, y);
        FAST_DEFS__VEC3_GETTER(w, w, z);
        FAST_DEFS__VEC3_GETTER(w, w, w);

        FAST_DEFS__VEC4_GETTER(x, x, x, x);
        FAST_DEFS__VEC4_GETTER(x, x, x, y);
        FAST_DEFS__VEC4_GETTER(x, x, x, z);
        FAST_DEFS__VEC4_GETTER(x, x, x, w);
        FAST_DEFS__VEC4_GETTER(x, x, y, x);
        FAST_DEFS__VEC4_GETTER(x, x, y, y);
        FAST_DEFS__VEC4_GETTER(x, x, y, z);
        FAST_DEFS__VEC4_GETTER(x, x, y, w);
        FAST_DEFS__VEC4_GETTER(x, x, z, x);
        FAST_DEFS__VEC4_GETTER(x, x, z, y);
        FAST_DEFS__VEC4_GETTER(x, x, z, z);
        FAST_DEFS__VEC4_GETTER(x, x, z, w);
        FAST_DEFS__VEC4_GETTER(x, x, w, x);
        FAST_DEFS__VEC4_GETTER(x, x, w, y);
        FAST_DEFS__VEC4_GETTER(x, x, w, z);
        FAST_DEFS__VEC4_GETTER(x, x, w, w);
        FAST_DEFS__VEC4_GETTER(x, y, x, x);
        FAST_DEFS__VEC4_GETTER(x, y, x, y);
        FAST_DEFS__VEC4_GETTER(x, y, x, z);
        FAST_DEFS__VEC4_GETTER(x, y, x, w);
        FAST_DEFS__VEC4_GETTER(x, y, y, x);
        FAST_DEFS__VEC4_GETTER(x, y, y, y);
        FAST_DEFS__VEC4_GETTER(x, y, y, z);
        FAST_DEFS__VEC4_GETTER(x, y, y, w);
        FAST_DEFS__VEC4_GETTER(x, y, z, x);
        FAST_DEFS__VEC4_GETTER(x, y, z, y);
        FAST_DEFS__VEC4_GETTER(x, y, z, z);
        FAST_DEFS__VEC4_GETTER(x, y, z, w);
        FAST_DEFS__VEC4_GETTER(x, y, w, x);
        FAST_DEFS__VEC4_GETTER(x, y, w, y);
        FAST_DEFS__VEC4_GETTER(x, y, w, z);
        FAST_DEFS__VEC4_GETTER(x, y, w, w);
        FAST_DEFS__VEC4_GETTER(x, z, x, x);
        FAST_DEFS__VEC4_GETTER(x, z, x, y);
        FAST_DEFS__VEC4_GETTER(x, z, x, z);
        FAST_DEFS__VEC4_GETTER(x, z, x, w);
        FAST_DEFS__VEC4_GETTER(x, z, y, x);
        FAST_DEFS__VEC4_GETTER(x, z, y, y);
        FAST_DEFS__VEC4_GETTER(x, z, y, z);
        FAST_DEFS__VEC4_GETTER(x, z, y, w);
        FAST_DEFS__VEC4_GETTER(x, z, z, x);
        FAST_DEFS__VEC4_GETTER(x, z, z, y);
        FAST_DEFS__VEC4_GETTER(x, z, z, z);
        FAST_DEFS__VEC4_GETTER(x, z, z, w);
        FAST_DEFS__VEC4_GETTER(x, z, w, x);
        FAST_DEFS__VEC4_GETTER(x, z, w, y);
        FAST_DEFS__VEC4_GETTER(x, z, w, z);
        FAST_DEFS__VEC4_GETTER(x, z, w, w);
        FAST_DEFS__VEC4_GETTER(x, w, x, x);
        FAST_DEFS__VEC4_GETTER(x, w, x, y);
        FAST_DEFS__VEC4_GETTER(x, w, x, z);
        FAST_DEFS__VEC4_GETTER(x, w, x, w);
        FAST_DEFS__VEC4_GETTER(x, w, y, x);
        FAST_DEFS__VEC4_GETTER(x, w, y, y);
        FAST_DEFS__VEC4_GETTER(x, w, y, z);
        FAST_DEFS__VEC4_GETTER(x, w, y, w);
        FAST_DEFS__VEC4_GETTER(x, w, z, x);
        FAST_DEFS__VEC4_GETTER(x, w, z, y);
        FAST_DEFS__VEC4_GETTER(x, w, z, z);
        FAST_DEFS__VEC4_GETTER(x, w, z, w);
        FAST_DEFS__VEC4_GETTER(x, w, w, x);
        FAST_DEFS__VEC4_GETTER(x, w, w, y);
        FAST_DEFS__VEC4_GETTER(x, w, w, z);
        FAST_DEFS__VEC4_GETTER(x, w, w, w);
        FAST_DEFS__VEC4_GETTER(y, x, x, x);
        FAST_DEFS__VEC4_GETTER(y, x, x, y);
        FAST_DEFS__VEC4_GETTER(y, x, x, z);
        FAST_DEFS__VEC4_GETTER(y, x, x, w);
        FAST_DEFS__VEC4_GETTER(y, x, y, x);
        FAST_DEFS__VEC4_GETTER(y, x, y, y);
        FAST_DEFS__VEC4_GETTER(y, x, y, z);
        FAST_DEFS__VEC4_GETTER(y, x, y, w);
        FAST_DEFS__VEC4_GETTER(y, x, z, x);
        FAST_DEFS__VEC4_GETTER(y, x, z, y);
        FAST_DEFS__VEC4_GETTER(y, x, z, z);
        FAST_DEFS__VEC4_GETTER(y, x, z, w);
        FAST_DEFS__VEC4_GETTER(y, x, w, x);
        FAST_DEFS__VEC4_GETTER(y, x, w, y);
        FAST_DEFS__VEC4_GETTER(y, x, w, z);
        FAST_DEFS__VEC4_GETTER(y, x, w, w);
        FAST_DEFS__VEC4_GETTER(y, y, x, x);
        FAST_DEFS__VEC4_GETTER(y, y, x, y);
        FAST_DEFS__VEC4_GETTER(y, y, x, z);
        FAST_DEFS__VEC4_GETTER(y, y, x, w);
        FAST_DEFS__VEC4_GETTER(y, y, y, x);
        FAST_DEFS__VEC4_GETTER(y, y, y, y);
        FAST_DEFS__VEC4_GETTER(y, y, y, z);
        FAST_DEFS__VEC4_GETTER(y, y, y, w);
        FAST_DEFS__VEC4_GETTER(y, y, z, x);
        FAST_DEFS__VEC4_GETTER(y, y, z, y);
        FAST_DEFS__VEC4_GETTER(y, y, z, z);
        FAST_DEFS__VEC4_GETTER(y, y, z, w);
        FAST_DEFS__VEC4_GETTER(y, y, w, x);
        FAST_DEFS__VEC4_GETTER(y, y, w, y);
        FAST_DEFS__VEC4_GETTER(y, y, w, z);
        FAST_DEFS__VEC4_GETTER(y, y, w, w);
        FAST_DEFS__VEC4_GETTER(y, z, x, x);
        FAST_DEFS__VEC4_GETTER(y, z, x, y);
        FAST_DEFS__VEC4_GETTER(y, z, x, z);
        FAST_DEFS__VEC4_GETTER(y, z, x, w);
        FAST_DEFS__VEC4_GETTER(y, z, y, x);
        FAST_DEFS__VEC4_GETTER(y, z, y, y);
        FAST_DEFS__VEC4_GETTER(y, z, y, z);
        FAST_DEFS__VEC4_GETTER(y, z, y, w);
        FAST_DEFS__VEC4_GETTER(y, z, z, x);
        FAST_DEFS__VEC4_GETTER(y, z, z, y);
        FAST_DEFS__VEC4_GETTER(y, z, z, z);
        FAST_DEFS__VEC4_GETTER(y, z, z, w);
        FAST_DEFS__VEC4_GETTER(y, z, w, x);
        FAST_DEFS__VEC4_GETTER(y, z, w, y);
        FAST_DEFS__VEC4_GETTER(y, z, w, z);
        FAST_DEFS__VEC4_GETTER(y, z, w, w);
        FAST_DEFS__VEC4_GETTER(y, w, x, x);
        FAST_DEFS__VEC4_GETTER(y, w, x, y);
        FAST_DEFS__VEC4_GETTER(y, w, x, z);
        FAST_DEFS__VEC4_GETTER(y, w, x, w);
        FAST_DEFS__VEC4_GETTER(y, w, y, x);
        FAST_DEFS__VEC4_GETTER(y, w, y, y);
        FAST_DEFS__VEC4_GETTER(y, w, y, z);
        FAST_DEFS__VEC4_GETTER(y, w, y, w);
        FAST_DEFS__VEC4_GETTER(y, w, z, x);
        FAST_DEFS__VEC4_GETTER(y, w, z, y);
        FAST_DEFS__VEC4_GETTER(y, w, z, z);
        FAST_DEFS__VEC4_GETTER(y, w, z, w);
        FAST_DEFS__VEC4_GETTER(y, w, w, x);
        FAST_DEFS__VEC4_GETTER(y, w, w, y);
        FAST_DEFS__VEC4_GETTER(y, w, w, z);
        FAST_DEFS__VEC4_GETTER(y, w, w, w);
        FAST_DEFS__VEC4_GETTER(z, x, x, x);
        FAST_DEFS__VEC4_GETTER(z, x, x, y);
        FAST_DEFS__VEC4_GETTER(z, x, x, z);
        FAST_DEFS__VEC4_GETTER(z, x, x, w);
        FAST_DEFS__VEC4_GETTER(z, x, y, x);
        FAST_DEFS__VEC4_GETTER(z, x, y, y);
        FAST_DEFS__VEC4_GETTER(z, x, y, z);
        FAST_DEFS__VEC4_GETTER(z, x, y, w);
        FAST_DEFS__VEC4_GETTER(z, x, z, x);
        FAST_DEFS__VEC4_GETTER(z, x, z, y);
        FAST_DEFS__VEC4_GETTER(z, x, z, z);
        FAST_DEFS__VEC4_GETTER(z, x, z, w);
        FAST_DEFS__VEC4_GETTER(z, x, w, x);
        FAST_DEFS__VEC4_GETTER(z, x, w, y);
        FAST_DEFS__VEC4_GETTER(z, x, w, z);
        FAST_DEFS__VEC4_GETTER(z, x, w, w);
        FAST_DEFS__VEC4_GETTER(z, y, x, x);
        FAST_DEFS__VEC4_GETTER(z, y, x, y);
        FAST_DEFS__VEC4_GETTER(z, y, x, z);
        FAST_DEFS__VEC4_GETTER(z, y, x, w);
        FAST_DEFS__VEC4_GETTER(z, y, y, x);
        FAST_DEFS__VEC4_GETTER(z, y, y, y);
        FAST_DEFS__VEC4_GETTER(z, y, y, z);
        FAST_DEFS__VEC4_GETTER(z, y, y, w);
        FAST_DEFS__VEC4_GETTER(z, y, z, x);
        FAST_DEFS__VEC4_GETTER(z, y, z, y);
        FAST_DEFS__VEC4_GETTER(z, y, z, z);
        FAST_DEFS__VEC4_GETTER(z, y, z, w);
        FAST_DEFS__VEC4_GETTER(z, y, w, x);
        FAST_DEFS__VEC4_GETTER(z, y, w, y);
        FAST_DEFS__VEC4_GETTER(z, y, w, z);
        FAST_DEFS__VEC4_GETTER(z, y, w, w);
        FAST_DEFS__VEC4_GETTER(z, z, x, x);
        FAST_DEFS__VEC4_GETTER(z, z, x, y);
        FAST_DEFS__VEC4_GETTER(z, z, x, z);
        FAST_DEFS__VEC4_GETTER(z, z, x, w);
        FAST_DEFS__VEC4_GETTER(z, z, y, x);
        FAST_DEFS__VEC4_GETTER(z, z, y, y);
        FAST_DEFS__VEC4_GETTER(z, z, y, z);
        FAST_DEFS__VEC4_GETTER(z, z, y, w);
        FAST_DEFS__VEC4_GETTER(z, z, z, x);
        FAST_DEFS__VEC4_GETTER(z, z, z, y);
        FAST_DEFS__VEC4_GETTER(z, z, z, z);
        FAST_DEFS__VEC4_GETTER(z, z, z, w);
        FAST_DEFS__VEC4_GETTER(z, z, w, x);
        FAST_DEFS__VEC4_GETTER(z, z, w, y);
        FAST_DEFS__VEC4_GETTER(z, z, w, z);
        FAST_DEFS__VEC4_GETTER(z, z, w, w);
        FAST_DEFS__VEC4_GETTER(z, w, x, x);
        FAST_DEFS__VEC4_GETTER(z, w, x, y);
        FAST_DEFS__VEC4_GETTER(z, w, x, z);
        FAST_DEFS__VEC4_GETTER(z, w, x, w);
        FAST_DEFS__VEC4_GETTER(z, w, y, x);
        FAST_DEFS__VEC4_GETTER(z, w, y, y);
        FAST_DEFS__VEC4_GETTER(z, w, y, z);
        FAST_DEFS__VEC4_GETTER(z, w, y, w);
        FAST_DEFS__VEC4_GETTER(z, w, z, x);
        FAST_DEFS__VEC4_GETTER(z, w, z, y);
        FAST_DEFS__VEC4_GETTER(z, w, z, z);
        FAST_DEFS__VEC4_GETTER(z, w, z, w);
        FAST_DEFS__VEC4_GETTER(z, w, w, x);
        FAST_DEFS__VEC4_GETTER(z, w, w, y);
        FAST_DEFS__VEC4_GETTER(z, w, w, z);
        FAST_DEFS__VEC4_GETTER(z, w, w, w);
        FAST_DEFS__VEC4_GETTER(w, x, x, x);
        FAST_DEFS__VEC4_GETTER(w, x, x, y);
        FAST_DEFS__VEC4_GETTER(w, x, x, z);
        FAST_DEFS__VEC4_GETTER(w, x, x, w);
        FAST_DEFS__VEC4_GETTER(w, x, y, x);
        FAST_DEFS__VEC4_GETTER(w, x, y, y);
        FAST_DEFS__VEC4_GETTER(w, x, y, z);
        FAST_DEFS__VEC4_GETTER(w, x, y, w);
        FAST_DEFS__VEC4_GETTER(w, x, z, x);
        FAST_DEFS__VEC4_GETTER(w, x, z, y);
        FAST_DEFS__VEC4_GETTER(w, x, z, z);
        FAST_DEFS__VEC4_GETTER(w, x, z, w);
        FAST_DEFS__VEC4_GETTER(w, x, w, x);
        FAST_DEFS__VEC4_GETTER(w, x, w, y);
        FAST_DEFS__VEC4_GETTER(w, x, w, z);
        FAST_DEFS__VEC4_GETTER(w, x, w, w);
        FAST_DEFS__VEC4_GETTER(w, y, x, x);
        FAST_DEFS__VEC4_GETTER(w, y, x, y);
        FAST_DEFS__VEC4_GETTER(w, y, x, z);
        FAST_DEFS__VEC4_GETTER(w, y, x, w);
        FAST_DEFS__VEC4_GETTER(w, y, y, x);
        FAST_DEFS__VEC4_GETTER(w, y, y, y);
        FAST_DEFS__VEC4_GETTER(w, y, y, z);
        FAST_DEFS__VEC4_GETTER(w, y, y, w);
        FAST_DEFS__VEC4_GETTER(w, y, z, x);
        FAST_DEFS__VEC4_GETTER(w, y, z, y);
        FAST_DEFS__VEC4_GETTER(w, y, z, z);
        FAST_DEFS__VEC4_GETTER(w, y, z, w);
        FAST_DEFS__VEC4_GETTER(w, y, w, x);
        FAST_DEFS__VEC4_GETTER(w, y, w, y);
        FAST_DEFS__VEC4_GETTER(w, y, w, z);
        FAST_DEFS__VEC4_GETTER(w, y, w, w);
        FAST_DEFS__VEC4_GETTER(w, z, x, x);
        FAST_DEFS__VEC4_GETTER(w, z, x, y);
        FAST_DEFS__VEC4_GETTER(w, z, x, z);
        FAST_DEFS__VEC4_GETTER(w, z, x, w);
        FAST_DEFS__VEC4_GETTER(w, z, y, x);
        FAST_DEFS__VEC4_GETTER(w, z, y, y);
        FAST_DEFS__VEC4_GETTER(w, z, y, z);
        FAST_DEFS__VEC4_GETTER(w, z, y, w);
        FAST_DEFS__VEC4_GETTER(w, z, z, x);
        FAST_DEFS__VEC4_GETTER(w, z, z, y);
        FAST_DEFS__VEC4_GETTER(w, z, z, z);
        FAST_DEFS__VEC4_GETTER(w, z, z, w);
        FAST_DEFS__VEC4_GETTER(w, z, w, x);
        FAST_DEFS__VEC4_GETTER(w, z, w, y);
        FAST_DEFS__VEC4_GETTER(w, z, w, z);
        FAST_DEFS__VEC4_GETTER(w, z, w, w);
        FAST_DEFS__VEC4_GETTER(w, w, x, x);
        FAST_DEFS__VEC4_GETTER(w, w, x, y);
        FAST_DEFS__VEC4_GETTER(w, w, x, z);
        FAST_DEFS__VEC4_GETTER(w, w, x, w);
        FAST_DEFS__VEC4_GETTER(w, w, y, x);
        FAST_DEFS__VEC4_GETTER(w, w, y, y);
        FAST_DEFS__VEC4_GETTER(w, w, y, z);
        FAST_DEFS__VEC4_GETTER(w, w, y, w);
        FAST_DEFS__VEC4_GETTER(w, w, z, x);
        FAST_DEFS__VEC4_GETTER(w, w, z, y);
        FAST_DEFS__VEC4_GETTER(w, w, z, z);
        FAST_DEFS__VEC4_GETTER(w, w, z, w);
        FAST_DEFS__VEC4_GETTER(w, w, w, x);
        FAST_DEFS__VEC4_GETTER(w, w, w, y);
        FAST_DEFS__VEC4_GETTER(w, w, w, z);
        FAST_DEFS__VEC4_GETTER(w, w, w, w);
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
    inline float length() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2)); }
    inline float dist_to(const vec4_t& vec) const { return vec4_t(*this - vec).length(); }
    inline constexpr float dot(const vec4_t& vec) const { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; }

    vec4_t<coord_t> normalized(this auto&& self) { return self / self.length(); }
    inline void normalize(this auto&& self) { self /= self.length(); }

public:
    FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, template <typename other_t>, vec4_t<other_t>() const, vec4_t<other_t>, (other_t), x, y, z, w);
    FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, , FAST_OPS_ARGS_PACK(std::tuple<coord_t, coord_t, coord_t, coord_t>)() const, std::make_tuple, , x, y, z, w);

    template <typename type_t> requires ntl::compatibility::data_type_convertertable<vec4_t<coord_t>, type_t>
    inline constexpr operator type_t() const { return ntl::compatibility::data_type_converter_t<vec4_t<coord_t>, type_t>::convert(*this); }

    template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.coordinates[i]; }

    FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(inline constexpr, x, y, z, w);
    FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(inline constexpr, x, y, z, w);

    FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const vec4_t<other_t>&, RHS_FIELD, x, y, z, w);
    FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, coord_t, RHS_VALUE, x, y, z, w);

    FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, template <typename other_t>, const vec4_t<other_t>&, RHS_FIELD, x, y, z, w);
    FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, , coord_t, RHS_VALUE, x, y, z, w);

    FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const vec4_t<other_t>&, RHS_FIELD, x, y, z, w);
    FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, template <typename self_t>, coord_t, RHS_VALUE, x, y, z, w);
};