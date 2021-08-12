#ifndef HLIBC_MATH_H_
#define HLIBC_MATH_H_

#define max(a,b) ({ \
    __typeof__(a) _a = (b); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b; \
})

#endif