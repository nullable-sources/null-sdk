#pragma once
#include <cmath>
#include <array>
#include <vector>

#include "../utils/compatibility/data-type-converter.h"
#include "../utils/fast-defines.h"
#include "../utils/fast-operators.h"

template <typename coord_t>
struct vec2_t;

namespace ntl::sdk {
#define FAST_DEFS__VEC2_GETTER(_x, _y) template <typename self_t> inline constexpr auto _x##_y(this self_t&& self) { return vec2_t<coord_t>(self. _x, self. _y); }

#define FAST_DEFS__VEC2_SETTER(_x, _y)                                                                                                                              \
    template <typename self_t> inline constexpr auto&& _x##_y(this self_t&& self, coord_t rhs) { self._x = self._y = rhs; return self; }                            \
    template <typename self_t> inline constexpr auto&& _x##_y(this self_t&& self, coord_t x_rhs, coord_t y_rhs) { self._x = x_rhs; self._y = y_rhs; return self; }  \
    template <typename self_t> inline constexpr auto&& _x##_y(this self_t&& self, const vec2_t<coord_t>& rhs) { self._x = rhs.x; self._y = rhs.y; return self; }    \

    template <typename coord_t>
    struct vec2_getter_t {
    public:
        FAST_DEFS__VEC2_SETTER(x, y);
        FAST_DEFS__VEC2_SETTER(y, x);

        FAST_DEFS__VEC2_GETTER(x, x);
        FAST_DEFS__VEC2_GETTER(x, y);
        FAST_DEFS__VEC2_GETTER(y, x);
        FAST_DEFS__VEC2_GETTER(y, y);
    };
}

template <typename coord_t>
struct vec2_t : public ntl::sdk::vec2_getter_t<coord_t> {
public:
    static constexpr size_t array_size = 2; //@note: size array{ x, y }

public:
    union {
        struct { coord_t x, y; };
        std::array<coord_t, array_size> coordinates{ };
    };

public:
    inline constexpr vec2_t() { }

    //@note: In general, you can leave the old constructors, but vs does not work well with requires, which causes errors (which do not affect compilation),
    //       so as soon as vs improves on requires, it will be possible to return the old constructors
    inline constexpr vec2_t(coord_t value) : vec2_t(value, value) { }
    inline constexpr vec2_t(coord_t _x, coord_t _y) : x(_x), y(_y) { }

    inline vec2_t(const std::array<coord_t, array_size>& _coordinates) : coordinates(_coordinates) { }
    inline vec2_t(const std::vector<coord_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), std::min(_coordinates.size(), array_size)), coordinates.begin()); }
    inline vec2_t(const std::tuple<coord_t, coord_t>& tuple) : coordinates(std::apply([](auto... n) { return std::array(n...); }, tuple)) { }

    template <typename type_t> requires ntl::compatibility::data_type_convertertable<type_t, vec2_t<coord_t>>
    inline constexpr vec2_t(const type_t& value) : vec2_t(ntl::compatibility::data_type_converter_t<type_t, vec2_t<coord_t>>::convert(value)) { }

public:
    inline float length() const { return std::hypot(x, y); }
    inline constexpr float dot(const vec2_t<coord_t>& vec) const { return x * vec.x + y * vec.y; }
    inline constexpr float cross(const vec2_t<coord_t>& vec) const { return x * vec.y - y * vec.x; }

    inline vec2_t<coord_t> direction(this auto&& self, const vec2_t<coord_t>& to) { return vec2_t<coord_t>(to - self).normalized(); }

    inline vec2_t<coord_t> normalized(this auto&& self) { return self / self.length(); }
    inline void normalize(this auto&& self) { self /= self.length(); }

public:
    FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, template <typename other_t>, vec2_t<other_t>() const, vec2_t<other_t>, (other_t), x, y);
    FAST_OPS_STRUCTURE_CONVERT_OPERATOR(inline constexpr, , FAST_OPS_ARGS_PACK(std::tuple<coord_t, coord_t>)() const, std::make_tuple, , x, y);

    template <typename type_t> requires ntl::compatibility::data_type_convertertable<vec2_t<coord_t>, type_t>
    inline constexpr operator type_t() const { return ntl::compatibility::data_type_converter_t<vec2_t<coord_t>, type_t>::convert(*this); }

    template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.coordinates[i]; }

    FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(inline constexpr, x, y);
    FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(inline constexpr, x, y);

    FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const vec2_t<other_t>&, RHS_FIELD, x, y);
    FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(inline constexpr, template <typename self_t>, coord_t, RHS_VALUE, x, y);

    FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, template <typename other_t>, const vec2_t<other_t>&, RHS_FIELD, x, y);
    FAST_OPS_STRUCTURE_EQUAL_OPERATOR(inline constexpr, , coord_t, RHS_VALUE, x, y);

    FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, FAST_OPS_ARGS_PACK(template <typename self_t, typename other_t>), const vec2_t<other_t>&, RHS_FIELD, x, y);
    FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(inline constexpr, template <typename self_t>, coord_t, RHS_VALUE, x, y);
};