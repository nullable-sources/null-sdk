#pragma once
#include <boost/preprocessor.hpp>

#define NULLSDK_FAST_DEFS__UNPACK_TUPLE_ELEMENT__(i, data, elem) BOOST_PP_TUPLE_ELEM(data, elem)
#define NULLSDK_FAST_DEFS__UNPACK_SEQ_ENUM(num, transform_name, ...)                                            \
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(                                                                   \
        NULLSDK_FAST_DEFS__UNPACK_TUPLE_ELEMENT__##transform_name, num, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)   \
    ))
