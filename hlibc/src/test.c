#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <hlibc/def.h>
#include <hlibc/test.h>

char *unit_test_result_string(struct unit_test_result *result)
{
    char *str;
    asprintf(&str,
             "{\n"
             "    id: %zu,\n"
             "    failed: %s,\n"
             "    reason: %s,\n"
             "    file: %s,\n"
             "    fn_name: %s,\n"
             "    line: %d,\n"
             "    duration: %f,\n"
             "}",
             result->id,
             result->failed ? "true" : "false",
             result->reason,
             result->file,
             result->fn_name,
             result->line,
             (double)result->duration / CLOCKS_PER_SEC);
    return str;
}

bool unit_test_init(struct unit_test *test,
                    void (*fn)(),
                    const char *desc,
                    const char *directive,
                    const char *directive_desc)
{
    test->fn = fn;
    test->desc = desc;
    test->directive = directive;
    test->directive_desc = directive_desc;
    return false;
}

struct unit_test *unit_test_new(void (*fn)(),
                                const char *desc,
                                const char *directive,
                                const char *directive_desc)
{
    struct unit_test *test = malloc(sizeof(*test));

    if (unit_test_init(test, fn, desc, directive, directive_desc)) {
        free(test);
        return NULL;
    }

    return test;
}

bool unit_test_group_init(struct unit_test_group *group, const char *desc)
{
    group->test_count = 0;
    group->test_cap = 10;
    group->desc = desc;
    group->tests = malloc(group->test_cap * sizeof(*group->tests));

    if (!group->tests) {
        return true;
    }

    return false;
}

struct unit_test_group *unit_test_group_new(const char *desc)
{
    struct unit_test_group *group = malloc(sizeof(*group));

    if (unit_test_group_init(group, desc)) {
        free(group);
        return NULL;
    }

    return group;
}

bool unit_test_group_add(struct unit_test_group *group, struct unit_test *test)
{
    if (group->test_count == group->test_cap) {
        size_t new_cap = 3 * group->test_cap >> 1;
        struct unit_test **tests =
            realloc(group->tests, new_cap * sizeof(*group->tests));

        if (!tests) {
            return true;
        }

        group->tests = tests;
        group->test_cap = new_cap;
    }

    group->tests[group->test_count++] = test;
    return false;
}

thread_local struct unit_test_result *active_result;

struct unit_test_result *unit_test_run(struct unit_test *test)
{
    thread_local static size_t id = 1;

    struct unit_test_result *result = malloc(sizeof(*result));

    if (!result) {
        return NULL;
    }

    result->id = id++;
    result->failed = false;
    result->reason = NULL;
    result->file = NULL;
    result->fn_name = NULL;
    result->line = 0;
    result->duration = 0;

    active_result = result;
    clock_t start = clock();

    test->fn();

    result->duration = clock() - start;
    active_result = NULL;

    return result;
}

struct unit_test_result **unit_test_group_run(struct unit_test_group *group)
{
    printf("{\n"
           "    desc: %s\n"
           "    test_count: %zu\n"
           "    test_cap: %zu\n"
           "}\n",
           group->desc,
           group->test_count,
           group->test_cap);

    struct unit_test_result **results =
        malloc(group->test_count * (sizeof(*results)));

    if (!results) {
        return NULL;
    }

    clock_t start = clock();

    for (size_t i = 0; i < group->test_count; i++) {
        results[i] = unit_test_run(group->tests[i]);
    }

    group->duration = clock() - start;
    return results;
}

int unit_test_group_launch(struct unit_test_group *group)
{
    return pthread_create(
        &group->thread, NULL, (void *(*)(void *))unit_test_group_run, group);
}

struct unit_test_result **unit_test_group_join(struct unit_test_group *group)
{
    struct unit_test_result **results;
    pthread_join(group->thread, (void *)&results);
    return results;
}
