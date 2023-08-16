#pragma once
#include <cmath>
#include "data-types/vec3.h"
#include "utils/fast_operators.h"

template <typename coord_t>
struct vec4_t {
public:
	static constexpr size_t array_size{ 4 }; //@note: size array{ x, y, z, w }

public:
	union {
		struct { coord_t x, y, z, w; };
		std::array<coord_t, array_size> coordinates{ };
	};

public:
	vec4_t() { }

	vec4_t(coord_t value) : vec4_t{ value, value, value, value } { }
	vec4_t(coord_t _x, coord_t _y, coord_t _z, coord_t _w) : x{ _x }, y{ _y }, z{ _z }, w{ _w } { }
	
	vec4_t(const vec3_t<coord_t>& vec, coord_t _w = { }) : x{ vec.x }, y{ vec.y }, z{ vec.z }, w{ _w } { }
	vec4_t(const vec2_t<coord_t>& vec, coord_t _z = { }, coord_t _w = { }) : x{ vec.x }, y{ vec.y }, z{ _z }, w{ _w } { }

	vec4_t(const std::array<coord_t, array_size>& _coordinates) : coordinates{ _coordinates } { }
	vec4_t(const std::vector<coord_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), array_size), coordinates.begin()); }
	vec4_t(const std::tuple<coord_t, coord_t, coord_t, coord_t>& tuple) : coordinates{ std::apply([](auto... n) { return std::array{ n... }; }, tuple) } { }
	vec4_t(const std::tuple<coord_t, coord_t, coord_t>& tuple, coord_t _w = { }) : coordinates{ std::apply([&](auto... n) { return std::array{ n..., _w }; }, tuple) } { }
	vec4_t(const std::tuple<coord_t, coord_t>& tuple, coord_t _z = { }, coord_t _w = { }) : coordinates{ std::apply([&](auto... n) { return std::array{ n..., _z, _w }; }, tuple) } { }
	
	template <typename type_t> requires null::compatibility::data_type_convertertable<type_t, vec4_t<coord_t>>
	vec4_t(const type_t& value) : vec4_t{ null::compatibility::data_type_converter_t<type_t, vec4_t<coord_t>>::convert(value) } { } 

public:
	float length() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2)); }
	float dist_to(const vec4_t& vec) const { return vec4_t{ *this - vec }.length(); }
	float dot(const vec4_t& vec) const { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; }

	vec4_t<coord_t> normalized(this auto&& self) { return self / self.length(); }
	void normalize(this auto&& self) { self /= self.length(); }

public:
	template <typename self_t> auto xy(this self_t&& self) { return vec2_t<coord_t>{ self.x, self.y }; }
	template <typename self_t> auto xyz(this self_t&& self) { return vec3_t<coord_t>{ self.x, self.y, self.z }; }

public:
	fast_ops_structure_convert_operator(template <typename other_t>, vec4_t<other_t>() const, vec4_t<other_t>, (other_t), x, y, z, w);
	fast_ops_structure_convert_operator(, fast_ops_args_pack(std::tuple<coord_t, coord_t, coord_t, coord_t>)() const, std::make_tuple, , x, y, z, w);

	template <typename type_t> requires null::compatibility::data_type_convertertable<vec4_t<coord_t>, type_t>
	operator type_t() const { return null::compatibility::data_type_converter_t<vec4_t<coord_t>, type_t>::convert(*this); }

	template <typename self_t> auto&& operator [](this self_t&& self, int i) { return self.coordinates[i]; }

	fast_ops_structure_all_prefix_operators(x, y, z, w);
	fast_ops_structure_all_postfix_operators(x, y, z, w);

	fast_ops_structure_all_arithmetic_operators(fast_ops_args_pack(template <typename self_t, typename other_t>), const vec4_t<other_t>&, rhs_field, x, y, z, w);
	fast_ops_structure_all_arithmetic_operators(template <typename self_t>, coord_t, rhs_value, x, y, z, w);

	fast_ops_structure_equal_operator(template <typename other_t>, const vec4_t<other_t>&, rhs_field, x, y, z, w);
	fast_ops_structure_equal_operator(, coord_t, rhs_value, x, y, z, w);

	fast_ops_structure_all_comparison_operators(fast_ops_args_pack(template <typename self_t, typename other_t>), const vec4_t<other_t>&, rhs_field, x, y, z, w);
	fast_ops_structure_all_comparison_operators(template <typename self_t>, coord_t, rhs_value, x, y, z, w);
};