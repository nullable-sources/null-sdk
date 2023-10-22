#pragma once
#include <cmath>
#include <array>
#include <vector>

#include "../utils/compatibility/data-type-converter.h"
#include "../utils/fast_operators.h"

template <typename coord_t>
struct vec2_t {
public:
	static constexpr size_t array_size = 2; //@note: size array{ x, y }

public:
	union {
		struct { coord_t x, y; };
		std::array<coord_t, array_size> coordinates{ };
	};

public:
	inline constexpr vec2_t() { }
	
	//@note:	In general, you can leave the old constructors, but vs does not work well with requires, which causes errors (which do not affect compilation),
	//		  so as soon as vs improves on requires, it will be possible to return the old constructors
	inline constexpr vec2_t(coord_t value) : vec2_t(value, value) { }
	inline constexpr vec2_t(coord_t _x, coord_t _y) : x(_x), y(_y) { }

	inline vec2_t(const std::array<coord_t, array_size>& _coordinates) : coordinates(_coordinates) { }
	inline vec2_t(const std::vector<coord_t>& _coordinates) { std::move(_coordinates.begin(), std::next(_coordinates.begin(), std::min(_coordinates.size(), array_size)), coordinates.begin()); }
	inline vec2_t(const std::tuple<coord_t, coord_t>& tuple) : coordinates(std::apply([](auto... n) { return std::array(n...); }, tuple)) { }

	template <typename type_t> requires null::compatibility::data_type_convertertable<type_t, vec2_t<coord_t>>
	inline constexpr vec2_t(const type_t& value) : vec2_t(null::compatibility::data_type_converter_t<type_t, vec2_t<coord_t>>::convert(value)) { }

public:
	inline float length() const { return std::hypot(x, y); }
	inline constexpr float dot(const vec2_t<coord_t>& vec) const { return x * vec.x + y * vec.y; }
	inline constexpr float cross(const vec2_t<coord_t>& vec) const { return x * vec.y - y * vec.x; }

	inline vec2_t<coord_t> direction(this auto&& self, const vec2_t<coord_t>& to) { return vec2_t<coord_t>(to - self).normalized(); }

	inline vec2_t<coord_t> normalized(this auto&& self) { return self / self.length(); }
	inline void normalize(this auto&& self) { self /= self.length(); }

public:	
	fast_ops_structure_convert_operator(inline constexpr, template <typename other_t>, vec2_t<other_t>() const, vec2_t<other_t>, (other_t), x, y);
	fast_ops_structure_convert_operator(inline constexpr, , fast_ops_args_pack(std::tuple<coord_t, coord_t>)() const, std::make_tuple, , x, y);

	template <typename type_t> requires null::compatibility::data_type_convertertable<vec2_t<coord_t>, type_t>
	inline constexpr operator type_t() const { return null::compatibility::data_type_converter_t<vec2_t<coord_t>, type_t>::convert(*this); }

	template <typename self_t> inline auto&& operator [](this self_t&& self, int i) { return self.coordinates[i]; }

	fast_ops_structure_all_prefix_operators(inline constexpr, x, y);
	fast_ops_structure_all_postfix_operators(inline constexpr, x, y);

	fast_ops_structure_all_arithmetic_operators(inline constexpr, fast_ops_args_pack(template <typename self_t, typename other_t>), const vec2_t<other_t>&, rhs_field, x, y);
	fast_ops_structure_all_arithmetic_operators(inline constexpr, template <typename self_t>, coord_t, rhs_value, x, y);

	fast_ops_structure_equal_operator(inline constexpr, template <typename other_t>, const vec2_t<other_t>&, rhs_field, x, y);
	fast_ops_structure_equal_operator(inline constexpr, , coord_t, rhs_value, x, y);

	fast_ops_structure_all_comparison_operators(inline constexpr, fast_ops_args_pack(template <typename self_t, typename other_t>), const vec2_t<other_t>&, rhs_field, x, y);
	fast_ops_structure_all_comparison_operators(inline constexpr, template <typename self_t>, coord_t, rhs_value, x, y);
};