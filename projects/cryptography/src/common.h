#ifndef CRYPTO_COMMON_H_
#define CRYPTO_COMMON_H_

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef thread_local
#define thread_local _Thread_local
#endif

#ifndef static_assert
#define static_assert _Static_assert
#endif

#ifndef noreturn
#define noreturn _Noreturn
#endif

#define IS_ARRAY(a) \
    (!__builtin_types_compatible_p(__typeof(a), __typeof(&(a)[0])))

#define ARRAY_SIZE(a)                                   \
    ({                                                  \
        static_assert(IS_ARRAY(a), "Non-static array"); \
        sizeof(a) / sizeof((a)[0]);                     \
    })

#endif