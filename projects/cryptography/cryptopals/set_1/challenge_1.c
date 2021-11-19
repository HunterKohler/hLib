#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <crypto/encoding.h>

int main()
{
    const byte_t hex[] =
        "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736"
        "f6e6f7573206d757368726f6f6d";

    const byte_t base64[] =
        "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

    byte_t hex_out[100] = { 0 };
    byte_t base64_out[100] = { 0 };

    hex_decode(hex, sizeof(hex) - 1, hex_out);
    base64_encode(hex_out, (sizeof(hex) - 1) / 2, base64_out);

    assert(!memcmp(base64_out, base64, sizeof(base64) - 1));

    printf("Success\n");
}
