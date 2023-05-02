#pragma once
#include <type_traits>

#define impl_default_arithmetic_assignment_func(op, variable_name) { self = self op variable_name; return self; }
#define impl_class_create_operator(return_type, op, op_func, args, ...) __VA_ARGS__ return_type operator op##args op_func

#define impl_class_create_arithmetic_operators(varialbe_name, class_t, op, op_func, op_assignment_func, ...)                        \
    impl_class_create_operator(auto, op, op_func, (this self_t&& self, const class_t& varialbe_name), __VA_ARGS__)                  \
    impl_class_create_operator(auto&&, op##=, op_assignment_func, (this self_t&& self, const class_t& varialbe_name), __VA_ARGS__)  \

#define class_create_arithmetic_operators(variable_name, class_t, op, op_func)                                                                                          \
    impl_class_create_arithmetic_operators(variable_name, class_t, op, op_func, impl_default_arithmetic_assignment_func(op, variable_name), template <typename self_t>) \

#define class_create_logic_operators(variable_name, class_t, op, op_func, op_arithmetic_func)                                                   \
    impl_class_create_operator(bool, op, op_func, (this self_t&& self, const class_t& variable_name), template <typename self_t>)               \
	impl_class_create_operator(bool, op##=, op_arithmetic_func, (this self_t&& self, const class_t& variable_name), template <typename self_t>) \


//@credits: thx lagcomp/csgo_sdk for this superior code
#define enum_create_cast_operator(enum_t, op) inline constexpr auto operator op(enum_t a) { return static_cast<std::underlying_type_t<enum_t>>(a); }

#define impl_enum_create_bit_operator(enum_t, op, use_enum_type)                                                                                            \
    template <typename value_t>                                                                                                                             \
    inline constexpr auto operator op(enum_t a, value_t b) {                                                                                                \
        using enum_type = std::underlying_type_t<enum_t>;                                                                                                   \
        return static_cast<std::conditional_t<use_enum_type, enum_type, enum_t>>(static_cast<enum_type>(a) op static_cast<enum_type>(b));                   \
    }                                                                                                                                                       \
    template <typename value_t>                                                                                                                             \
    inline auto& operator op##=(enum_t& a, value_t b) {                                                                                                     \
        using enum_type = std::underlying_type_t<enum_t>;                                                                                                   \
        return reinterpret_cast<std::conditional_t<use_enum_type, enum_type, enum_t>&>(reinterpret_cast<enum_type&>(a) op##= static_cast<enum_type>(b));    \
    }                                                                                                                                                       \

#define enum_create_bit_operators(enum_t, use_enum_type)                                                        \
    impl_enum_create_bit_operator(enum_t, |, use_enum_type);                                                    \
    impl_enum_create_bit_operator(enum_t, &, use_enum_type);                                                    \
    impl_enum_create_bit_operator(enum_t, ^, use_enum_type);                                                    \
    impl_enum_create_bit_operator(enum_t, <<, use_enum_type);                                                   \
    impl_enum_create_bit_operator(enum_t, >>, use_enum_type);                                                   \
    inline constexpr auto operator ~(const enum_t a) {                                                          \
        using enum_type = std::underlying_type_t<enum_t>;                                                       \
        return static_cast<std::conditional_t<use_enum_type, enum_type, enum_t>>(~static_cast<enum_type>(a));   \
    }

#define make_tuple_impl_expand(x) x
#define make_tuple_impl_get_macro(_1, _2, _3, _4, name,...) name

#define make_tuple_impl_method_name(...)	\
	make_tuple_impl_expand(					\
		make_tuple_impl_get_macro(			\
			__VA_ARGS__,					\
			make_tuple_impl_method_name4,	\
			make_tuple_impl_method_name3,	\
			make_tuple_impl_method_name2,	\
			make_tuple_impl_method_name1	\
		)(__VA_ARGS__)						\
	)										\

#define make_tuple_impl_method_name1(arg1)						arg1
#define make_tuple_impl_method_name2(arg1, arg2)				arg1##arg2
#define make_tuple_impl_method_name3(arg1, arg2, arg3)			arg1##arg2##arg3
#define make_tuple_impl_method_name4(arg1, arg2, arg3, arg4)	arg1##arg2##arg3##arg4

#define make_tuple_impl_method_body(...)	\
	make_tuple_impl_expand(					\
		make_tuple_impl_get_macro(			\
			__VA_ARGS__,					\
			make_tuple_impl_method_body4,	\
			make_tuple_impl_method_body3,	\
			make_tuple_impl_method_body2,	\
			make_tuple_impl_method_body1	\
		)(__VA_ARGS__)						\
	)										\

#define make_tuple_impl_method_body1(arg1)						self.arg1
#define make_tuple_impl_method_body2(arg1, arg2)				self.arg1, self.arg2
#define make_tuple_impl_method_body3(arg1, arg2, arg3)			self.arg1, self.arg2, self.arg3
#define make_tuple_impl_method_body4(arg1, arg2, arg3, arg4)	self.arg1, self.arg2, self.arg3, self.arg4

#define make_tuple_cast(...)                                                                        \
    template <typename self_t> auto make_tuple_impl_method_name(__VA_ARGS__)(this self_t&& self) {  \
        return std::make_tuple(make_tuple_impl_method_body(__VA_ARGS__));                           \
    }