#include <string.h>

#include "common.h"
#include "encoding.h"

size_t hex_len(size_t n)
{
    return n << 1;
}

const char hex_charset[] = "0123456789ABCDEF";

char *hex_encode(char *restrict dest, const char *restrict src, size_t n)
{
    for (int i = 0; i < n; i++) {
        dest[(i << 1)] = hex_charset[src[i] >> 4];
        dest[(i << 1) + 1] = hex_charset[src[i] & 15];
    }

    return dest;
}

char *hex_decode(char *restrict dest, const char *restrict src, size_t n)
{
    for (int i = 0; i < n; i++) {
        dest[i >> 1] = (src[i] & 15) | (src[i + 1] << 4);
    }

    return dest;
}

size_t base64_len(size_t n)
{
    return ((n + 2) / 3) << 2;
}

const char base64_charset[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *base64_encode(char *restrict dest, const char *restrict src, size_t n)
{
    char *head = dest;
    const char *it = src;
    const char *end = src + n - 3;

    for (; it < end; it += 3) {
        *head++ = base64_charset[it[0] >> 2];
        *head++ = base64_charset[((it[0] & 0x03) << 4) | (it[1] >> 4)];
        *head++ = base64_charset[((it[1] & 0x0F) << 2) | (it[2] >> 6)];
        *head++ = base64_charset[it[2] & 0x3F];
    }

    switch (n & 3) {
    case 1:
        *head++ = base64_charset[it[0] >> 2];
        *head++ = base64_charset[it[0] & 0x03];
        *head++ = '=';
        *head++ = '=';
        break;
    case 2:
        *head++ = base64_charset[it[0] >> 2];
        *head++ = base64_charset[((it[0] & 0x03) << 4) | (it[1] >> 4)];
        *head++ = base64_charset[((it[1] & 0x0F) << 2)];
        *head++ = '=';
        break;
    }

    return dest;
}

char *base64_decode(char *restrict dest, const char *restrict src, size_t n)
{}
