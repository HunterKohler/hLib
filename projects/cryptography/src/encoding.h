#ifndef CRYPTO_ENCODING_H_
#define CRYPTO_ENCODING_H_

#include "common.h"

size_t hex_decode_size(size_t n);
size_t hex_encode_size(size_t n);

void hex_encode(const byte_t *restrict src, size_t n, byte_t *restrict dest);
int hex_decode(const byte_t *restrict src, size_t n, byte_t *restrict dest);

size_t base64_encode_size(size_t n);

/*
 * Gives decoded length of base64 buffer. If encoeded is `NULL`, the maximum
 * decoded size is given.
 */
size_t base64_decode_size(const byte_t *encoded, size_t n);

void base64_encode(const byte_t *restrict src, size_t n, byte_t *restrict dest);
int base64_decode(const byte_t *restrict src, size_t n, byte_t *restrict dest);

#endif