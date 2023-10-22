#pragma once
#include <type_traits>

#define impl_fast_ops_body_variant_this_rhs_field(op, field) field op rhs.field
#define impl_fast_ops_body_variant_self_rhs_field(op, field) self.field op rhs.field

#define impl_fast_ops_body_variant_this_rhs_value(op, field) field op rhs
#define impl_fast_ops_body_variant_self_rhs_value(op, field) impl_fast_ops_body_variant_this_rhs_value(op, self.field)

#define impl_fast_ops_body_variant_this_postfix(op, field) field##op
#define impl_fast_ops_body_variant_self_postfix(op, field) impl_fast_ops_body_variant_this_postfix(op, self.field)

#define impl_fast_ops_body_variant_this_prefix(op, field) op##field
#define impl_fast_ops_body_variant_self_prefix(op, field) impl_fast_ops_body_variant_this_prefix(op, self.field)


#define impl_fast_ops_arg(arg) arg

#define impl_fast_ops_get_comma(op, variant, _1, _2, _3, _4, name, ...) name
#define impl_fast_ops_get_delimiter(op, variant, delimiter_literal, _1, _2, _3, _4, name, ...) name
#define fast_ops_make_body(type /*delimiter or comma*/, ...)																							\
	impl_fast_ops_arg(																																	\
		impl_fast_ops_get_##type(																														\
			__VA_ARGS__, impl_fast_ops_##type##_4, impl_fast_ops_##type##_3, impl_fast_ops_##type##_2, impl_fast_ops_##type##_1, impl_fast_ops_##type##	\
		)(__VA_ARGS__)																																	\
	)																																					\

#define impl_fast_ops_delimiter_1(op, variant, delimiter_literal, field)			impl_fast_ops_body_variant_##variant(op, field)
#define impl_fast_ops_delimiter_2(op, variant, delimiter_literal, _1, _2)			impl_fast_ops_delimiter_1(op, variant, , _1)							delimiter_literal impl_fast_ops_delimiter_1(op, variant, , _2)
#define impl_fast_ops_delimiter_3(op, variant, delimiter_literal, _1, _2, _3)		impl_fast_ops_delimiter_2(op, variant, delimiter_literal, _1, _2)		delimiter_literal impl_fast_ops_delimiter_1(op, variant, , _3)
#define impl_fast_ops_delimiter_4(op, variant, delimiter_literal, _1, _2, _3, _4)	impl_fast_ops_delimiter_3(op, variant, delimiter_literal, _1, _2, _3)	delimiter_literal impl_fast_ops_delimiter_1(op, variant, , _4)

#define impl_fast_ops_comma_1(op, variant, field)			impl_fast_ops_body_variant_##variant(op, field)
#define impl_fast_ops_comma_2(op, variant, _1, _2)			impl_fast_ops_comma_1(op, variant, _1)			, impl_fast_ops_comma_1(op, variant, _2)
#define impl_fast_ops_comma_3(op, variant, _1, _2, _3)		impl_fast_ops_comma_2(op, variant, _1, _2)		, impl_fast_ops_comma_1(op, variant, _3)
#define impl_fast_ops_comma_4(op, variant, _1, _2, _3, _4)	impl_fast_ops_comma_3(op, variant, _1, _2, _3)	, impl_fast_ops_comma_1(op, variant, _4)


//@note: global fast_ops defines
#define fast_ops_args_pack(...) __VA_ARGS__

#define impl_fast_ops_ref_op_fn(op, body_variant, ...) { fast_ops_make_body(delimiter, op, self_##body_variant, ;, __VA_ARGS__); return self; }
#define impl_fast_ops_new_op_fn(op, body_variant, ...) { return std::decay_t<self_t>(fast_ops_make_body(comma, op, self_##body_variant, __VA_ARGS__)); }
#define impl_fast_ops_logical_op_fn(op, body_variant, ...) { return fast_ops_make_body(delimiter, op, body_variant, &&, __VA_ARGS__); }
#define impl_fast_ops_arithmetic_assignment_fn(op) { self = self op rhs; return self; }

