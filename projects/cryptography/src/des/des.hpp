#ifndef LIBRARY_DES_H_
#define LIBRARY_DES_H_

#include <mutex>
#include <thread>
#include <iostream>
#include <cstdint>
#include <bitset>
#include <functional>
#include <utility>
#include <algorithm>
#include <cassert>
#include <string>
#include <concepts>
#include <exception>


#define bit_string_32(x) std::bitset<32>(x).to_string()
#define bit_string_64(x) std::bitset<64>(x).to_string()

// Bits are taken as concatenations B1,B2,B3,...,Bn
// most signifigant bit (MSB) 1, indexing
namespace DES {
    // TODO determine best uint64
    typedef unsigned long long uint64;
    typedef std::size_t size_t;

    template <size_t N>
        requires (N > 0)
    class Table {
      protected:
        uint64 table[N];

        constexpr Table(const std::initializer_list<int>& il) {
            if(il.size() != N) table[-1] = -1; // TODO TEST MAKESHIFT COMPILE TIME ASSERT
            int i = 0;
            for(int j: il) {
                table[i++] = j;
            }
        }

      public:
        size_t size() const {return N;}

        friend std::ostream& operator<<(std::ostream& os, const Table<N>& t) {
            os << "{";
            for(int i = 0; i < N; i++)
                os << t.table[i] << ",";
            return os << "\b}";
        }
    };

    template <size_t N>
    class LeftShift : public Table<N> {
      public:
        constexpr LeftShift(const std::initializer_list<int>& il): Table<N>(il) {}
        uint64 operator()(size_t i, uint64 x) const { // 1-indexed for round i
            if(this->table[i-1] == 1) { // TODO compact expression
                return ((x & 0xc000000000000000ull) >> 30) |
                       ((x & 0x3fffffff00000000ull) <<  2) |
                       ((x & 0x00000000c0000000ull) >> 30) |
                       ((x & 0x000000003fffffffull) << 2);
            } else {
                return ((x & 0x8000000000000000ull) >> 31) |
                       ((x & 0x7fffffff00000000ull) <<  1) |
                       ((x & 0x0000000080000000ull) >> 31) |
                       ((x & 0x000000007fffffffull) << 1);
            }
        }
    };

    template <size_t N>
    class Permutation : public Table<N> {
      public:
        constexpr Permutation(const std::initializer_list<int>& il): Table<N>(il) {}
        uint64 operator()(uint64 x) const {
            uint64 y = 0;
            for(int i = 1; i <= N; i++) {
                y += (((x >> (64 - this->table[i-1])) & 1)) << (64 - i);
            }
            return y;
        }
    };

    template <size_t N>
    class SBox : public Table<N> {
      public:
        constexpr SBox(const std::initializer_list<int>& il): Table<N>(il) {
            if(il.size() != N) this->table[-1] = -1; // TODO TEST MAKESHIFT COMPILE TIME ASSERT

            int i = 0;
            for(int j: il) {
                this->table[((i << 1) & 30) | (i & 32) | ((i >> 4) & 1)] = j;
            }
        }

        uint64 operator()(uint64 i) const {
            return this->table[i];
        }
    };

    constexpr Permutation<64> IP {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17,  9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };

    constexpr Permutation<64> IP_INV {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41,  9, 49, 17, 57, 25
    };

    constexpr Permutation<48> E = {
        32,  1,  2,  3,  4,  5,
         4,  5,  6,  7,  8,  9,
         8,  9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32,  1
    };

    constexpr Permutation<32> P = {
        16,  7, 20, 21,
        29, 12, 28, 17,
         1, 15, 23, 26,
         5, 18, 31, 10,
         2,  8, 24, 14,
        32, 27,  3,  9,
        19, 13, 30,  6,
        22, 11,  4, 25
    };

    constexpr Permutation<56> PC_1 {
        57, 49, 41, 33, 25, 17,  9,
         1, 58, 50, 42, 34, 26, 18,
        10,  2, 59, 51, 43, 35, 27,
        19, 11,  3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
         7, 62, 54, 46, 38, 30, 22,
        14,  6, 61, 53, 45, 37, 29,
        21, 13,  5, 28, 20, 12,  4
    };

    constexpr Permutation<48> PC_2 = {
        14, 17, 11, 24,  1,  5,
         3, 28, 15,  6, 21, 10,
        23, 19, 12,  4, 26,  8,
        16,  7, 27, 20, 13,  2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };

    constexpr SBox<64> S1 = {
        14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
         0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
         4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
    };

