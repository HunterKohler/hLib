#include <string.h>

#include "encoding.h"

const byte_t hex_charset[16] = "0123456789ABCDEF";

const byte_t hex_table[256] = {
    [0 ... 255] = 16, ['0'] = 0,  ['1'] = 1,  ['2'] = 2,  ['3'] = 3,
    ['4'] = 4,        ['5'] = 5,  ['6'] = 6,  ['7'] = 7,  ['8'] = 8,
    ['9'] = 9,        ['A'] = 10, ['B'] = 11, ['C'] = 12, ['D'] = 13,
    ['E'] = 14,       ['F'] = 15, ['a'] = 10, ['b'] = 11, ['c'] = 12,
    ['d'] = 13,       ['e'] = 14, ['f'] = 15
};

size_t hex_encode_size(size_t n)
{
    return n << 1;
}

size_t hex_decode_size(size_t n)
{
    return n >> 1;
}

void hex_encode(const byte_t *restrict src, size_t n, byte_t *restrict dest)
{
    for (int i = 0; i < n; i++) {
        *dest++ = hex_charset[src[i] >> 4];
        *dest++ = hex_charset[src[i] & 15];
    }
}

int hex_decode(const byte_t *restrict src, size_t n, byte_t *restrict dest)
{
    for (int i = 0; i + 1 < n; i += 2) {
        byte_t upper = hex_table[src[i]];
        byte_t lower = hex_table[src[i + 1]];

        if (upper > 15)
            return i;
        if (lower > 15)
            return i + 1;

        *dest++ = (upper << 4) | lower;
    }

    if ((n & 1) && (*dest++ = hex_table[src[n - 1]] << 4) > 240)
        return n - 1;

    return -1;
}

const byte_t base64_charset[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const byte_t base64_table[256] = {
    [0 ... 255] = 64, ['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,
    ['E'] = 4,        ['F'] = 5,  ['G'] = 6,  ['H'] = 7,  ['I'] = 8,
    ['J'] = 9,        ['K'] = 10, ['L'] = 11, ['M'] = 12, ['N'] = 13,
    ['O'] = 14,       ['P'] = 15, ['Q'] = 16, ['R'] = 17, ['S'] = 18,
    ['T'] = 19,       ['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23,
    ['Y'] = 24,       ['Z'] = 25, ['a'] = 26, ['b'] = 27, ['c'] = 28,
    ['d'] = 29,       ['e'] = 30, ['f'] = 31, ['g'] = 32, ['h'] = 33,
    ['i'] = 34,       ['j'] = 35, ['k'] = 36, ['l'] = 37, ['m'] = 38,
    ['n'] = 39,       ['o'] = 40, ['p'] = 41, ['q'] = 42, ['r'] = 43,
    ['s'] = 44,       ['t'] = 45, ['u'] = 46, ['v'] = 47, ['w'] = 48,
    ['x'] = 49,       ['y'] = 50, ['z'] = 51, ['0'] = 52, ['1'] = 53,
    ['2'] = 54,       ['3'] = 55, ['4'] = 56, ['5'] = 57, ['6'] = 58,
    ['7'] = 59,       ['8'] = 60, ['9'] = 61, ['+'] = 62, ['/'] = 63,
};

size_t base64_encode_size(size_t n)
{
    return ((n + 2) / 3) << 2;
}

size_t base64_decode_size(const byte_t *encoded, size_t n)
{
    if (!n)
        return 0;

    return (n >> 2) * 3 -
           (encoded ? (encoded[n - 1] == '=') + (encoded[n - 2] == '=') : 0);
}

void base64_encode(const byte_t *restrict src, size_t n, byte_t *restrict dest)
{
    for (const byte_t *end = src + n - 3; src <= end; src += 3) {
        *dest++ = base64_charset[src[0] >> 2];
        *dest++ = base64_charset[(src[0] & 0x03) << 4 | src[1] >> 4];
        *dest++ = base64_charset[(src[1] & 0x0F) << 2 | src[2] >> 6];
        *dest++ = base64_charset[src[2] & 0x3F];
    }

    switch (n % 3) {
    case 1:
        *dest++ = base64_charset[src[0] >> 2];
        *dest++ = base64_charset[(src[0] & 0x03) << 4];
        *dest++ = '=';
        *dest++ = '=';
        break;
    case 2:
        *dest++ = base64_charset[src[0] >> 2];
        *dest++ = base64_charset[(src[0] & 0x03) << 4 | src[1] >> 4];
        *dest++ = base64_charset[(src[1] & 0x0F) << 2];
        *dest++ = '=';
        break;
    }
}

int base64_decode(const byte_t *restrict src, size_t n, byte_t *restrict dest)
{
    if (n % 4)
        return n;
    else if (!n)
        return -1;

    int i = 0;
    int end = n - 4 * (src[n - 1] == '=');

    while (i < end) {
        byte_t a = base64_table[src[i++]];
        if (a >= 64)
            return i - 1;

        byte_t b = base64_table[src[i++]];
        if (b >= 64)
            return i - 1;

        byte_t c = base64_table[src[i++]];
        if (c >= 64)
            return i - 1;

        byte_t d = base64_table[src[i++]];
        if (d >= 64)
            return i - 1;

        *dest++ = a << 2 | b >> 4;
        *dest++ = b << 4 | c >> 2;
        *dest++ = c << 6 | d;
    }

    if (src[n - 2] == '=') {
        byte_t a = base64_table[src[i++]];
        if (a >= 64)
            return i - 1;

        byte_t b = base64_table[src[i++]];
        if (b >= 64)
            return i - 1;

        *dest++ = a << 2 | b >> 4;
    } else if (src[n - 1] == '=') {
        byte_t a = base64_table[src[i++]];
        if (a >= 64)
            return i - 1;

        byte_t b = base64_table[src[i++]];
        if (b >= 64)
            return i - 1;

        byte_t c = base64_table[src[i++]];
        if (c >= 64)
            return i - 1;

        *dest++ = a << 2 | b >> 4;
        *dest++ = b << 4 | c >> 2;
    }

    return -1;
}