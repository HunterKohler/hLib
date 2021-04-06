#include <iostream>
#include <cassert>
#include <cstdint>

namespace DES {

    // TODO determine best uint64
    typedef std::uint_fast64_t uint64;

    // Bits are taken as concatenations B1,B2,B3,...,Bn
    // most signifigant bit (MSB) 1, indexing
    constexpr int IP[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17,  9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };

    constexpr int IP_INV[64] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41,  9, 49, 17, 57, 25
    };

    constexpr int E[48] = {
        32,  1,  2,  3,  4,  5,
         4,  5,  6,  7,  8,  9,
         8,  9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32,  1
    };

    constexpr int P[32] = {
        16,  7, 20, 21,
        29, 12, 28, 17,
         1, 15, 23, 26,
         5, 18, 31, 10,
         2,  8, 24, 14,
        32, 27,  3,  9,
        19, 13, 30,  6,
        22, 11,  4, 25
    };

    constexpr int PC_1, = {
        57, 49, 41, 33, 25, 17,  9,
         1, 58, 50, 42, 34, 26, 18,
        10,  2, 59, 51, 43, 35, 27,
        19, 11,  3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
         7, 62, 54, 46, 38, 30, 22,
        14,  6, 61, 53, 45, 37, 29,
        21, 13,  5, 28, 20, 12,  4
    };

    constexpr int PC_2 = {
        14, 17, 11, 24,  1,  5,
         3, 28, 15,  6, 21, 10,
        23, 19, 12,  4, 26,  8,
        16,  7, 27, 20, 13,  2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };

    struct Sbox {
        int box[64];
        inline int operator[](int i) {
             return box[8 * (((i >> 4) & 2) + (i & 1)) + ((i >> 1) & 15)];
        inline int operator()(int i) {return (*this)[i];}

        inline int operator()(int i, int j) {return box[8*i+j];}
    }

    // S-box converted to constant lookup table
    constexpr int S[8][64] = {
        // TODO
    };

    constexpr int LS = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    // TODO consider reducing some uint64 and typeint it to std::uint64_t
    uint64 DES(uint64 k, uint64 x) {
        // TODO consider unroll pragma for all loops

        // PC-1(k)
        uint64 k_i[17] {};
        for(int i = 0; i < 56; i++) {
            k_i[0] += ((k >> (64 - PC_1[i])) & 1);
        }

        uint64 ls_1[17] = {k_i[0]};
        for(int i = 0; i < 16; i++) {
            // LS-1(C), LS-1(D)
            ls_1[i+1] = (((ls_1[i] << LS[i]) | (ls_1[i] >> (32 - LS[i]))) & 0xffffffff00000000ull)|
                        (((ls_1[i] << LS[i]) | (ls_1[i] >> (32 - LS[i]))) & 0x00000000ffffffffull);
            // PC-2
            for(int j = 0; j < 48; j++) {
                k_i[i+1] += ((ls_1[i+1] >> (56 - PC_2[j])) & 1);
            }
        }

        // IP(x)
        uint64 lr_i = 0;
        for(int i = 0; i < 64; i++) {
            lr_i += (((x >> (64 - IP[x])) & 1) << (63 - j));
        }

        for(int i = 1; i <= 16; i++) {
            // E(R_i)
            uint64 e = 0;
            for(int j = 0; j < 48; j++) {
                e += (((lr_i >> (32 - E[j])) & 1) << (47 - j));
            }

            // E(R_i) xor k_i
            e ^= k_i[i];

            // S(E(R_i) xor k_i)
            uint64 s;
            for(int j = 0; j < 8; j++) {
                s += (S[j][e >> (6*(7-j))] << (4*(7-j)));
            }

            // P
            uint64 p = 0;
            for(int j = 0; j < 32; j++) {
                p += (((s >> (32 - P[j])) & 1) << (31 - j));
            }

            // Passthrough store R_(i-1) for L_(i)
            uint64 r_i = (lr_i << 32);

            // l xor f
            lr_i = r_i + ((lr_i >> 32) ^ p);
        }

        // TODO determine if you cross back before IP^-1

        // IP^-1
        uint64 y = 0;
        for(int i = 0; i < 64; i++) {
            y += ((lr_i >> (64 - IP_INV[i])) & 1) << (63 - i));
        }

        return y;
    }
}
