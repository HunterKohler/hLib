#ifndef PROJECTS_BF_BENCHMARK_H_
#define PROJECTS_BF_BENCHMARK_H_

#include <time.h>

clock_t BENCHMARK_START_TIME;
clock_t BENCHMARK_END_TIME;
clock_t BENCHMARK_TIME_DIFF;
clock_t BENCHMARK_SECONDS;

#define benchmark(...)                                                \
BENCHMARK_START_TIME = clock();                                       \
__VA_ARGS__                                                           \
BENCHMARK_END_TIME = clock();                                         \
BENCHMARK_TIME_DIFF = BENCHMARK_END_TIME - BENCHMARK_START_TIME;      \
BENCHMARK_SECONDS = ((double) BENCHMARK_TIME_DIFF) / CLOCKS_PER_SEC;  \
printf("%f seconds\n", BENCHMARK_SECONDS);


#endif