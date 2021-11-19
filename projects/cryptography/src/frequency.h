#ifndef CRYPTO_FREQUENCY_H_
#define CRYPTO_FREQUENCY_H_

#include "common.h"

#define NON_PRINTABLE_PENALTY 0.1

/*
 * Does not consider characters other than lowercase letters.
 */
extern const double en_letter_frequency[];

/*
 * Compares frequency error to table, lowercasing letters.
 */
double en_frequency_error(const byte_t *bytes, size_t n);

#endif
