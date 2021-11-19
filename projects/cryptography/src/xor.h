#ifndef CRYPTO_XOR_H_
#define CRYPTO_XOR_H_

#include "common.h"

/*
 * Expecting popcount builtin.
 */
static_assert(__has_builtin(__builtin_popcount) &&
              __has_builtin(__builtin_popcountl) &&
              __has_builtin(__builtin_popcountll));

byte_t single_xor_key(const byte_t *src, size_t n);
void single_xor_apply(byte_t *target, size_t n, byte_t key);
void multi_xor_apply(byte_t *restrict target, size_t n,
                     const byte_t *restrict key, size_t m);

size_t hamming_distance(const void *a, const void *b, size_t n);

#endif