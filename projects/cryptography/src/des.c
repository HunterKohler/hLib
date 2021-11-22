#include "des.h"

/*
 * `width` is the output width of the permutation.
 */
static inline uint64_t permute_partial_64(uint64_t input, size_t width,
                                          const uint8_t *permutation)
{
    uint64_t ret = 0;

    for (int i = 0; i < width; i++)
        ret |= ((input >> permutation[i]) & 1) << (width - 1 - i);

    return ret;
}

uint64_t des(uint64_t input, uint64_t key, bool encrypt)
{
    uint64_t ks[16];
    uint64_t lr = permute_partial_64(input, 64, des_table_IP);

    des_key_schedule(key, ks);

    for (int i = 0; i < 16; i++) {
        uint64_t out = des_f(lr & ((1ULL << 32) - 1), ks[encrypt ? i : 15 - i]);
        lr = lr << 32 | ((lr >> 32) ^ out);
    }

    lr = permute_partial_64(lr, 64, des_table_IP_inv);
    return lr;
}

uint64_t des_f(uint64_t r, uint64_t k)
{
    r = permute_partial_64(r, 48, des_table_E);
    r ^= k;

    uint64_t ret = 0;

    for (int i = 0; i < 8; i++) {
        ret |= des_table_S[i][(r >> (42 - i * 6)) & 0x3F] << (28 - i * 4);
    }

    ret = permute_partial_64(ret, 32, des_table_P);
    return ret;
}

uint64_t *des_key_schedule(uint64_t key, uint64_t *keylist)
{
    uint64_t k = des_PC_1(key);
    for (int i = 0; i < 16; i++) {
        k = des_LS(k, i);
        keylist[i] = des_PC_2(k);
    }
    return keylist;
}

uint64_t des_IP(uint64_t x)
{
    return permute_partial_64(x, 64, des_table_IP);
}

uint64_t des_IP_inv(uint64_t x)
{
    return permute_partial_64(x, 64, des_table_IP_inv);
}

uint64_t des_E(uint64_t x)
{
    return permute_partial_64(x, 48, des_table_E);
}

uint64_t des_S(uint64_t x, size_t n)
{
    return des_table_S[n][(x >> (42 - 6 * n)) & 0x3F];
}

uint64_t des_PC_1(uint64_t x)
{
    return permute_partial_64(x, 56, des_table_PC_1);
}

uint64_t des_PC_2(uint64_t x)
{
    return permute_partial_64(x, 48, des_table_PC_2);
}

uint64_t des_LS(uint64_t k, size_t n)
{
    uint64_t c = k >> 28 & 0xFFFFFFF;
    uint64_t d = k & 0xFFFFFFF;

    c = (c << des_table_LS[n] | c >> (28 - des_table_LS[n])) & 0xFFFFFFF;
    d = (d << des_table_LS[n] | d >> (28 - des_table_LS[n])) & 0xFFFFFFF;

    return c << 28 | d;
}

uint64_t des_P(uint64_t x)
{
    return permute_partial_64(x, 32, des_table_P);
}

const byte_t des_table_IP[] = {
    6, 14, 22, 30, 38, 46, 54, 62, 4, 12, 20, 28, 36, 44, 52, 60,
    2, 10, 18, 26, 34, 42, 50, 58, 0, 8,  16, 24, 32, 40, 48, 56,
    7, 15, 23, 31, 39, 47, 55, 63, 5, 13, 21, 29, 37, 45, 53, 61,
    3, 11, 19, 27, 35, 43, 51, 59, 1, 9,  17, 25, 33, 41, 49, 57,
};

const byte_t des_table_IP_inv[] = {
    24, 56, 16, 48, 8,  40, 0, 32, 25, 57, 17, 49, 9,  41, 1, 33,
    26, 58, 18, 50, 10, 42, 2, 34, 27, 59, 19, 51, 11, 43, 3, 35,
    28, 60, 20, 52, 12, 44, 4, 36, 29, 61, 21, 53, 13, 45, 5, 37,
    30, 62, 22, 54, 14, 46, 6, 38, 31, 63, 23, 55, 15, 47, 7, 39,
};

const byte_t des_table_E[] = {
    0,  31, 30, 29, 28, 27, 28, 27, 26, 25, 24, 23, 24, 23, 22, 21,
    20, 19, 20, 19, 18, 17, 16, 15, 16, 15, 14, 13, 12, 11, 12, 11,
    10, 9,  8,  7,  8,  7,  6,  5,  4,  3,  4,  3,  2,  1,  0,  31,
};

