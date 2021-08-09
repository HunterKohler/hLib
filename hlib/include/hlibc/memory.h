#include <stdlib.h>
#include <stdio.h>

#ifdef DEBUG
#define xalloc_error() \
    do { \
        perror(__FILE__":"__LINE__": Error allocating memory: "); \
        exit(1); \
    } while(0)
#else
#define xalloc_error() \
    do { \
        perror("Error allocating memory: "); \
        exit(1); \
    } while(0)
#endif

__attribute__((always_inline, malloc))
inline void* xmalloc(size_t size) {
    void* mem = malloc(size);

    if(!mem) {
        xalloc_error();
    }

    return mem;
}

__attribute__((always_inline, malloc))
inline void* xcalloc(size_t count, size_t size) {
    void* mem = calloc(count, size);

    if(!mem) {
        xalloc_error();
    }

    return mem;
}

__attribute__((always_inline))
inline void* xrealloc(void* ptr, size_t size) {
    ptr = realloc(ptr, size);

    if(!ptr) {
        xalloc_error();
    }

    return ptr;
}