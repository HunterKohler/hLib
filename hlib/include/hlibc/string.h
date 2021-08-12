#ifndef HLIBC_STRING_H_
#define HLIBC_STRING_H_

#include <string.h>

#if __has_builtin(__builtin_types_compatible_p)
    #define lstrcpy(dest, src) \
        ({ \
            _Static_assert( \
                __builtin_types_compatible_p(__typeof__(src), char[])); \
            memcpy(dest, str, sizeof(src)); \
        })
#endif

#endif