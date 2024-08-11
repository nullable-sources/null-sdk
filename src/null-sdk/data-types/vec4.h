#pragma once
#include <cmath>
#include "vec3.h"
#include "../utils/fast-operators.h"

template <typename coord_t>
struct vec4_t;

namespace null::sdk {
#define __fast_defs__vec4_getter(_x, _y, _z, _w) template <typename self_t> inline constexpr auto _x##_y##_z##_w(this self_t&& self) { return vec4_t<coord_t>(self. _x, self. _y, self. _z, self. _w); }

#define __fast_defs__vec4_setter(_x, _y, _z, _w)                                                                                                                                                                                                \
    template <typename self_t> inline constexpr auto&& _x##_y##_z##_w(this self_t&& self, coord_t rhs) { self. _x = self. _y = self. _z = self. _w = rhs; return self; }                                                                        \
    template <typename self_t> inline constexpr auto&& _x##_y##_z##_w(this self_t&& self, coord_t x_rhs, coord_t y_rhs, coord_t z_rhs, coord_t w_rhs) { self. _x = x_rhs; self. _y = y_rhs; self. _z = z_rhs; self. _w = w_rhs; return self; }  \
    template <typename self_t> inline constexpr auto&& _x##_y##_z##_w(this self_t&& self, const vec4_t<coord_t>& rhs) { self ._x = rhs.x; self. _y = rhs.y; self. _z = rhs.z; self. _w = rhs.w; return self; }                                  \

    //@todo: either change the compiler (msvc is not able to compile the implementation via BOOST_PP_SEQ_FOR_EACH_PRODUCT), or wait for its support to appear (I doubt that this will happen)
    template <typename coord_t>
    struct vec4_getter_t {
    public:
        __fast_defs__vec2_setter(x, y);
        __fast_defs__vec2_setter(x, z);
        __fast_defs__vec2_setter(x, w);
        __fast_defs__vec2_setter(y, x);
        __fast_defs__vec2_setter(y, z);
        __fast_defs__vec2_setter(y, w);
        __fast_defs__vec2_setter(z, x);
        __fast_defs__vec2_setter(z, y);
        __fast_defs__vec2_setter(z, w);
        __fast_defs__vec2_setter(w, x);
        __fast_defs__vec2_setter(w, y);
        __fast_defs__vec2_setter(w, z);

        __fast_defs__vec3_setter(x, y, z);
        __fast_defs__vec3_setter(x, y, w);
        __fast_defs__vec3_setter(x, z, y);
        __fast_defs__vec3_setter(x, z, w);
        __fast_defs__vec3_setter(x, w, y);
        __fast_defs__vec3_setter(x, w, z);
        __fast_defs__vec3_setter(y, x, z);
        __fast_defs__vec3_setter(y, x, w);
        __fast_defs__vec3_setter(y, z, x);
        __fast_defs__vec3_setter(y, z, w);
        __fast_defs__vec3_setter(y, w, x);
        __fast_defs__vec3_setter(y, w, z);
        __fast_defs__vec3_setter(z, x, y);
        __fast_defs__vec3_setter(z, x, w);
        __fast_defs__vec3_setter(z, y, x);
        __fast_defs__vec3_setter(z, y, w);
        __fast_defs__vec3_setter(z, w, x);
        __fast_defs__vec3_setter(z, w, y);
        __fast_defs__vec3_setter(w, x, y);
        __fast_defs__vec3_setter(w, x, z);
        __fast_defs__vec3_setter(w, y, x);
        __fast_defs__vec3_setter(w, y, z);
        __fast_defs__vec3_setter(w, z, x);
        __fast_defs__vec3_setter(w, z, y);

