#include "../src/encoding.c"

#include <assert.h>
#include <stdio.h>

struct test_case {
    size_t plain_size;
    const byte_t *plain;

    size_t hex_size;
    const byte_t *hex;

    size_t base64_size;
    const byte_t *base64;
};

struct test_case test_vector[] = {
    {0,       "",  0,             "", 0,         ""},
    {1,      "f",  2,           "66", 4,     "Zg=="},
    {2,     "fo",  4,         "666f", 4,     "Zm8="},
    {3,    "foo",  6,       "666f6f", 4,     "Zm9v"},
    {4,   "foob",  8,     "666f6f62", 8, "Zm9vYg=="},
    {5,  "fooba", 10,   "666f6f6261", 8, "Zm9vYmE="},
    {6, "foobar", 12, "666f6f626172", 8, "Zm9vYmFy"},
};

void test_base64_encode(struct test_case *tc)
{
    byte_t out[1024] = { 0 };

    base64_encode(tc->plain, tc->plain_size, out);
    assert(!memcmp(out, tc->base64, tc->base64_size));
}

void test_base64_decode(struct test_case *tc)
{
    byte_t buf[1024] = { 0 };

    base64_decode(tc->base64, tc->base64_size, buf);
    assert(!memcmp(buf, tc->plain, tc->plain_size));
}

void test_hex_encode(struct test_case *tc)
{
    byte_t out[1024] = { 0 };
    hex_encode(tc->plain, tc->plain_size, out);
    assert(!memcmp(out, tc->hex, tc->hex_size));
}

void test_hex_decode(struct test_case *tc)
{
    byte_t out[1024] = { 0 };

    assert(hex_decode(tc->hex, tc->hex_size, out) == -1);
    assert(!memcmp(out, tc->plain, tc->plain_size));
}

// void test_hex_decode_error()
// {
// }

// void test_base64_decode_error()
// {
// }

int main()
{
    for (int i = 0; i < ARRAY_SIZE(test_vector); i++) {
        test_hex_encode(test_vector + i);
        test_hex_decode(test_vector + i);
        test_base64_encode(test_vector + i);
        test_base64_decode(test_vector + i);
    }

    // test_hex_decode_error();
    // test_base64_decode_error();

    printf("Success\n");
}
