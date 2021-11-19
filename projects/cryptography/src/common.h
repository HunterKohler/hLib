#ifndef CRYPTO_COMMON_H_
#define CRYPTO_COMMON_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef noreturn
#define noreturn _Noreturn
#endif

#ifndef thread_local
#define thread_local _Thread_local
#endif

#ifndef static_assert
#define static_assert _Static_assert
#endif

#ifndef generic
#define generic _Generic
#endif

#define IS_ARRAY(x) \
    (!__builtin_types_compatible_p(__typeof__(x), __typeof__(&(x)[0])))

#define ARRAY_SIZE(x)                            \
    ({                                           \
        static_assert(IS_ARRAY(x), "Non-array"); \
        sizeof(x) / sizeof((x)[0]);              \
    })

#endif