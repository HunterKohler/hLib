#ifndef XOR_BREAKER
#define XOR_BREAKER

#include <iostream>
#include <fstream>
#include <string>

std::tuple<float,char> english_letter_frequency[] = {
    {.1202,'e'}, {0.0910,'t'}, {0.0812,'a'}, {0.0768,'o'}, {0.0731,'i'}, {0.0695,'n'},
    {.0628,'s'}, {0.0602,'r'}, {0.0592,'h'}, {0.0432,'d'}, {0.0398,'l'}, {0.0288,'u'},
    {.0271,'c'}, {0.0261,'m'}, {0.0230,'f'}, {0.0211,'y'}, {0.0209,'w'}, {0.0203,'g'},
    {.0182,'p'}, {0.0149,'b'}, {0.0111,'v'}, {0.0069,'k'}, {0.0017,'x'}, {0.0011,'q'},
    {.0010,'j'}, {.0007,'z'}
};

inline int set_bits(int);

float* char_frequency(const std::string&);

int hamming_distance(
    std::string::const_iterator first1, std::string::const_iterator last1,
    std::string::const_iterator first2, std::string::const_iterator last2
);

inline int hamming_distance(std::string&, std::string&);
inline int hamming_distance(int,int);

template <int,int,int>
int* guess_keysize(const std::string&);

#endif
