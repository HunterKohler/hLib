#include <string.h>
#include <math.h>
#include <ctype.h>

#include "xor.h"
#include "frequency.h"

byte_t single_xor_key(const byte_t *src, size_t n)
{
    double min_error = INFINITY;
    byte_t min_key = 0;

    for (int key = 0; key < 256; key++) {
        int count[256] = { 0 };
        double error = 0;

        for (int i = 0; i < n; i++)
            count[src[i] ^ key]++;

        for (int i = 0; i < 256; i++)
            error += fabs(en_letter_frequency[i] - (((double)count[i]) / n));

        if (error < min_error) {
            min_error = error;
            min_key = key;
        }
    }

    return min_key;
}

void single_xor_apply(byte_t *target, size_t n, byte_t key)
{
    multi_xor_apply(target, n, &key, 1);
}

void multi_xor_apply(byte_t *restrict target, size_t n,
                     const byte_t *restrict key, size_t m)
{
    for (int i = 0; i < n; i++)
        target[i] ^= key[i % m];
}

double multi_xor_keysize_dist(const byte_t *src, size_t n, size_t keysize)
{
    if (!n || !keysize || !(n / keysize))
        return INFINITY;

    size_t blocks = n / keysize;
    double distance = 0;

    for (int i = 0; i < n / keysize; i++) {
        for (int j = i + 1; j < n / keysize; j++) {
            distance +=
                hamming_distance(src + i * keysize, src + j * keysize, keysize);
        }
    }

    return 2 * distance / (blocks * (blocks - 1) * keysize);
}

#include <stdio.h>

#define MIN_KEYSIZE(n) 2
#define MAX_KEYSIZE(n) ((n) / 25)

/*
 * Get key of multibyte xor.
 */
size_t multi_xor_key(const byte_t *src, size_t n, byte_t *dest)
{
    size_t keysize = 0;
    double keysize_dist = INFINITY;

    for (int i = MIN_KEYSIZE(n); i < MAX_KEYSIZE(n); i++) {
        double dist = multi_xor_keysize_dist(src, n, i);

        if (dist < keysize_dist) {
            keysize = i;
            keysize_dist = dist;
        }
    }

    for (int i = 0; i < keysize; i++) {
        double min_err = INFINITY;

        for (int key = 0; key < 256; key++) {
            int count[256] = { 0 };
            double error = 0;

            for (int j = i; j < n; j += keysize)
                count[src[j] ^ key]++;

            for (int j = 0; j < 256; j++)
                error += fabs(en_letter_frequency[j] -
                              keysize * ((double)count[j]) / n);

            if (error < min_err) {
                min_err = error;
                dest[i] = key;
            }
        }
    }

    return keysize;
}

/*
 * Take hamming distance (popcount) on arbitrary `n` bytes.
 */
size_t hamming_distance(const void *a, const void *b, size_t n)
{
    /*
     * Casting to `unsigned long long` initially becuase it massivly reduces
     * constant complexity when larger popcount instructions are available.
     */
    size_t dist = 0;
    size_t i = 0;

    for (; i + sizeof(unsigned long long) < n; i += sizeof(unsigned long long))
        dist += __builtin_popcountll(*((const unsigned long long *)(a + i)) ^
                                     *((const unsigned long long *)(b + i)));

    for (; i < n; i++)
        dist += __builtin_popcount(*((const byte_t *)(a + i)) ^
                                   *((const byte_t *)(b + i)));

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