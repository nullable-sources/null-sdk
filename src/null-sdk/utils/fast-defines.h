#pragma once
#include <boost/preprocessor.hpp>

#define __fast_defs__unpack_tuple_element__(i, data, elem) BOOST_PP_TUPLE_ELEM(data, elem)
#define __fast_defs__unpack_seq_enum(num, transform_name, ...)                                          \
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(                                                           \
        __fast_defs__unpack_tuple_element__##transform_name, num, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__) \
    ))                                                                                                  \