const byte_t des_table_S[8][64] = {
    {
        14, 0,  4,  15, 13, 7,  1,  4,  2,  14, 15, 2, 11, 13, 8,  1,
        3,  10, 10, 6,  6,  12, 12, 11, 5,  9,  9,  5, 0,  3,  7,  8,
        4,  15, 1,  12, 14, 8,  8,  2,  13, 4,  6,  9, 2,  1,  11, 7,
        15, 5,  12, 11, 9,  3,  7,  14, 3,  10, 10, 0, 5,  6,  0,  13,
    },
    {
        15, 3,  1,  13, 8,  4,  14, 7,  6,  15, 11, 2,  3,  8,  4,  14,
        9,  12, 7,  0,  2,  1,  13, 10, 12, 6,  0,  9,  5,  11, 10, 5,
        0,  13, 14, 8,  7,  10, 11, 1,  10, 3,  4,  15, 13, 4,  1,  2,
        5,  11, 8,  6,  12, 7,  6,  12, 9,  0,  3,  5,  2,  14, 15, 9,
    },
    {
        10, 13, 0,  7,  9,  0,  14, 9,  6,  3,  3,  4,  15, 6,  5, 10,
        1,  2,  13, 8,  12, 5,  7,  14, 11, 12, 4,  11, 2,  15, 8, 1,
        13, 1,  6,  10, 4,  13, 9,  0,  8,  6,  15, 9,  3,  8,  0, 7,
        11, 4,  1,  15, 2,  14, 12, 3,  5,  11, 10, 5,  14, 2,  7, 12,
    },
    {
        7,  13, 13, 8,  14, 11, 3,  5,  0,  6,  6,  15, 9, 0,  10, 3,
        1,  4,  2,  7,  8,  2,  5,  12, 11, 1,  12, 10, 4, 14, 15, 9,
        10, 3,  6,  15, 9,  0,  0,  6,  12, 10, 11, 1,  7, 13, 13, 8,
        15, 9,  1,  4,  3,  5,  14, 11, 5,  12, 2,  7,  8, 2,  4,  14,
    },
    {
        2,  14, 12, 11, 4,  2,  1,  12, 7,  4,  10, 7,  11, 13, 6,  1,
        8,  5,  5,  0,  3,  15, 15, 10, 13, 3,  0,  9,  14, 8,  9,  6,
        4,  11, 2,  8,  1,  12, 11, 7,  10, 1,  13, 14, 7,  2,  8,  13,
        15, 6,  9,  15, 12, 0,  5,  9,  6,  10, 3,  4,  0,  5,  14, 3,
    },
    {
        12, 10, 1,  15, 10, 4,  15, 2,  9,  7, 2,  12, 6,  9,  8,  5,
        0,  6,  13, 1,  3,  13, 4,  14, 14, 0, 7,  11, 5,  3,  11, 8,
        9,  4,  14, 3,  15, 2,  5,  12, 2,  9, 8,  5,  12, 15, 3,  10,
        7,  11, 0,  14, 4,  1,  10, 7,  1,  6, 13, 0,  11, 8,  6,  13,
    },
    {
        4,  13, 11, 0,  2,  11, 14, 7,  15, 4,  0,  9,  8, 1,  13, 10,
        3,  14, 12, 3,  9,  5,  7,  12, 5,  2,  10, 15, 6, 8,  1,  6,
        1,  6,  4,  11, 11, 13, 13, 8,  12, 1,  3,  4,  7, 10, 14, 7,
        10, 9,  15, 5,  6,  0,  8,  15, 0,  14, 5,  2,  9, 3,  2,  12,
    },
    {
        13, 1,  2,  15, 8,  13, 4,  8,  6,  10, 15, 3,  11, 7, 1, 4,
        10, 12, 9,  5,  3,  6,  14, 11, 5,  0,  0,  14, 12, 9, 7, 2,
        7,  2,  11, 1,  4,  14, 1,  7,  9,  4,  12, 10, 14, 8, 2, 13,
        0,  15, 6,  12, 10, 9,  13, 0,  15, 3,  3,  5,  5,  6, 8, 11,
    }
};

const byte_t des_table_P[] = {
    16, 25, 12, 11, 3, 20, 4,  15, 31, 17, 9, 6,  27, 14, 1,  22,
    30, 24, 8,  18, 0, 5,  29, 23, 13, 19, 2, 26, 10, 21, 28, 7,
};

const byte_t des_table_PC_1[] = {
    7,  15, 23, 31, 39, 47, 55, 63, 6,  14, 22, 30, 38, 46, 54, 62, 5,  13, 21,
    29, 37, 45, 53, 61, 4,  12, 20, 28, 1,  9,  17, 25, 33, 41, 49, 57, 2,  10,
    18, 26, 34, 42, 50, 58, 3,  11, 19, 27, 35, 43, 51, 59, 36, 44, 52, 60,
};

const byte_t des_table_PC_2[] = {
    42, 39, 45, 32, 55, 51, 53, 28, 41, 50, 35, 46, 33, 37, 44, 52,
    30, 48, 40, 49, 29, 36, 43, 54, 15, 4,  25, 19, 9,  1,  26, 16,
    5,  11, 23, 8,  12, 7,  17, 0,  22, 3,  10, 14, 6,  20, 27, 24,
};

const byte_t des_table_LS[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};
