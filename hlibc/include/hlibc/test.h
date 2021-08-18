#ifndef HLIBC_TEST_H_
#define HLIBC_TEST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <hlibc/def.h>

struct unit_test {
    void (*fn)();

    const char *desc;
    const char *directive;
    const char *directive_desc;
};

struct unit_test_group {
    const char *desc;

    size_t test_count;
    size_t test_cap;

    struct unit_test **tests;

    pthread_t thread;
    clock_t duration;
};

struct unit_test_result {
    size_t id;

    bool failed;
    const char *reason;
    const char *file;
    const char *fn_name;
    unsigned int line;

    clock_t duration;
};

char *unit_test_result_string(struct unit_test_result *result);
bool unit_test_init(struct unit_test *test,
                    void (*fn)(),
                    const char *desc,
                    const char *directive,
                    const char *directive_desc);
struct unit_test *unit_test_new(void (*fn)(),
                                const char *desc,
                                const char *directive,
                                const char *directive_desc);

bool unit_test_group_init(struct unit_test_group *group, const char *desc);
struct unit_test_group *unit_test_group_new(const char *desc);
bool unit_test_group_add(struct unit_test_group *group, struct unit_test *test);

int unit_test_group_launch(struct unit_test_group *group);

struct unit_test_result *unit_test_run(struct unit_test *test);
struct unit_test_result **unit_test_group_run(struct unit_test_group *group);
struct unit_test_result **unit_test_group_join(struct unit_test_group *group);

#define assert(x)                                     \
    do {                                              \
        if (!(x)) {                                   \
            active_result->failed = true;             \
            active_result->reason = "assert(" #x ")"; \
            active_result->file = __FILE__;           \
            active_result->line = __LINE__;           \
            active_result->fn_name = __FUNCTION__;    \
            return;                                   \
        }                                             \
    } while (0)

#endif