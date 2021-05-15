#include <iostream>
#include <vector>
#include <tuple>

#include "./types/utils.h"
#include "./types/int_sequence.h"

using namespace hlib;

int main() {
    // bool b = is_volatile_v<volatile int>;
    // std::cout << b << std::end;

    std::cout << integral_sequence<int,1,2,3>() << std::endl
              << integral_sequence<int,1,2>() << std::endl
              << integral_sequence<int,1>() << std::endl
              << integral_sequence<int>() << std::endl
              << get<0>(integral_sequence<int,1,2,3>()) << std::endl
              << get<1>(integral_sequence<int,1,2,3>()) << std::endl
              << get<2>(integral_sequence<int,1,2,3>()) << std::endl
              << get<0>(integral_sequence<int,1,2,3>()) << std::endl
              << index_sequence<int,5>::type() << std::endl
              << index_sequence<int,4>::type() << std::endl
              << index_sequence<int,3>::type() << std::endl
              << index_sequence<int,2>::type() << std::endl
              << index_sequence<int,1>::type() << std::endl
              << index_sequence<int,0>::type() << std::endl
              << index_sequence<int>::type() << std::endl

    ;
}