#include "../src/des.c"
// #include "../src/encoding.c"

#include <assert.h>
#include <stdio.h>
#include <stdint.h>

void test_des_LS()
{
    uint64_t k = 0x93C0EEB98CEF5C;

    const uint64_t expected[] = {
        0x2781DD7319DEB9, 0x4F03BAE633BD72, 0x3C0EEB98CEF5C9, 0xF03BAE433BD726,
        0xC0EEB93CEF5C98, 0x03BAE4F3BD7263, 0x0EEB93CEF5C98C, 0x3BAE4F0BD72633,
        0x775C9E07AE4C67, 0xDD72781EB9319D, 0x75C9E07AE4C677, 0xD72781DB9319DE,
        0x5C9E077E4C677A, 0x72781DD9319DEB, 0xC9E07754C677AE, 0x93C0EEB98CEF5C,
    };

    for (int i = 0; i < 16; i++) {
        k = des_LS(k, i);
        assert(k == expected[i]);
    }
}

void test_des_PC_1()
{
    uint64_t k = 0xE7A1926FFE75BCA3;
    uint64_t expected = 0x00D739FB79D79584;

    k = des_PC_1(k);

    assert(k == expected);
}

void test_des_PC_2()
{
    uint64_t k = 0xD4A5D5F058FFD2;
    uint64_t expected = 0x00F941ADDC5CBC;

    k = des_PC_2(k);

    assert(k == expected);
}

void test_des_P()
{
    uint64_t x = 0x71BEBA57;
    uint64_t expected = 0x3772DBE6;

    x = des_P(x);

    assert(x == expected);
}

void test_des_E()
{
    uint64_t x = 0x0001AC31B3E;
    uint64_t expected = 0xF56068F69FC;

    x = des_E(x);

    assert(x == expected);
}

void test_des_IP()
{
    uint64_t x = 0x5E9D0E69E9093B5D;
    uint64_t expected = 0x99C387FA1258FF45;

    x = des_IP(x);

    assert(x == expected);
}

void test_des_IP_inv()
{
    uint64_t x = 0x5E9D0E69E9093B5D;
    uint64_t expected = 0xBB4C56FF5A89C390;

    x = des_IP_inv(x);

    assert(x == expected);
}

int main()
{
    test_des_LS();
    test_des_PC_1();
    test_des_PC_2();
    test_des_P();
    test_des_E();
    test_des_IP();
    test_des_IP_inv();
}
