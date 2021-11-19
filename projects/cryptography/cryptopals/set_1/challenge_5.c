#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <crypto/xor.h>
#include <crypto/encoding.h>

int main()
{
    const byte_t input[] = "Burning 'em, if you ain't quick and nimble\n"
                           "I go crazy when I hear a cymbal";
    const byte_t key[] = "ICE";
    const byte_t expected[] =
        "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272"
        "765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326"
        "302e27282f";

    size_t n = sizeof(input) - 1;
    size_t m = sizeof(key) - 1;

    byte_t out[1024];
    byte_t encoded[1024];

    memcpy(out, input, n);

    multi_xor_apply(out, n, key, m);
    hex_encode(out, n, encoded);

    assert(!memcmp(encoded, expected, sizeof(expected) - 1));
    printf("Success\n");
}