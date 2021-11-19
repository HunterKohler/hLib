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
    for (int i = 0; i < n; i++)
        target[i] ^= key;
}

void multi_xor_apply(byte_t *restrict target, size_t n,
                     const byte_t *restrict key, size_t m)
{
    for (int i = 0; i < n; i++)
        target[i] ^= key[i % m];
}

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
        dist += __builtin_popcountll(((const long long *)a)[i] ^
                                     ((const long long *)b)[i]);

    for (int i = n % sizeof(long long); i < n; i++)
        dist +=
            __builtin_popcount(((const byte_t *)a)[i] ^ ((const byte_t *)b)[i]);

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