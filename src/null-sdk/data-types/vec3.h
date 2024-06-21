#pragma once
#include <cmath>
#include "vec2.h"
#include "../utils/fast_operators.h"

template <typename coord_t>
struct vec3_t {
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

    template <typename type_t> requires null::compatibility::data_type_convertertable<type_t, vec3_t<coord_t>>
    inline constexpr vec3_t(const type_t& value) : vec3_t(null::compatibility::data_type_converter_t<type_t, vec3_t<coord_t>>::convert(value)) { }

public:
    inline float length() const { return std::hypot(x, y, z); }
    inline float dist_to(const vec3_t<coord_t>& vec) const { return vec3_t(*this - vec).length(); }
    inline constexpr float dot(const vec3_t<coord_t>& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
    inline constexpr vec3_t<coord_t> cross(const vec3_t<coord_t>& vec) const { return { y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x }; }

    template <typename self_t> inline vec3_t<coord_t> normalized(this self_t&& self) { return self / self.length(); }
    template <typename self_t> inline void normalize(this self_t&& self) { self /= self.length(); }

public:
    template <typename self_t> inline constexpr auto xy(this self_t&& self) { return vec2_t<coord_t>(self.x, self.y); }

public:
    fast_ops_structure_convert_operator(inline constexpr, template <typename other_t>, vec3_t<other_t>() const, vec3_t<other_t>, (other_t), x, y, z);
    fast_ops_structure_convert_operator(inline constexpr, , fast_ops_args_pack(std::tuple<coord_t, coord_t, coord_t>)() const, std::make_tuple, , x, y, z);

    template <typename type_t> requires null::compatibility::data_type_convertertable<vec3_t<coord_t>, type_t>
    inline constexpr operator type_t() const { return null::compatibility::data_type_converter_t<vec3_t<coord_t>, type_t>::convert(*this); }

    template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.coordinates[i]; }

    fast_ops_structure_all_prefix_operators(inline constexpr, x, y, z);
    fast_ops_structure_all_postfix_operators(inline constexpr, x, y, z);

    fast_ops_structure_all_arithmetic_operators(inline constexpr, fast_ops_args_pack(template <typename self_t, typename other_t>), const vec3_t<other_t>&, rhs_field, x, y, z);
    fast_ops_structure_all_arithmetic_operators(inline constexpr, template <typename self_t>, coord_t, rhs_value, x, y, z);

    fast_ops_structure_equal_operator(inline constexpr, template <typename other_t>, const vec3_t<other_t>&, rhs_field, x, y, z);
    fast_ops_structure_equal_operator(inline constexpr, , coord_t, rhs_value, x, y, z);

    fast_ops_structure_all_comparison_operators(inline constexpr, fast_ops_args_pack(template <typename self_t, typename other_t>), const vec3_t<other_t>&, rhs_field, x, y, z);
    fast_ops_structure_all_comparison_operators(inline constexpr, template <typename self_t>, coord_t, rhs_value, x, y, z);
};