        __fast_defs__vec4_setter(x, y, z, w);
        __fast_defs__vec4_setter(x, y, w, z);
        __fast_defs__vec4_setter(x, z, y, w);
        __fast_defs__vec4_setter(x, z, w, y);
        __fast_defs__vec4_setter(x, w, y, z);
        __fast_defs__vec4_setter(x, w, z, y);
        __fast_defs__vec4_setter(y, x, z, w);
        __fast_defs__vec4_setter(y, x, w, z);
        __fast_defs__vec4_setter(y, z, x, w);
        __fast_defs__vec4_setter(y, z, w, x);
        __fast_defs__vec4_setter(y, w, x, z);
        __fast_defs__vec4_setter(y, w, z, x);
        __fast_defs__vec4_setter(z, x, y, w);
        __fast_defs__vec4_setter(z, x, w, y);
        __fast_defs__vec4_setter(z, y, x, w);
        __fast_defs__vec4_setter(z, y, w, x);
        __fast_defs__vec4_setter(z, w, x, y);
        __fast_defs__vec4_setter(z, w, y, x);
        __fast_defs__vec4_setter(w, x, y, z);
        __fast_defs__vec4_setter(w, x, z, y);
        __fast_defs__vec4_setter(w, y, x, z);
        __fast_defs__vec4_setter(w, y, z, x);
        __fast_defs__vec4_setter(w, z, x, y);
        __fast_defs__vec4_setter(w, z, y, x);

        __fast_defs__vec2_getter(x, x);
        __fast_defs__vec2_getter(x, y);
        __fast_defs__vec2_getter(x, z);
        __fast_defs__vec2_getter(x, w);
        __fast_defs__vec2_getter(y, x);
        __fast_defs__vec2_getter(y, y);
        __fast_defs__vec2_getter(y, z);
        __fast_defs__vec2_getter(y, w);
        __fast_defs__vec2_getter(z, x);
        __fast_defs__vec2_getter(z, y);
        __fast_defs__vec2_getter(z, z);
        __fast_defs__vec2_getter(z, w);
        __fast_defs__vec2_getter(w, x);
        __fast_defs__vec2_getter(w, y);
        __fast_defs__vec2_getter(w, z);
        __fast_defs__vec2_getter(w, w);

        __fast_defs__vec3_getter(x, x, x);
        __fast_defs__vec3_getter(x, x, y);
        __fast_defs__vec3_getter(x, x, z);
        __fast_defs__vec3_getter(x, x, w);
        __fast_defs__vec3_getter(x, y, x);
        __fast_defs__vec3_getter(x, y, y);
        __fast_defs__vec3_getter(x, y, z);
        __fast_defs__vec3_getter(x, y, w);
        __fast_defs__vec3_getter(x, z, x);
        __fast_defs__vec3_getter(x, z, y);
        __fast_defs__vec3_getter(x, z, z);
        __fast_defs__vec3_getter(x, z, w);
        __fast_defs__vec3_getter(x, w, x);
        __fast_defs__vec3_getter(x, w, y);
        __fast_defs__vec3_getter(x, w, z);
        __fast_defs__vec3_getter(x, w, w);
        __fast_defs__vec3_getter(y, x, x);
        __fast_defs__vec3_getter(y, x, y);
        __fast_defs__vec3_getter(y, x, z);
        __fast_defs__vec3_getter(y, x, w);
        __fast_defs__vec3_getter(y, y, x);
        __fast_defs__vec3_getter(y, y, y);
        __fast_defs__vec3_getter(y, y, z);
        __fast_defs__vec3_getter(y, y, w);
        __fast_defs__vec3_getter(y, z, x);
        __fast_defs__vec3_getter(y, z, y);
        __fast_defs__vec3_getter(y, z, z);
        __fast_defs__vec3_getter(y, z, w);
        __fast_defs__vec3_getter(y, w, x);
        __fast_defs__vec3_getter(y, w, y);
        __fast_defs__vec3_getter(y, w, z);
        __fast_defs__vec3_getter(y, w, w);
        __fast_defs__vec3_getter(z, x, x);
        __fast_defs__vec3_getter(z, x, y);
        __fast_defs__vec3_getter(z, x, z);
        __fast_defs__vec3_getter(z, x, w);
        __fast_defs__vec3_getter(z, y, x);
        __fast_defs__vec3_getter(z, y, y);
        __fast_defs__vec3_getter(z, y, z);
        __fast_defs__vec3_getter(z, y, w);
        __fast_defs__vec3_getter(z, z, x);
        __fast_defs__vec3_getter(z, z, y);
        __fast_defs__vec3_getter(z, z, z);
        __fast_defs__vec3_getter(z, z, w);
        __fast_defs__vec3_getter(z, w, x);
        __fast_defs__vec3_getter(z, w, y);
        __fast_defs__vec3_getter(z, w, z);
        __fast_defs__vec3_getter(z, w, w);
        __fast_defs__vec3_getter(w, x, x);
        __fast_defs__vec3_getter(w, x, y);
        __fast_defs__vec3_getter(w, x, z);
        __fast_defs__vec3_getter(w, x, w);
        __fast_defs__vec3_getter(w, y, x);
        __fast_defs__vec3_getter(w, y, y);
        __fast_defs__vec3_getter(w, y, z);
        __fast_defs__vec3_getter(w, y, w);
        __fast_defs__vec3_getter(w, z, x);
        __fast_defs__vec3_getter(w, z, y);
        __fast_defs__vec3_getter(w, z, z);
        __fast_defs__vec3_getter(w, z, w);
        __fast_defs__vec3_getter(w, w, x);
        __fast_defs__vec3_getter(w, w, y);
        __fast_defs__vec3_getter(w, w, z);
        __fast_defs__vec3_getter(w, w, w);

