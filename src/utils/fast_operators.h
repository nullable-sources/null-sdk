#pragma once
#include <type_traits>

#define impl_default_arithmetic_assignment_func(op, variable_name) { self = self op variable_name; return self; }
#define impl_class_create_operator(return_type, op, op_func, args, ...) __VA_ARGS__ return_type operator op##args op_func

#define impl_class_create_arithmetic_operators(varialbe_name, class_t, op, op_func, op_assignment_func)                                             \
    impl_class_create_operator(auto, op, op_func, (this self_t&& self, const class_t& varialbe_name), template <typename self_t>)                 \
    impl_class_create_operator(auto&&, op##=, op_assignment_func, (this self_t&& self, const class_t& varialbe_name), template <typename self_t>)   \

#define class_create_arithmetic_operators(variable_name, class_t, op, op_func)                                                              \
    impl_class_create_arithmetic_operators(variable_name, class_t, op, op_func, impl_default_arithmetic_assignment_func(op, variable_name)) \

#define class_create_logic_operators(variable_name, class_t, op, op_func, op_arithmetic_func)                                                   \
    impl_class_create_operator(bool, op, op_func, (this self_t&& self, const class_t& variable_name), template <typename self_t>)               \
	impl_class_create_operator(bool, op##=, op_arithmetic_func, (this self_t&& self, const class_t& variable_name), template <typename self_t>) \


//@credits: thx lagcomp/csgo_sdk for this superior code
#define enum_create_cast_operator(enum_t, op) inline constexpr auto operator op(enum_t a) { return static_cast<std::underlying_type_t<enum_t>>(a); }

#define enum_create_bit_operator(enum_t, op, use_enum_type)                                                                                                 \
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
    enum_create_bit_operator(enum_t, |, use_enum_type)                                                          \
    enum_create_bit_operator(enum_t, &, use_enum_type)                                                          \
    enum_create_bit_operator(enum_t, ^, use_enum_type)                                                          \
    inline constexpr auto operator ~(const enum_t a) {                                                          \
        using enum_type = std::underlying_type_t<enum_t>;                                                       \
        return static_cast<std::conditional_t<use_enum_type, enum_type, enum_t>>( ~static_cast<enum_type>(a));  \
    }