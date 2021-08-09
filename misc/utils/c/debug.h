#ifndef HLIB_UTILS_C_DEBUG_H_
#define HLIB_UTILS_C_DEBUG_H_

#include "./generics.h"

#define _STR(X) #X
#define STR(X) _STR(X)
#define DEBUG_PREFIX "\e[3;1;33mDEBUG\e[0m" " " __FILE__ ":" STR(__LINE__) "  "

#define DEBUG(X) \
    do { \
        printf(DEBUG_PREFIX #X " := "); \
        printf(FORMAT_SPECIFIER(X), X); \
        printf("\n"); \
    } while (0)


#endif