#include <iostream>
#include <fstream>
#include <string>
#include "base64_decode.hpp"
#include "xor_breaker.hpp"

using namespace std;

double* char_frequency(const string& str) {
    double* frequency = new double[256]();
    for(char c: str)
        frequency[c] += c;
    for(int i = 0; i < 256; i++)
        frequency[i] /= str.length();
    return frequency;
}

int hamming_distance(
    string::const_iterator first1, string::const_iterator last1,
    string::const_iterator first2, string::const_iterator last2
) {
    if(last1 - first1 > last2 - first2)
        return hamming_distance(first2,last2,first1,last1);

    int d = 0;
    while(first1 != last1)
        d += hamming_distance(*(first1++),*(first2++));
    while(first2 != last2)
        d += set_bits(*(first2++));

    return d;
}

inline int hamming_distance(const string& a, const string& b) {
    return hamming_distance(a.begin(),a.end(),b.begin(),b.end());
}

inline int hamming_distance(int x, int y) {
    return set_bits(x^y);
}

inline int set_bits(int x) {
    int s = x == 0;
    while(x > 0)
        s += 1 & (x >> 1);
    return s;
}

template <
    int number_of_guesses,
    int lower = 2, // [lower,upper)
    int upper = 25
> int* guess_keysize(const string& str) {
    int distances[upper - lower];
    for(int keysize = lower; keysize < upper; keysize++) {
        distances[keysize-lower] = hamming_distance(
            str.begin(),
            str.begin() + keysize,
            str.begin() + keysize,
            str.begin() + 2 * keysize
        );
    }

    tuple<double,int> normalized_distances[upper - lower];
    for(int keysize = lower; keysize < upper; keysize++) {
        normalized_distances[keysize-lower] = {distances[keysize-lower], keysize};
        sort(normalized_distances,normalized_distances + upper - lower);
    }

    int* guesses = new int[number_of_guesses];
    for(int i = 0; i < number_of_guesses; i++)
        guesses[i] = get<1>(normalized_distances[i]);
    return guesses;
}

int main(int argc, char *argv[]) {
    // ifstream ifs(argv[1]);
    cout << "enter";
    // string content((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    // content = base64_decode(content);

    cout << "exit";

    // cout << hamming_distance("this is a test","wokka wokka!!!");
}
