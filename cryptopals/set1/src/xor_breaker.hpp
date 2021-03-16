#ifndef XOR_BREAKER
#define XOR_BREAKER

#include <iostream>
#include <fstream>
#include <string>

inline int set_bits(int);

double* char_frequency(const std::string&);

int hamming_distance(
    std::string::const_iterator first1, std::string::const_iterator last1,
    std::string::const_iterator first2, std::string::const_iterator last2
);

inline int hamming_distance(std::string&, std::string&);
inline int hamming_distance(int,int);

template <int,int,int>
int* guess_keysize(const std::string&);

#endif
