#pragma once
#include <concepts>

namespace null::compatibility {
	template <typename from_t, typename to_t>
	struct data_type_converter_t {
		static inline auto convert(const from_t& from);
	};

	template <typename from_t, typename to_t>
	concept data_type_convertertable = requires(from_t from) {
		{ data_type_converter_t<from_t, to_t>::convert(from) } -> std::same_as<to_t>;
	};
}