#pragma once
#include <type_traits>

#define class_create_operators(return_type, op, op_func, ...)   \
    return_type operator op(__VA_ARGS__) const op_func          \
    return_type operator op(__VA_ARGS__) op_func                \

#define class_create_arithmetic_operators(class_t, op, op_func, op_comparison_func) \
    class_create_operators(class_t, op, op_func, const class_t& a)                  \
    class_t& operator op##=(const class_t& a) op_comparison_func                    \

#define class_create_logic_operators(class_t, op, op_func, op_comparison_func)	\
    class_create_operators(bool, op, op_func, const class_t& a)					\
	class_create_operators(bool, op##=, op_comparison_func, const class_t& a)	\

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