        __fast_defs__vec4_getter(x, x, x, x);
        __fast_defs__vec4_getter(x, x, x, y);
        __fast_defs__vec4_getter(x, x, x, z);
        __fast_defs__vec4_getter(x, x, x, w);
        __fast_defs__vec4_getter(x, x, y, x);
        __fast_defs__vec4_getter(x, x, y, y);
        __fast_defs__vec4_getter(x, x, y, z);
        __fast_defs__vec4_getter(x, x, y, w);
        __fast_defs__vec4_getter(x, x, z, x);
        __fast_defs__vec4_getter(x, x, z, y);
        __fast_defs__vec4_getter(x, x, z, z);
        __fast_defs__vec4_getter(x, x, z, w);
        __fast_defs__vec4_getter(x, x, w, x);
        __fast_defs__vec4_getter(x, x, w, y);
        __fast_defs__vec4_getter(x, x, w, z);
        __fast_defs__vec4_getter(x, x, w, w);
        __fast_defs__vec4_getter(x, y, x, x);
        __fast_defs__vec4_getter(x, y, x, y);
        __fast_defs__vec4_getter(x, y, x, z);
        __fast_defs__vec4_getter(x, y, x, w);
        __fast_defs__vec4_getter(x, y, y, x);
        __fast_defs__vec4_getter(x, y, y, y);
        __fast_defs__vec4_getter(x, y, y, z);
        __fast_defs__vec4_getter(x, y, y, w);
        __fast_defs__vec4_getter(x, y, z, x);
        __fast_defs__vec4_getter(x, y, z, y);
        __fast_defs__vec4_getter(x, y, z, z);
        __fast_defs__vec4_getter(x, y, z, w);
        __fast_defs__vec4_getter(x, y, w, x);
        __fast_defs__vec4_getter(x, y, w, y);
        __fast_defs__vec4_getter(x, y, w, z);
        __fast_defs__vec4_getter(x, y, w, w);
        __fast_defs__vec4_getter(x, z, x, x);
        __fast_defs__vec4_getter(x, z, x, y);
        __fast_defs__vec4_getter(x, z, x, z);
        __fast_defs__vec4_getter(x, z, x, w);
        __fast_defs__vec4_getter(x, z, y, x);
        __fast_defs__vec4_getter(x, z, y, y);
        __fast_defs__vec4_getter(x, z, y, z);
        __fast_defs__vec4_getter(x, z, y, w);
        __fast_defs__vec4_getter(x, z, z, x);
        __fast_defs__vec4_getter(x, z, z, y);
        __fast_defs__vec4_getter(x, z, z, z);
        __fast_defs__vec4_getter(x, z, z, w);
        __fast_defs__vec4_getter(x, z, w, x);
        __fast_defs__vec4_getter(x, z, w, y);
        __fast_defs__vec4_getter(x, z, w, z);
        __fast_defs__vec4_getter(x, z, w, w);
        __fast_defs__vec4_getter(x, w, x, x);
        __fast_defs__vec4_getter(x, w, x, y);
        __fast_defs__vec4_getter(x, w, x, z);
        __fast_defs__vec4_getter(x, w, x, w);
        __fast_defs__vec4_getter(x, w, y, x);
        __fast_defs__vec4_getter(x, w, y, y);
        __fast_defs__vec4_getter(x, w, y, z);
        __fast_defs__vec4_getter(x, w, y, w);
        __fast_defs__vec4_getter(x, w, z, x);
        __fast_defs__vec4_getter(x, w, z, y);
        __fast_defs__vec4_getter(x, w, z, z);
        __fast_defs__vec4_getter(x, w, z, w);
        __fast_defs__vec4_getter(x, w, w, x);
        __fast_defs__vec4_getter(x, w, w, y);
        __fast_defs__vec4_getter(x, w, w, z);
        __fast_defs__vec4_getter(x, w, w, w);
        __fast_defs__vec4_getter(y, x, x, x);
        __fast_defs__vec4_getter(y, x, x, y);
        __fast_defs__vec4_getter(y, x, x, z);
        __fast_defs__vec4_getter(y, x, x, w);
        __fast_defs__vec4_getter(y, x, y, x);
        __fast_defs__vec4_getter(y, x, y, y);
        __fast_defs__vec4_getter(y, x, y, z);
        __fast_defs__vec4_getter(y, x, y, w);
        __fast_defs__vec4_getter(y, x, z, x);
        __fast_defs__vec4_getter(y, x, z, y);
        __fast_defs__vec4_getter(y, x, z, z);
        __fast_defs__vec4_getter(y, x, z, w);
        __fast_defs__vec4_getter(y, x, w, x);
        __fast_defs__vec4_getter(y, x, w, y);
        __fast_defs__vec4_getter(y, x, w, z);
        __fast_defs__vec4_getter(y, x, w, w);
        __fast_defs__vec4_getter(y, y, x, x);
        __fast_defs__vec4_getter(y, y, x, y);
        __fast_defs__vec4_getter(y, y, x, z);
        __fast_defs__vec4_getter(y, y, x, w);
        __fast_defs__vec4_getter(y, y, y, x);
        __fast_defs__vec4_getter(y, y, y, y);
        __fast_defs__vec4_getter(y, y, y, z);
        __fast_defs__vec4_getter(y, y, y, w);
        __fast_defs__vec4_getter(y, y, z, x);
        __fast_defs__vec4_getter(y, y, z, y);
        __fast_defs__vec4_getter(y, y, z, z);
        __fast_defs__vec4_getter(y, y, z, w);
        __fast_defs__vec4_getter(y, y, w, x);
        __fast_defs__vec4_getter(y, y, w, y);
        __fast_defs__vec4_getter(y, y, w, z);
        __fast_defs__vec4_getter(y, y, w, w);
        __fast_defs__vec4_getter(y, z, x, x);
        __fast_defs__vec4_getter(y, z, x, y);
        __fast_defs__vec4_getter(y, z, x, z);
        __fast_defs__vec4_getter(y, z, x, w);
        __fast_defs__vec4_getter(y, z, y, x);
        __fast_defs__vec4_getter(y, z, y, y);
        __fast_defs__vec4_getter(y, z, y, z);
        __fast_defs__vec4_getter(y, z, y, w);
        __fast_defs__vec4_getter(y, z, z, x);
        __fast_defs__vec4_getter(y, z, z, y);
        __fast_defs__vec4_getter(y, z, z, z);
        __fast_defs__vec4_getter(y, z, z, w);
        __fast_defs__vec4_getter(y, z, w, x);
        __fast_defs__vec4_getter(y, z, w, y);
        __fast_defs__vec4_getter(y, z, w, z);
        __fast_defs__vec4_getter(y, z, w, w);
        __fast_defs__vec4_getter(y, w, x, x);
        __fast_defs__vec4_getter(y, w, x, y);
        __fast_defs__vec4_getter(y, w, x, z);
        __fast_defs__vec4_getter(y, w, x, w);
        __fast_defs__vec4_getter(y, w, y, x);
        __fast_defs__vec4_getter(y, w, y, y);
        __fast_defs__vec4_getter(y, w, y, z);
        __fast_defs__vec4_getter(y, w, y, w);
        __fast_defs__vec4_getter(y, w, z, x);
        __fast_defs__vec4_getter(y, w, z, y);
        __fast_defs__vec4_getter(y, w, z, z);
        __fast_defs__vec4_getter(y, w, z, w);
        __fast_defs__vec4_getter(y, w, w, x);
        __fast_defs__vec4_getter(y, w, w, y);
        __fast_defs__vec4_getter(y, w, w, z);
        __fast_defs__vec4_getter(y, w, w, w);
        __fast_defs__vec4_getter(z, x, x, x);
        __fast_defs__vec4_getter(z, x, x, y);
        __fast_defs__vec4_getter(z, x, x, z);
        __fast_defs__vec4_getter(z, x, x, w);
        __fast_defs__vec4_getter(z, x, y, x);
        __fast_defs__vec4_getter(z, x, y, y);
        __fast_defs__vec4_getter(z, x, y, z);
        __fast_defs__vec4_getter(z, x, y, w);
        __fast_defs__vec4_getter(z, x, z, x);
        __fast_defs__vec4_getter(z, x, z, y);
        __fast_defs__vec4_getter(z, x, z, z);
        __fast_defs__vec4_getter(z, x, z, w);
        __fast_defs__vec4_getter(z, x, w, x);
        __fast_defs__vec4_getter(z, x, w, y);
        __fast_defs__vec4_getter(z, x, w, z);
        __fast_defs__vec4_getter(z, x, w, w);
        __fast_defs__vec4_getter(z, y, x, x);
        __fast_defs__vec4_getter(z, y, x, y);
        __fast_defs__vec4_getter(z, y, x, z);
        __fast_defs__vec4_getter(z, y, x, w);
        __fast_defs__vec4_getter(z, y, y, x);
        __fast_defs__vec4_getter(z, y, y, y);
        __fast_defs__vec4_getter(z, y, y, z);
        __fast_defs__vec4_getter(z, y, y, w);
        __fast_defs__vec4_getter(z, y, z, x);
        __fast_defs__vec4_getter(z, y, z, y);
        __fast_defs__vec4_getter(z, y, z, z);
        __fast_defs__vec4_getter(z, y, z, w);
        __fast_defs__vec4_getter(z, y, w, x);
        __fast_defs__vec4_getter(z, y, w, y);
        __fast_defs__vec4_getter(z, y, w, z);
        __fast_defs__vec4_getter(z, y, w, w);
        __fast_defs__vec4_getter(z, z, x, x);
        __fast_defs__vec4_getter(z, z, x, y);
        __fast_defs__vec4_getter(z, z, x, z);
        __fast_defs__vec4_getter(z, z, x, w);
        __fast_defs__vec4_getter(z, z, y, x);
        __fast_defs__vec4_getter(z, z, y, y);
        __fast_defs__vec4_getter(z, z, y, z);
        __fast_defs__vec4_getter(z, z, y, w);
        __fast_defs__vec4_getter(z, z, z, x);
        __fast_defs__vec4_getter(z, z, z, y);
        __fast_defs__vec4_getter(z, z, z, z);
        __fast_defs__vec4_getter(z, z, z, w);
        __fast_defs__vec4_getter(z, z, w, x);
        __fast_defs__vec4_getter(z, z, w, y);
        __fast_defs__vec4_getter(z, z, w, z);
        __fast_defs__vec4_getter(z, z, w, w);
        __fast_defs__vec4_getter(z, w, x, x);
        __fast_defs__vec4_getter(z, w, x, y);
        __fast_defs__vec4_getter(z, w, x, z);
        __fast_defs__vec4_getter(z, w, x, w);
        __fast_defs__vec4_getter(z, w, y, x);
        __fast_defs__vec4_getter(z, w, y, y);
        __fast_defs__vec4_getter(z, w, y, z);
        __fast_defs__vec4_getter(z, w, y, w);
        __fast_defs__vec4_getter(z, w, z, x);
        __fast_defs__vec4_getter(z, w, z, y);
        __fast_defs__vec4_getter(z, w, z, z);
        __fast_defs__vec4_getter(z, w, z, w);
        __fast_defs__vec4_getter(z, w, w, x);
        __fast_defs__vec4_getter(z, w, w, y);
        __fast_defs__vec4_getter(z, w, w, z);
        __fast_defs__vec4_getter(z, w, w, w);
        __fast_defs__vec4_getter(w, x, x, x);
        __fast_defs__vec4_getter(w, x, x, y);
        __fast_defs__vec4_getter(w, x, x, z);
        __fast_defs__vec4_getter(w, x, x, w);
        __fast_defs__vec4_getter(w, x, y, x);
        __fast_defs__vec4_getter(w, x, y, y);
        __fast_defs__vec4_getter(w, x, y, z);
        __fast_defs__vec4_getter(w, x, y, w);
        __fast_defs__vec4_getter(w, x, z, x);
        __fast_defs__vec4_getter(w, x, z, y);
        __fast_defs__vec4_getter(w, x, z, z);
        __fast_defs__vec4_getter(w, x, z, w);
        __fast_defs__vec4_getter(w, x, w, x);
        __fast_defs__vec4_getter(w, x, w, y);
        __fast_defs__vec4_getter(w, x, w, z);
        __fast_defs__vec4_getter(w, x, w, w);
        __fast_defs__vec4_getter(w, y, x, x);
        __fast_defs__vec4_getter(w, y, x, y);
        __fast_defs__vec4_getter(w, y, x, z);
        __fast_defs__vec4_getter(w, y, x, w);
        __fast_defs__vec4_getter(w, y, y, x);
        __fast_defs__vec4_getter(w, y, y, y);
        __fast_defs__vec4_getter(w, y, y, z);
        __fast_defs__vec4_getter(w, y, y, w);
        __fast_defs__vec4_getter(w, y, z, x);
        __fast_defs__vec4_getter(w, y, z, y);
        __fast_defs__vec4_getter(w, y, z, z);
        __fast_defs__vec4_getter(w, y, z, w);
        __fast_defs__vec4_getter(w, y, w, x);
        __fast_defs__vec4_getter(w, y, w, y);
        __fast_defs__vec4_getter(w, y, w, z);
        __fast_defs__vec4_getter(w, y, w, w);
        __fast_defs__vec4_getter(w, z, x, x);
        __fast_defs__vec4_getter(w, z, x, y);
        __fast_defs__vec4_getter(w, z, x, z);
        __fast_defs__vec4_getter(w, z, x, w);
        __fast_defs__vec4_getter(w, z, y, x);
        __fast_defs__vec4_getter(w, z, y, y);
        __fast_defs__vec4_getter(w, z, y, z);
        __fast_defs__vec4_getter(w, z, y, w);
        __fast_defs__vec4_getter(w, z, z, x);
        __fast_defs__vec4_getter(w, z, z, y);
        __fast_defs__vec4_getter(w, z, z, z);
        __fast_defs__vec4_getter(w, z, z, w);
        __fast_defs__vec4_getter(w, z, w, x);
        __fast_defs__vec4_getter(w, z, w, y);
        __fast_defs__vec4_getter(w, z, w, z);
        __fast_defs__vec4_getter(w, z, w, w);
        __fast_defs__vec4_getter(w, w, x, x);
        __fast_defs__vec4_getter(w, w, x, y);
        __fast_defs__vec4_getter(w, w, x, z);
        __fast_defs__vec4_getter(w, w, x, w);
        __fast_defs__vec4_getter(w, w, y, x);
        __fast_defs__vec4_getter(w, w, y, y);
        __fast_defs__vec4_getter(w, w, y, z);
        __fast_defs__vec4_getter(w, w, y, w);
        __fast_defs__vec4_getter(w, w, z, x);
        __fast_defs__vec4_getter(w, w, z, y);
        __fast_defs__vec4_getter(w, w, z, z);
        __fast_defs__vec4_getter(w, w, z, w);
        __fast_defs__vec4_getter(w, w, w, x);
        __fast_defs__vec4_getter(w, w, w, y);
        __fast_defs__vec4_getter(w, w, w, z);
        __fast_defs__vec4_getter(w, w, w, w);
    };
}

