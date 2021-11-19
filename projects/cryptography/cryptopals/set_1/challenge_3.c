#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <crypto/encoding.h>
#include <crypto/xor.h>

int main()
{
    const byte_t input[] =
        "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    size_t n = sizeof(input) - 1;
    byte_t out[200];

    hex_decode(input, n, out);

    byte_t key = single_xor_key(out, n / 2);

    for (int i = 0; i < n / 2; i++)
        out[i] ^= key;

    assert(!memcmp(out, "Cooking MC's like a pound of bacon", n / 2));

    printf("Success\n");
}