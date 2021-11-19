#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <crypto/encoding.h>
#include <crypto/xor.h>

int main()
{
    const byte_t hex[] = "1c0111001f010100061a024b53535009181c";
    const byte_t key[] = "686974207468652062756c6c277320657965";
    const byte_t expected[] = "746865206b696420646f6e277420706c6179";

    size_t n = sizeof(hex) - 1;

    byte_t x[100];
    byte_t y[100];
    byte_t xor_out[100];
    byte_t encoded[100];

    hex_decode(hex, n, x);
    hex_decode(key, n, y);

    for (int i = 0; i < n; i++)
        xor_out[i] = x[i] ^ y[i];

    hex_encode(xor_out, n, encoded);
    assert(!memcmp(expected, encoded, n));

    printf("Success\n");
}