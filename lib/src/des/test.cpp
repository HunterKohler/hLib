#include <iostream>
#include <random>
#include <bitset>
#include <type_traits>
#include <concepts>
#include <string>
#include <bit>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "des.hpp"

typedef std::uint_fast64_t uint64;

uint64 bit_distr_64() {
    static std::mt19937_64 mt{(std::random_device{})()};
    static std::uniform_int_distribution<uint64> distr;
    return distr(mt);
}

int int_distr(int a, int b) {
    static std::mt19937 mt{(std::random_device{})()};
    static std::uniform_int_distribution<int> distr;
    return distr(mt,std::uniform_int_distribution<int>::param_type(a,b));
}

void bit_print_64(uint64 n) {std::cout << std::bitset<64>(n) << std::endl;}
int bit_count(uint64 n) {return std::bitset<64>(n).count();}
std::string bit_string(uint64 n) {return std::bitset<64>(n).to_string();}


TEST_CASE("PC-1") {
    uint64 key = bit_distr_64();
    uint64 k0 = DES::PC_1(key);

    CAPTURE(bit_string(key),bit_string(k0));

    // test for left-hand index
    REQUIRE((k0 & 0xFF) == 0);
    // test for correct bit count
    REQUIRE(bit_count(k0) <= bit_count(key));
    REQUIRE(bit_count(k0) >= (bit_count(key) - 8));
}

// TEST_CASE("Left shift") {
// }
//
// TEST_CASE("PC-2") {
//
// }

TEST_CASE("encrypt") {
    uint64 x = bit_distr_64();
    uint64 k_0 = bit_distr_64();

    CAPTURE(x,k_0);

    uint64 y = DES::encrypt(x,k_0);

    CAPTURE(y);

    REQUIRE(false);
}
