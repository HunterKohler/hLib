#ifndef HLIB_BF_GENERICS_H_
#define HLIB_BF_GENERICS_H_

#include <stdbool.h>
#include <stdint.h>

#define FORMAT_SPECIFIER(X) \
    _Generic((X), \
             signed char: "%hhd", \
             short: "%hd", \
             int: "%d", \
             long: "%ld", \
             long long: "%lld", \
             unsigned char: "%hhu", \
             unsigned short: "%hu", \
             unsigned int: "%u", \
             unsigned long: "%lu", \
             unsigned long long: "%llu", \
             float: "%.5f", \
             double: "%.5f", \
             long double: "%.10Lf", \
             char: "%c", \
             char*: "%s")

#define IS_SIGNED_INTEGRAL(X) \
    _Generic((X), \
             signed char: true, \
             short: true, \
             int: true, \
             long: true, \
             long long: true, \
             default: false)

#define IS_UNSIGNED_INTEGRAL(X) \
    _Generic((X), \
             unsigned char: true, \
             unsigned short: true, \
             unsigned int: true, \
             unsigned long: true, \
             unsigned long long: true, \
             default: false)

#define IS_INTEGRAL(X) (IS_UNSIGNED_INTEGRAL(X) || IS_SIGNED_INTEGRAL(X))

#define IS_FLOATING_POINT(X) \
    _Generic((X), \
             float: true, \
             double: true, \
             long double: true, \
             default: false)

#endif