#pragma once

#if defined(NULLSDK_STATIC_LINKING)
    #define NULLSDK_API
#elif defined(NULLSDK_DYNAMIC_LINKING)
    #ifdef NULLSDK_EXPORTING
        #define NULLSDK_API __declspec(dllexport)
    #else
        #define NULLSDK_API __declspec(dllimport)
    #endif
#else
    #error unknown null-sdk linking type
#endif