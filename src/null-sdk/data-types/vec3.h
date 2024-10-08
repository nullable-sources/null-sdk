#pragma once
#include <cmath>
#include "vec2.h"

template <typename coord_t>
struct vec3_t;

namespace ntl::sdk {
#define NULLSDK_FAST_DEFS__VEC3_GETTER(_x, _y, _z) template <typename self_t> inline constexpr auto _x##_y##_z(this self_t&& self) { return vec3_t<coord_t>(self. _x, self. _y, self. _z); }

#define NULLSDK_FAST_DEFS__VEC3_SETTER(_x, _y, _z)                                                                                                                                                                \
    template <typename self_t> inline constexpr auto&& _x##_y##_z(this self_t&& self, coord_t rhs) { self. _x = self. _y = self. _z = rhs; return self; }                                                   \
    template <typename self_t> inline constexpr auto&& _x##_y##_z(this self_t&& self, coord_t x_rhs, coord_t y_rhs, coord_t z_rhs) { self. _x = x_rhs; self. _y = y_rhs; self. _z = z_rhs; return self; }   \
    template <typename self_t> inline constexpr auto&& _x##_y##_z(this self_t&& self, const vec3_t<coord_t>& rhs) { self ._x = rhs.x; self. _y = rhs.y; self. _z = rhs.z; return self; }                    \

    template <typename coord_t>
    struct vec3_getter_t {
    public:
        NULLSDK_FAST_DEFS__VEC2_SETTER(x, y);
        NULLSDK_FAST_DEFS__VEC2_SETTER(x, z);
        NULLSDK_FAST_DEFS__VEC2_SETTER(y, x);
        NULLSDK_FAST_DEFS__VEC2_SETTER(y, z);
        NULLSDK_FAST_DEFS__VEC2_SETTER(z, x);
        NULLSDK_FAST_DEFS__VEC2_SETTER(z, y);

        NULLSDK_FAST_DEFS__VEC3_SETTER(x, y, z);
        NULLSDK_FAST_DEFS__VEC3_SETTER(x, z, y);
        NULLSDK_FAST_DEFS__VEC3_SETTER(y, x, z);
        NULLSDK_FAST_DEFS__VEC3_SETTER(y, z, x);
        NULLSDK_FAST_DEFS__VEC3_SETTER(z, x, y);
        NULLSDK_FAST_DEFS__VEC3_SETTER(z, y, x);


        NULLSDK_FAST_DEFS__VEC2_GETTER(x, x);
        NULLSDK_FAST_DEFS__VEC2_GETTER(x, y);
        NULLSDK_FAST_DEFS__VEC2_GETTER(x, z);
        NULLSDK_FAST_DEFS__VEC2_GETTER(y, x);
        NULLSDK_FAST_DEFS__VEC2_GETTER(y, y);
        NULLSDK_FAST_DEFS__VEC2_GETTER(y, z);
        NULLSDK_FAST_DEFS__VEC2_GETTER(z, x);
        NULLSDK_FAST_DEFS__VEC2_GETTER(z, y);
        NULLSDK_FAST_DEFS__VEC2_GETTER(z, z);

        NULLSDK_FAST_DEFS__VEC3_GETTER(x, x, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, x, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, x, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, y, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, y, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, y, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, z, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, z, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(x, z, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, x, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, x, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, x, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, y, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, y, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, y, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, z, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, z, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(y, z, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, x, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, x, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, x, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, y, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, y, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, y, z);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, z, x);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, z, y);
        NULLSDK_FAST_DEFS__VEC3_GETTER(z, z, z);
    };
}

template <typename coord_t>
struct vec3_t : public ntl::sdk::vec3_getter_t<coord_t> {
public:
    static constexpr size_t array_size = 3; //@note: size array{ x, y, z }

public:
    union {
        struct { coord_t x, y, z; };
        std::array<coord_t, array_size> coordinates;
    };

public:
    inline constexpr vec3_t() { }

    inline constexpr vec3_t(coord_t value) : vec3_t(value, value, value) { }
    inline constexpr vec3_t(coord_t _x, coord_t _y, coord_t _z) : x(_x), y(_y), z(_z) { }

    inline constexpr vec3_t(const vec2_t<coord_t>& vec, coord_t _z = { }) : x(vec.x), y(vec.y), z(_z) { }

    inline vec3_t(const std::array<coord_t, array_size>& _coordinates) : coordinates(_coordinates) { }
    inline vec3_t(const std::vector<coord_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), std::min(_coordinates.size(), array_size)), coordinates.begin()); }
    inline vec3_t(const std::tuple<coord_t, coord_t, coord_t>& tuple) : coordinates(std::apply([](auto... n) { return std::array(n...); }, tuple)) { }
    inline vec3_t(const std::tuple<coord_t, coord_t>& tuple, coord_t _z = { }) : coordinates(std::apply([&](auto... n) { return std::array(n..., _z); }, tuple)) { }

    template <typename type_t> requires ntl::compatibility::data_type_convertertable<type_t, vec3_t<coord_t>>
    inline constexpr vec3_t(const type_t& value) : vec3_t(ntl::compatibility::data_type_converter_t<type_t, vec3_t<coord_t>>::convert(value)) { }

public:
    inline float length() const { return std::hypot(x, y, z); }
    inline float length_sqrt() const { return std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2); }
    inline float dist_to(const vec3_t<coord_t>& vec) const { return vec3_t(*this - vec).length(); }
    inline constexpr float dot(const vec3_t<coord_t>& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
    inline constexpr vec3_t<coord_t> cross(const vec3_t<coord_t>& vec) const { return { y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x }; }

    template <typename self_t> inline vec3_t<coord_t> normalized(this self_t&& self) { return self / self.length(); }
    template <typename self_t> inline void normalize(this self_t&& self) { self /= self.length(); }

    vec3_t<coord_t> project_to_norm(const vec3_t<float> dir) const { return dir * dot(dir); }
    vec3_t<coord_t> project_to(const vec3_t<float> dir) const { return project_to_norm(dir) / dir.length_sqrt(); }

public:
    NULLSDK_FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, template <typename other_t>, vec3_t<other_t>() const, vec3_t<other_t>, (other_t), x, y, z);
    NULLSDK_FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, , NULLSDK_FAST_OPS_ARGS_PACK(std::tuple<coord_t, coord_t, coord_t>)() const, std::make_tuple, , x, y, z);

    template <typename type_t> requires ntl::compatibility::data_type_convertertable<vec3_t<coord_t>, type_t>
    inline constexpr operator type_t() const { return ntl::compatibility::data_type_converter_t<vec3_t<coord_t>, type_t>::convert(*this); }

    template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.coordinates[i]; }

    NULLSDK_FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(inline constexpr, x, y, z);
    NULLSDK_FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(inline constexpr, x, y, z);

    NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, NULLSDK_FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const vec3_t<other_t>&, RHS_FIELD, x, y, z);
    NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, coord_t, RHS_VALUE, x, y, z);

    NULLSDK_FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, template <typename other_t>, const vec3_t<other_t>&, RHS_FIELD, x, y, z);
    NULLSDK_FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, , coord_t, RHS_VALUE, x, y, z);

    NULLSDK_FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, NULLSDK_FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const vec3_t<other_t>&, RHS_FIELD, x, y, z);
    NULLSDK_FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, template <typename self_t>, coord_t, RHS_VALUE, x, y, z);
};