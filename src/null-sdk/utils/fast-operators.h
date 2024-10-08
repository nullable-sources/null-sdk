#pragma once
#include <boost/preprocessor.hpp>
#include <type_traits>

#if !defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL
#define NULLSDK_TRADITIONAL_BOOST_PP_EXPAND(X) BOOST_PP_EXPAND(X)
#else
#define NULLSDK_TRADITIONAL_BOOST_PP_EXPAND(X) X
#endif

#define NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_THIS_RHS_FIELD(op, field) field op rhs.field
#define NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_SELF_RHS_FIELD(op, field) self.field op rhs.field

#define NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_THIS_RHS_VALUE(op, field) field op rhs
#define NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_SELF_RHS_VALUE(op, field) NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_THIS_RHS_VALUE(op, self.field)

#define NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_THIS_POSTFIX(op, field) field##op
#define NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_SELF_POSTFIX(op, field) NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_THIS_POSTFIX(op, self.field)

#define NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_THIS_PREFIX(op, field) op##field
#define NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_SELF_PREFIX(op, field) NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_THIS_PREFIX(op, self.field)

#define NULLSDK_IMPL_FAST_OPS_GET_COMMA(op, variant, _1, _2, _3, _4, name, ...) name
#define NULLSDK_IMPL_FAST_OPS_GET_DELIMITER(op, variant, delimiter_literal, _1, _2, _3, _4, name, ...) name
#define NULLSDK_FAST_OPS_MAKE_BODY(type /*DELIMITER or COMMA*/, ...)                                                                                                                            \
    NULLSDK_TRADITIONAL_BOOST_PP_EXPAND(                                                                                                                                                        \
        NULLSDK_IMPL_FAST_OPS_GET_##type(                                                                                                                                                       \
            __VA_ARGS__, NULLSDK_IMPL_FAST_OPS_##type##_4, NULLSDK_IMPL_FAST_OPS_##type##_3, NULLSDK_IMPL_FAST_OPS_##type##_2, NULLSDK_IMPL_FAST_OPS_##type##_1, NULLSDK_IMPL_FAST_OPS_##type## \
        )(__VA_ARGS__)                                                                                                                                                                          \
    )                                                                                                                                                                                           \

#define NULLSDK_IMPL_FAST_OPS_DELIMITER_1(op, variant, delimiter_literal, field)            NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_##variant(op, field)
#define NULLSDK_IMPL_FAST_OPS_DELIMITER_2(op, variant, delimiter_literal, _1, _2)           NULLSDK_IMPL_FAST_OPS_DELIMITER_1(op, variant, , _1)                            delimiter_literal NULLSDK_IMPL_FAST_OPS_DELIMITER_1(op, variant, , _2)
#define NULLSDK_IMPL_FAST_OPS_DELIMITER_3(op, variant, delimiter_literal, _1, _2, _3)       NULLSDK_IMPL_FAST_OPS_DELIMITER_2(op, variant, delimiter_literal, _1, _2)       delimiter_literal NULLSDK_IMPL_FAST_OPS_DELIMITER_1(op, variant, , _3)
#define NULLSDK_IMPL_FAST_OPS_DELIMITER_4(op, variant, delimiter_literal, _1, _2, _3, _4)   NULLSDK_IMPL_FAST_OPS_DELIMITER_3(op, variant, delimiter_literal, _1, _2, _3)   delimiter_literal NULLSDK_IMPL_FAST_OPS_DELIMITER_1(op, variant, , _4)

#define NULLSDK_IMPL_FAST_OPS_COMMA_1(op, variant, field)           NULLSDK_IMPL_FAST_OPS_BODY_VARIANT_##variant(op, field)
#define NULLSDK_IMPL_FAST_OPS_COMMA_2(op, variant, _1, _2)          NULLSDK_IMPL_FAST_OPS_COMMA_1(op, variant, _1)          , NULLSDK_IMPL_FAST_OPS_COMMA_1(op, variant, _2)
#define NULLSDK_IMPL_FAST_OPS_COMMA_3(op, variant, _1, _2, _3)      NULLSDK_IMPL_FAST_OPS_COMMA_2(op, variant, _1, _2)      , NULLSDK_IMPL_FAST_OPS_COMMA_1(op, variant, _3)
#define NULLSDK_IMPL_FAST_OPS_COMMA_4(op, variant, _1, _2, _3, _4)  NULLSDK_IMPL_FAST_OPS_COMMA_3(op, variant, _1, _2, _3)  , NULLSDK_IMPL_FAST_OPS_COMMA_1(op, variant, _4)


