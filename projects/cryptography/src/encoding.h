#ifndef CRYPTO_ENCODING_H_
#define CRYPTO_ENCODING_H_

#include "common.h"

size_t hex_len(size_t n);

void hex_encode(const byte_t *restrict src, size_t n, byte_t *restrict dest);
int hex_decode(const byte_t *restrict src, size_t n, byte_t *restrict dest);

size_t base64_len(size_t n);

void base64_encode(const byte_t *restrict src, size_t n, byte_t *restrict dest);
int base64_decode(const byte_t *restrict src, size_t n, byte_t *restrict dest);

#endif