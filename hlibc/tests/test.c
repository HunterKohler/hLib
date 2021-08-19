#include <hlibc/io.h>
#include <hlibc/test.h>

void test_frewind()
{
}

int main()
{
    struct unit_test tests[5];
    unit_test_init(tests, test_frewind, "frewind()", NULL, NULL);
    struct unit_test_result *result = unit_test_run(tests);

    printf("%s\n", unit_test_result_string(result));
}