//@note: global fast_ops defines
#define NULLSDK_FAST_OPS_ARGS_PACK(...) __VA_ARGS__

#define NULLSDK_IMPL_FAST_OPS_REF_OP_FN(op, body_variant, ...) { NULLSDK_FAST_OPS_MAKE_BODY(DELIMITER, op, SELF_##body_variant, ;, __VA_ARGS__); return self; }
#define NULLSDK_IMPL_FAST_OPS_NEW_OP_FN(op, body_variant, ...) { return std::decay_t<self_t>(NULLSDK_FAST_OPS_MAKE_BODY(COMMA, op, SELF_##body_variant, __VA_ARGS__)); }
#define NULLSDK_IMPL_FAST_OPS_LOGICAL_OP_FN(op, body_variant, ...) { return NULLSDK_FAST_OPS_MAKE_BODY(DELIMITER, op, body_variant, &&, __VA_ARGS__); }
#define NULLSDK_IMPL_FAST_OPS_ARITHMETIC_ASSIGNMENT_FN(op) { self = self op rhs; return self; }

#define NULLSDK_IMPL_FAST_OPS_CREATE_OP(specifiers, return_t, op, args, op_fn, ...) __VA_ARGS__ specifiers return_t operator op##args op_fn
#define NULLSDK_IMPL_FAST_OPS_CREATE_LHS_OP(specifiers, return_t, op, op_fn, ...) NULLSDK_IMPL_FAST_OPS_CREATE_OP(specifiers, return_t, op, (this self_t&& self), op_fn, __VA_ARGS__)
#define NULLSDK_IMPL_FAST_OPS_CREATE_RHS_OP(specifiers, return_t, rhs_t, op, op_fn, ...) NULLSDK_IMPL_FAST_OPS_CREATE_OP(specifiers, return_t, op, (rhs_t rhs), op_fn, __VA_ARGS__)
#define NULLSDK_IMPL_FAST_OPS_CREATE_LHS_RHS_OP(specifiers, return_t, rhs_t, op, op_fn, ...) NULLSDK_IMPL_FAST_OPS_CREATE_OP(specifiers, return_t, op, (this self_t&& self, rhs_t rhs), op_fn, __VA_ARGS__)
#define NULLSDK_IMPL_FAST_OPS_CREATE_OPS(specifiers, op_ret_t, assigment_op_ret_t, rhs_t, op, op_fn, op_assignment_fn, ... /*templates*/)   \
    NULLSDK_IMPL_FAST_OPS_CREATE_LHS_RHS_OP(specifiers, op_ret_t,           rhs_t, op,      op_fn,              __VA_ARGS__)                \
    NULLSDK_IMPL_FAST_OPS_CREATE_LHS_RHS_OP(specifiers, assigment_op_ret_t, rhs_t, op##=,   op_assignment_fn,   __VA_ARGS__)                \


//@note: converting operators utils
#define NULLSDK_FAST_OPS_STRUCTURE_CONVERT_OPERATOR(specifiers, templates, covnerting_t, construct, member_op, ... /*members*/)                                                                         \
    NULLSDK_IMPL_FAST_OPS_CREATE_OP(specifiers, , NULLSDK_FAST_OPS_ARGS_PACK(covnerting_t), , { return construct(NULLSDK_FAST_OPS_MAKE_BODY(COMMA, member_op, THIS_PREFIX, __VA_ARGS__)); }, templates)

//@note: unary operators utils
#define NULLSDK_FAST_OPS_STRUCTURE_PREFIX_OPERATOR(specifiers, return_t, op_t/*new/ref*/, op, ... /*members*/)                                                  \
    NULLSDK_IMPL_FAST_OPS_CREATE_LHS_OP(specifiers, return_t, op, NULLSDK_IMPL_FAST_OPS_##op_t##_OP_FN(op, PREFIX, __VA_ARGS__), template <typename self_t>)    \

#define NULLSDK_FAST_OPS_STRUCTURE_POSTFIX_OPERATOR(specifiers, return_t, op, ... /*members*/)                                                                                  \
    NULLSDK_IMPL_FAST_OPS_CREATE_OP(return_t, specifiers, op, (this self_t&& self, int), NULLSDK_IMPL_FAST_OPS_NEW_OP_FN(op, POSTFIX, __VA_ARGS__), template <typename self_t>) \

#define NULLSDK_FAST_OPS_STRUCTURE_PREFIX_OPERATORS(specifiers, op, ... /*members*/)            \
    NULLSDK_FAST_OPS_STRUCTURE_PREFIX_OPERATOR(specifiers, auto&&, REF, op##op, __VA_ARGS__)    \
    NULLSDK_FAST_OPS_STRUCTURE_PREFIX_OPERATOR(specifiers, auto, NEW, op, __VA_ARGS__)          \

#define NULLSDK_FAST_OPS_STRUCTURE_ALL_PREFIX_OPERATORS(specifiers, ... /*members*/)    \
    NULLSDK_FAST_OPS_STRUCTURE_PREFIX_OPERATORS(specifiers, +, __VA_ARGS__);            \
    NULLSDK_FAST_OPS_STRUCTURE_PREFIX_OPERATORS(specifiers, -, __VA_ARGS__);            \

#define NULLSDK_FAST_OPS_STRUCTURE_ALL_POSTFIX_OPERATORS(specifiers, ... /*members*/)   \
    NULLSDK_FAST_OPS_STRUCTURE_POSTFIX_OPERATOR(specifiers, auto, ++, __VA_ARGS__);     \
    NULLSDK_FAST_OPS_STRUCTURE_POSTFIX_OPERATOR(specifiers, auto, --, __VA_ARGS__);     \

//@note: arithmetic operators utils
#define NULLSDK_FAST_OPS_STRUCTURE_ARITHMETIC_OPERATORS(specifiers, templates, rhs_t, op, body_variant, ... /*members*/)                                                                                    \
    NULLSDK_IMPL_FAST_OPS_CREATE_OPS(specifiers, auto, auto&&, rhs_t, op, NULLSDK_IMPL_FAST_OPS_NEW_OP_FN(op, body_variant, __VA_ARGS__), NULLSDK_IMPL_FAST_OPS_ARITHMETIC_ASSIGNMENT_FN(op), templates)    \

#define NULLSDK_FAST_OPS_STRUCTURE_ARITHMETIC_OPERATORS_USER(specifiers, templates, rhs_t, op, op_fn)                                           \
    NULLSDK_IMPL_FAST_OPS_CREATE_OPS(specifiers, auto, auto&&, rhs_t, op, op_fn, NULLSDK_IMPL_FAST_OPS_ARITHMETIC_ASSIGNMENT_FN(op), templates) \

#define NULLSDK_FAST_OPS_STRUCTURE_ALL_ARITHMETIC_OPERATORS(specifiers, templates, rhs_t, body_variant, ... /*members*/)                    \
    NULLSDK_FAST_OPS_STRUCTURE_ARITHMETIC_OPERATORS(specifiers, NULLSDK_FAST_OPS_ARGS_PACK(templates), rhs_t, +, body_variant, __VA_ARGS__) \
    NULLSDK_FAST_OPS_STRUCTURE_ARITHMETIC_OPERATORS(specifiers, NULLSDK_FAST_OPS_ARGS_PACK(templates), rhs_t, -, body_variant, __VA_ARGS__) \
    NULLSDK_FAST_OPS_STRUCTURE_ARITHMETIC_OPERATORS(specifiers, NULLSDK_FAST_OPS_ARGS_PACK(templates), rhs_t, *, body_variant, __VA_ARGS__) \
    NULLSDK_FAST_OPS_STRUCTURE_ARITHMETIC_OPERATORS(specifiers, NULLSDK_FAST_OPS_ARGS_PACK(templates), rhs_t, /, body_variant, __VA_ARGS__) \
    NULLSDK_FAST_OPS_STRUCTURE_ARITHMETIC_OPERATORS(specifiers, NULLSDK_FAST_OPS_ARGS_PACK(templates), rhs_t, %, body_variant, __VA_ARGS__) \

//@note: comparison operators utils
#define NULLSDK_FAST_OPS_STRUCTURE_COMPARISON_OPERATORS(specifiers, templates, rhs_t, op, body_variant, ... /*members*/)                                                                                                        \
    NULLSDK_IMPL_FAST_OPS_CREATE_OPS(specifiers, bool, bool, rhs_t, op, NULLSDK_IMPL_FAST_OPS_LOGICAL_OP_FN(op, body_variant, __VA_ARGS__), NULLSDK_IMPL_FAST_OPS_LOGICAL_OP_FN(op##=, body_variant, __VA_ARGS__), templates)   \

#define NULLSDK_FAST_OPS_STRUCTURE_COMPARISON_OPERATORS_USER(specifiers, templates, rhs_t, op, op_fn, op_equal_fn)  \
    NULLSDK_IMPL_FAST_OPS_CREATE_OPS(specifiers, bool, bool, rhs_t, op, op_fn, op_equal_fn, templates)              \

#define NULLSDK_FAST_OPS_STRUCTURE_EQUAL_OPERATOR(specifiers, templates, rhs_t, body_variant, ... /*members*/)                                                                                  \
    NULLSDK_IMPL_FAST_OPS_CREATE_RHS_OP(specifiers, bool, rhs_t, ==, const NULLSDK_IMPL_FAST_OPS_LOGICAL_OP_FN(== , THIS_##body_variant, __VA_ARGS__), NULLSDK_FAST_OPS_ARGS_PACK(templates))   \

#define NULLSDK_FAST_OPS_STRUCTURE_SELF_EQUAL_OPERATOR(specifiers, templates, rhs_t, body_variant, ... /*members*/)                                                                         \
    NULLSDK_IMPL_FAST_OPS_CREATE_LHS_RHS_OP(specifiers, bool, rhs_t, ==, NULLSDK_IMPL_FAST_OPS_LOGICAL_OP_FN(== , SELF_##body_variant, __VA_ARGS__), NULLSDK_FAST_OPS_ARGS_PACK(templates)) \

#define NULLSDK_FAST_OPS_STRUCTURE_ALL_COMPARISON_OPERATORS(specifiers, templates, rhs_t, body_variant, ... /*members*/)                            \
    NULLSDK_FAST_OPS_STRUCTURE_COMPARISON_OPERATORS(specifiers, NULLSDK_FAST_OPS_ARGS_PACK(templates), rhs_t, <, SELF_##body_variant, __VA_ARGS__)  \
    NULLSDK_FAST_OPS_STRUCTURE_COMPARISON_OPERATORS(specifiers, NULLSDK_FAST_OPS_ARGS_PACK(templates), rhs_t, >, SELF_##body_variant, __VA_ARGS__)  \

//@credits: thx lagcomp/csgo_sdk for this superior code
#define NULLSDK_ENUM_CREATE_CAST_OPERATOR(enum_t, op) inline constexpr auto operator op(enum_t a) { return static_cast<std::underlying_type_t<enum_t>>(a); }

#define NULLSDK_IMPL_ENUM_CREATE_BIT_OPERATOR(enum_t, op, use_enum_type)                                                                                    \
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

#define NULLSDK_ENUM_CREATE_BIT_OPERATORS(enum_t, use_enum_type)                                                \
    NULLSDK_IMPL_ENUM_CREATE_BIT_OPERATOR(enum_t, |, use_enum_type);                                            \
    NULLSDK_IMPL_ENUM_CREATE_BIT_OPERATOR(enum_t, &, use_enum_type);                                            \
    NULLSDK_IMPL_ENUM_CREATE_BIT_OPERATOR(enum_t, ^, use_enum_type);                                            \
    NULLSDK_IMPL_ENUM_CREATE_BIT_OPERATOR(enum_t, <<, use_enum_type);                                           \
    NULLSDK_IMPL_ENUM_CREATE_BIT_OPERATOR(enum_t, >>, use_enum_type);                                           \
    inline constexpr auto operator ~(const enum_t a) {                                                          \
        using enum_type = std::underlying_type_t<enum_t>;                                                       \
        return static_cast<std::conditional_t<use_enum_type, enum_type, enum_t>>(~static_cast<enum_type>(a));   \
    }