#define impl_fast_ops_create_op(specifiers, return_t, op, args, op_fn, ...) __VA_ARGS__ specifiers return_t operator op##args op_fn
#define impl_fast_ops_create_lhs_op(specifiers, return_t, op, op_fn, ...) impl_fast_ops_create_op(specifiers, return_t, op, (this self_t&& self), op_fn, __VA_ARGS__)
#define impl_fast_ops_create_rhs_op(specifiers, return_t, rhs_t, op, op_fn, ...) impl_fast_ops_create_op(specifiers, return_t, op, (rhs_t rhs), op_fn, __VA_ARGS__)
#define impl_fast_ops_create_lhs_rhs_op(specifiers, return_t, rhs_t, op, op_fn, ...) impl_fast_ops_create_op(specifiers, return_t, op, (this self_t&& self, rhs_t rhs), op_fn, __VA_ARGS__)
#define impl_fast_ops_create_ops(specifiers, op_ret_t, assigment_op_ret_t, rhs_t, op, op_fn, op_assignment_fn, ... /*templates*/)	\
	impl_fast_ops_create_lhs_rhs_op(specifiers, op_ret_t,			rhs_t, op,		op_fn,				__VA_ARGS__)				\
	impl_fast_ops_create_lhs_rhs_op(specifiers, assigment_op_ret_t, rhs_t, op##=,	op_assignment_fn,	__VA_ARGS__)				\


//@note: converting operators utils
#define fast_ops_structure_convert_operator(specifiers, templates, covnerting_t, construct, member_op, ... /*members*/)  \
	impl_fast_ops_create_op(specifiers, , fast_ops_args_pack(covnerting_t), , { return  construct(fast_ops_make_body(comma, member_op, this_prefix, __VA_ARGS__)); }, templates)

//@note: unary operators utils
#define fast_ops_structure_prefix_operator(specifiers, return_t, op_t/*new/ref*/, op, ... /*members*/)											\
	impl_fast_ops_create_lhs_op(specifiers, return_t, op, impl_fast_ops_##op_t##_op_fn(op, prefix, __VA_ARGS__), template <typename self_t>)	\

#define fast_ops_structure_postfix_operator(specifiers, return_t, op, ... /*members*/)																			\
	impl_fast_ops_create_op(return_t, specifiers, op, (this self_t&& self, int), impl_fast_ops_new_op_fn(op, postfix, __VA_ARGS__), template <typename self_t>)	\

#define fast_ops_structure_prefix_operators(specifiers, op, ... /*members*/)			\
	fast_ops_structure_prefix_operator(specifiers, auto&&, ref, op##op, __VA_ARGS__)	\
	fast_ops_structure_prefix_operator(specifiers, auto, new, op, __VA_ARGS__)			\

#define fast_ops_structure_all_prefix_operators(specifiers, ... /*members*/)	\
	fast_ops_structure_prefix_operators(specifiers, +, __VA_ARGS__);			\
	fast_ops_structure_prefix_operators(specifiers, -, __VA_ARGS__);			\

#define fast_ops_structure_all_postfix_operators(specifiers, ... /*members*/)	\
	fast_ops_structure_postfix_operator(specifiers, auto, ++, __VA_ARGS__);		\
	fast_ops_structure_postfix_operator(specifiers, auto, --, __VA_ARGS__);		\

//@note: arithmetic operators utils
#define fast_ops_structure_arithmetic_operators(specifiers, templates, rhs_t, op, body_variant, ... /*members*/)																	\
	impl_fast_ops_create_ops(specifiers, auto, auto&&, rhs_t, op, impl_fast_ops_new_op_fn(op, body_variant, __VA_ARGS__), impl_fast_ops_arithmetic_assignment_fn(op), templates)	\

#define fast_ops_structure_arithmetic_operators_user(specifiers, templates, rhs_t, op, op_fn)									\
	impl_fast_ops_create_ops(specifiers, auto, auto&&, rhs_t, op, op_fn, impl_fast_ops_arithmetic_assignment_fn(op), templates)	\

#define fast_ops_structure_all_arithmetic_operators(specifiers, templates, rhs_t, body_variant, ... /*members*/)			\
	fast_ops_structure_arithmetic_operators(specifiers, fast_ops_args_pack(templates), rhs_t, +, body_variant, __VA_ARGS__)	\
	fast_ops_structure_arithmetic_operators(specifiers, fast_ops_args_pack(templates), rhs_t, -, body_variant, __VA_ARGS__)	\
	fast_ops_structure_arithmetic_operators(specifiers, fast_ops_args_pack(templates), rhs_t, *, body_variant, __VA_ARGS__)	\
	fast_ops_structure_arithmetic_operators(specifiers, fast_ops_args_pack(templates), rhs_t, /, body_variant, __VA_ARGS__)	\
	fast_ops_structure_arithmetic_operators(specifiers, fast_ops_args_pack(templates), rhs_t, %, body_variant, __VA_ARGS__)	\

//@note: comparison operators utils
#define fast_ops_structure_comparison_operators(specifiers, templates, rhs_t, op, body_variant, ... /*members*/)																						\
	impl_fast_ops_create_ops(specifiers, bool, bool, rhs_t, op, impl_fast_ops_logical_op_fn(op, body_variant, __VA_ARGS__), impl_fast_ops_logical_op_fn(op##=, body_variant, __VA_ARGS__), templates)	\

#define fast_ops_structure_comparison_operators_user(specifiers, templates, rhs_t, op, op_fn, op_equal_fn)	\
	impl_fast_ops_create_ops(specifiers, bool, bool, rhs_t, op, op_fn, op_equal_fn, templates)				\

#define fast_ops_structure_equal_operator(specifiers, templates, rhs_t, body_variant, ... /*members*/)																	\
	impl_fast_ops_create_rhs_op(specifiers, bool, rhs_t, ==, const impl_fast_ops_logical_op_fn(== , this_##body_variant, __VA_ARGS__), fast_ops_args_pack(templates))	\

#define fast_ops_structure_all_comparison_operators(specifiers, templates, rhs_t, body_variant, ... /*members*/)					\
	fast_ops_structure_comparison_operators(specifiers, fast_ops_args_pack(templates), rhs_t, <, self_##body_variant, __VA_ARGS__)	\
	fast_ops_structure_comparison_operators(specifiers, fast_ops_args_pack(templates), rhs_t, >, self_##body_variant, __VA_ARGS__)	\

//@credits: thx lagcomp/csgo_sdk for this superior code
#define enum_create_cast_operator(enum_t, op) inline constexpr auto operator op(enum_t a) { return static_cast<std::underlying_type_t<enum_t>>(a); }

#define impl_enum_create_bit_operator(enum_t, op, use_enum_type)																							\
	template <typename value_t>																																\
	inline constexpr auto operator op(enum_t a, value_t b) {																								\
		using enum_type = std::underlying_type_t<enum_t>;																									\
		return static_cast<std::conditional_t<use_enum_type, enum_type, enum_t>>(static_cast<enum_type>(a) op static_cast<enum_type>(b));					\
	}																																						\
	template <typename value_t>																																\
	inline auto& operator op##=(enum_t& a, value_t b) {																										\
		using enum_type = std::underlying_type_t<enum_t>;																									\
		return reinterpret_cast<std::conditional_t<use_enum_type, enum_type, enum_t>&>(reinterpret_cast<enum_type&>(a) op##= static_cast<enum_type>(b));	\
	}																																						\

#define enum_create_bit_operators(enum_t, use_enum_type)														\
	impl_enum_create_bit_operator(enum_t, |, use_enum_type);													\
	impl_enum_create_bit_operator(enum_t, &, use_enum_type);													\
	impl_enum_create_bit_operator(enum_t, ^, use_enum_type);													\
	impl_enum_create_bit_operator(enum_t, <<, use_enum_type);													\
	impl_enum_create_bit_operator(enum_t, >>, use_enum_type);													\
	inline constexpr auto operator ~(const enum_t a) {															\
		using enum_type = std::underlying_type_t<enum_t>;														\
		return static_cast<std::conditional_t<use_enum_type, enum_type, enum_t>>(~static_cast<enum_type>(a));	\
	}