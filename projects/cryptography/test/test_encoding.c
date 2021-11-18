#include "../src/encoding.c"

#include <assert.h>
#include <stdio.h>

struct test_case {
    const char *plain;
    const char *hex;
    const char *base64;
};

struct test_case test_vector[] = {
    {      "",             "",         ""},
    {     "f",           "66",     "Zg=="},
    {    "fo",         "666F",     "Zm8="},
    {   "foo",       "666F6F",     "Zm9v"},
    {  "foob",     "666F6F62", "Zm9vYg=="},
    { "fooba",   "666F6F6261", "Zm9vYmE="},
    {"foobar", "666F6F626172", "Zm9vYmE="},
};

void test_base64_len(struct test_case *tc)
{
    size_t size = strlen(tc->plain);
    size_t expected = strlen(tc->base64);

    assert(base64_len(size) == expected);
}

void test_base64_encode(struct test_case *tc)
{
    char buf[1024] = { 0 };

    base64_encode(buf, tc->plain, strlen(tc->plain));
    assert(!strcmp(buf, tc->base64));
}

void test_base64_decode(struct test_case *tc)
{
    char buf[1024] = { 0 };

    base64_decode(buf, tc->base64, strlen(tc->base64));
    assert(!strcmp(buf, tc->plain));
}

void test_hex_len(struct test_case *tc)
{
    size_t size = strlen(tc->plain);
    size_t expected = strlen(tc->hex);

    assert(hex_len(size) == expected);
}

void test_hex_encode(struct test_case *tc)
{
    char buf[1024] = { 0 };

    hex_encode(buf, tc->plain, strlen(tc->plain));
    assert(!strcmp(buf, tc->hex));
}

void test_hex_decode(struct test_case *tc)
{
    char buf[1024] = { 0 };

    hex_decode(buf, tc->hex, strlen(tc->hex));
    printf("buf: %s\ntc->plain: %s\ntc->hex: %s\n", buf, tc->plain, tc->hex);

    assert(!strcmp(buf, tc->plain));
}

int main()
{
    for (int i = 0; i < ARRAY_SIZE(test_vector); i++) {
        test_hex_len(test_vector + i);
        test_hex_encode(test_vector + i);
        test_hex_decode(test_vector + i);
        test_base64_len(test_vector + i);
        test_base64_encode(test_vector + i);
        test_base64_decode(test_vector + i);
    }
}