    constexpr SBox<64> S2 = {
        15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
         3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
         0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
        13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
    };

    constexpr SBox<64> S3 = {
        10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
        13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
        13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
         1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
    };

    constexpr SBox<64> S4 = {
         7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
        13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
        10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
         3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
    };

    constexpr SBox<64> S5 = {
         2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
        14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
         4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
        11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
    };

    constexpr SBox<64> S6 = {
        12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
        10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
         9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
         4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
    };

    constexpr SBox<64> S7 = {
         4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
        13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
         1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
         6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
    };

    constexpr SBox<64> S8 = {
        13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
         1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
         7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
         2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
    };

    constexpr LeftShift<16> LS = {
        1, 1, 2, 2, 2, 2, 2, 2, // number of bits to shift
        1, 2, 2, 2, 2, 2, 2, 1
    };

    uint64 f(uint64 L, uint64 k) {
        std::cout << "f_E   = " << bit_string_64(E(L)) << std::endl;
        L = E(L) ^ k; // TO MAKE LEFT JUSTIFIED INPUTS FOR SI()
        std::cout << "f_E^k = " << bit_string_64(L) << std::endl;


        L = (S1((L >> 58) & 63) << 60) |
            (S2((L >> 52) & 63) << 56) |
            (S3((L >> 46) & 63) << 52) |
            (S4((L >> 40) & 63) << 48) |
            (S5((L >> 34) & 63) << 44) |
            (S6((L >> 28) & 63) << 40) |
            (S7((L >> 22) & 63) << 36) |
            (S8((L >> 16) & 63) << 32);

        std::cout << "f_O   = " << bit_string_64(L)  << std::endl;
        std::cout << "f_P   = " << bit_string_64(P(L)) << std::endl;
        return P(L);
    }

    // 1-indexed for rounds
    uint64 encrypt(uint64 x, uint64 k_0) {
        printf("encrypt(x,k_0)\n\tx = %llu\n\tk_0 = %llu\n",x,k_0);

        uint64 k[17] {k_0};

        for(int i = 1; i <= 16; i++) {
            k[i] = LS(i,k[i-1]);
            k[i-1] = PC_2(k[i-1]);
        }

        for(int i = 1; i <= 16; i++) {
            printf("\tkey %s%d = %s\n", i < 10 ? " " : "", i,bit_string_64(k[i]));
        }

        x = IP(x);

        std::cout << "\tL0  = " << bit_string_32(x >> 32) << ", R0  = " <<  bit_string_32(x) << std::endl;
        for(int i = 1; i <= 16; i++) {
            x = (x << 32) | ((f((x << 32),k[i]) ^ (x & 0xFFFFFFFF00000000ull)) >> 32);

            std::cout << "\tL" << i << (i < 10 ? " " : "") << " = " << bit_string_32(x >> 32)
                      << ", R" << i << (i < 10 ? " " : "") << " = " << bit_string_32(x) << std::endl;
        }

        return IP_INV(x);
    }

    void thread_handler(
        std::string& str,
        // std::mutex str_m&,
        int& index,
        std::mutex& index_m,
        uint64 k_0
    ) {
        while(true) {
            int i;
            index_m.lock();
            if(index < str.length()) {
                i = index;
                index += 8;
            } else {
                index_m.unlock();
                return;
            }
            index_m.unlock();

            uint64 x = 0;
            int max_j = std::min<std::size_t>(str.length() - i, 8);
            for(int j = 1; j <= max_j; j++) {
                x |= (str[i + j] << (64 - (8 * j)));
            }

            x = encrypt(x,k_0);
            for(int j = 1; j <= max_j; j++) {
                str[i + j] = (x >> (64 - (8 * j))) & 0xFF;
            }
        }
    }

    std::string encrypt(std::string str, uint64 k_0) {
        int max_threads = std::thread::hardware_concurrency();
        if(max_threads <= 0) {
            throw std::runtime_error("Could not determine available concurrency resources.");
        }

        int index = 0;
        std::mutex str_m,index_m;

        std::thread *threads = new std::thread[max_threads];
        for(int i = 0; i < max_threads; i++) {
            threads[i] = std::thread(
                thread_handler,
                std::ref(str),
                // std::ref(str_m),
                std::ref(index),
                std::ref(index_m),
                k_0
            );
        }

        for(int i = 0; i < max_threads; i++) {
            threads[i].join();
        }

        delete[] threads;
        return str;
    }
}

#endif