template <typename coord_t>
struct vec4_t : public null::sdk::vec4_getter_t<coord_t> {
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

    template <typename type_t> requires null::compatibility::data_type_convertertable<type_t, vec4_t<coord_t>>
    inline constexpr vec4_t(const type_t& value) : vec4_t(null::compatibility::data_type_converter_t<type_t, vec4_t<coord_t>>::convert(value)) { }

public:
    inline float length() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2)); }
    inline float dist_to(const vec4_t& vec) const { return vec4_t(*this - vec).length(); }
    inline constexpr float dot(const vec4_t& vec) const { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; }

    vec4_t<coord_t> normalized(this auto&& self) { return self / self.length(); }
    inline void normalize(this auto&& self) { self /= self.length(); }

public:
    fast_ops_structure_convert_operator(inline constexpr, template <typename other_t>, vec4_t<other_t>() const, vec4_t<other_t>, (other_t), x, y, z, w);
    fast_ops_structure_convert_operator(inline constexpr, , fast_ops_args_pack(std::tuple<coord_t, coord_t, coord_t, coord_t>)() const, std::make_tuple, , x, y, z, w);

    template <typename type_t> requires null::compatibility::data_type_convertertable<vec4_t<coord_t>, type_t>
    inline constexpr operator type_t() const { return null::compatibility::data_type_converter_t<vec4_t<coord_t>, type_t>::convert(*this); }

    template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.coordinates[i]; }

    fast_ops_structure_all_prefix_operators(inline constexpr, x, y, z, w);
    fast_ops_structure_all_postfix_operators(inline constexpr, x, y, z, w);

    fast_ops_structure_all_arithmetic_operators(inline constexpr, fast_ops_args_pack(template <typename self_t, typename other_t>), const vec4_t<other_t>&, rhs_field, x, y, z, w);
    fast_ops_structure_all_arithmetic_operators(inline constexpr, template <typename self_t>, coord_t, rhs_value, x, y, z, w);

    fast_ops_structure_equal_operator(inline constexpr, template <typename other_t>, const vec4_t<other_t>&, rhs_field, x, y, z, w);
    fast_ops_structure_equal_operator(inline constexpr, , coord_t, rhs_value, x, y, z, w);

    fast_ops_structure_all_comparison_operators(inline constexpr, fast_ops_args_pack(template <typename self_t, typename other_t>), const vec4_t<other_t>&, rhs_field, x, y, z, w);
    fast_ops_structure_all_comparison_operators(inline constexpr, template <typename self_t>, coord_t, rhs_value, x, y, z, w);
};