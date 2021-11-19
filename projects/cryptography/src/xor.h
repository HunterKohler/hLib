#ifndef CRYPTO_XOR_H_
#define CRYPTO_XOR_H_

#include <string.h>
#include <math.h>

#include "xor.h"
#include "frequency.h"
#include "common.h"

void single_xor_error(double error[256], const uint8_t *src, size_t n)
{
    for (int key = 0; key < 256; key++) {
        double count[256] = { 0 };
        error[key] = 0;

        for (int i = 0; i < n; i++)
            count[src[i] ^ key]++;

        for (int i = 0; i < 256; i++)
            error += fabs(letter_frequency[i] - (count[i] / n));
    }
}

uint8_t single_xor_key(const uint8_t *src, size_t n)
{
    int key = 0;
    double error[256];

    single_xor_error(error, src, n);

    for (int i = 0; i < 256; i++) {
        if (error[i] < error[key])
            key = i;
    }

    return key;
}

void single_xor_apply(uint8_t *restrict dest, const uint8_t *restrict src,
                      size_t n, uint8_t key)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i] ^ key;
}

void single_xor_decode(uint8_t *restrict dest, const uint8_t *restrict src,
                       size_t n)
{
    return single_xor_apply(dest, src, n, single_xor_key(dest, src, n));
}

void multi_xor_apply(uint8_t *restrict dest, const uint8_t *restrict src,
                     size_t size, const uint8_t *key, size_t keysize)
{
    for (int i = 0; i < size; i++)
        dest[i] = src[i] ^ key[i % keysize];
}

void multi_xor_decode()
{}

/*
 * Expecting popcount builtin.
 */
static_assert(__has_builtin(__builtin_popcount) &&
              __has_builtin(__builtin_popcountl) &&
              __has_builtin(__builtin_popcountll));

/*
 * Take hamming distance (popcount) on arbitrary `n` bytes.
 */
size_t hamming_distance(const void *a, const void *b, size_t n)
{
    /*
     * Casting to `long long` initially becuase it massivly reduces constant
     * complexity when larger popcount instructions are available.
     */
    size_t dist = 0;

    for (int i = 0; i < n / sizeof(long long); i++)
        dist += __builting_popcountll(((const long long *)a)[i] ^
                                      ((const long long *)b)[i]);

    for (int i = n % sizeof(long long); i < n; i++)
        dist += __buildint_popcount(((const uint8_t *)a)[i] ^
                                    ((const uint8_t *)b)[i]);

    return dist;
}

// std::tuple<std::string, std::string, float> decode(const std::string &str)
// {
//     std::vector<Keysize> keysizes;

//     for (int i = Keysize::MIN; i < Keysize::MAX; i++) {
//         keysizes.emplace_back(i, str);
//     }

//     std::sort(keysizes.begin(), keysizes.end());

//     int min_error_index;
//     float min_error = 1e10;
//     std::string min_key;
//     std::string min_message;
//     for (int i = 0; i < Keysize::CHECK; i++) {
//         std::string key;
//         key.resize(keysizes[i].size());

//         for (int j = 0; j < keysizes[i].size(); j++) {
//             std::string block;
//             for (int k = j; k < str.length(); k += key.size())
//                 block += str[k];

//             std::tie(key[j], std::ignore, std::ignore) =
//                 single_character_xor::decode(block);
//         }

//         std::string message = apply(str, key);
//         float error = english::frequency_error(message);

//         if (error < min_error) {
//             min_error = error;
//             min_key = key;
//             min_message = apply(str, key);
//         }
//     }

//     return { min_key, min_message, min_error };
// }

// // ===================== KEYSIZE CLASS ===========================
// Keysize::Keysize(int _s, const std::string &str) : _size{ _s }
// {
//     _norm_distance = 0;
//     for (int i = 0, b1 = 0, b2 = 0; i < BLOCKS; i++) {
//         bool first = true;
//         while (first || b1 == b2) {
//             first = false;
//             b1 = random_int(str.length() / _size);
//             b2 = random_int(str.length() / _size);
//         }

//         _norm_distance +=
//             hamming_distance(std::string_view(&str[_size * b1], _size),
//                              std::string_view(&str[_size * b2], _size));
//     }

//     _norm_distance /= _size;
// }

// int Keysize::size() const
// {
//     return _size;
// }
// float Keysize::norm_distance() const
// {
//     return _norm_distance;
// }
// bool Keysize::operator<(const Keysize &k) const
// {
//     return norm_distance() < k.norm_distance();
// }
// // ============================================================

// } // namespace string_xor

#endif