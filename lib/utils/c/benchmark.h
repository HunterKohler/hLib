#ifndef HLIB_UTILS_C_BENCHMARK_H_
#define HLIB_UTILS_C_BENCHMARK_H_

#include <stdio.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif


double benchmark(void (*function)()) {
    clock_t start = clock();
    function();
    return ((double) (clock() - start)) / CLOCKS_PER_SEC;
}

clock_t benchmark_log(const char* label, void (* function)()) {
    printf("%s: %f sec\n", label, benchmark(function));
}

#ifdef __cplusplus
}
#endif

#endif