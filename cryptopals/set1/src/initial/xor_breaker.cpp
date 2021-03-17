#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

#include "base64_decode.hpp"
#include "xor_breaker.hpp"

#define INF (1 << 30)

using namespace std;

float* char_frequency(const string& str) {
    float* frequency = new float[256]();
    for(char c: str)
        frequency[c]++;
    for(int i = 0; i < 256; i++)
        frequency[i] /= str.length();
    return frequency;
}

template <int terms_to_compare = 5>
int average_frequency_distance(float* frequency) {
    tuple<float,char> frequency_list[256];
    for(int i = 0; i < 256; i++)
        frequency_list[i] = {frequency[i],i};
    sort(frequency_list,frequency_list+256,greater<tuple<float,char>>());
    int sum = 0;
    for(int i = 0; i < terms_to_compare; i++)
        sum += get<1>(english_letter_frequency[i]) - get<1>(frequency_list[i]);
    return sum / terms_to_compare;
}

string* make_partitions(const string& str, int n) {
    string* partitions = new string[n];
    for(int i = 0; i < str.length(); i++)
        partitions[i % n] += str[i];
    return partitions;
}

string merge_partitions(string* partitions, int n) {
    int length = 0;
    for(int i = 0; i < n; i++)
        length += partitions[i].length();
    string str(length,' ');
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < partitions[i].length();j++)
            str[j * n + i] = partitions[i][j];
    }
    return str;
}

string shift(string str, int n) {
    for(int i = 0; i < str.length(); i++)
        str[i] = (str[i] + n) % 256;
    return str;
}

int hamming_distance(const string& a, const string& b) {
    if(a.length() > b.length())
        return hamming_distance(b,a);

    int d = 0;
    for(int i = 0; i < a.length(); i++)
        d += hamming_distance(a[i],b[i]);
    for(int i = a.length(); i < b.length(); i++)
        d += set_bits(b[i]);

    return d;
}

inline int hamming_distance(int x, int y) {
    return set_bits(x^y);
}

inline int set_bits(int x) {
    int s = 0;
    while(x > 0) {
        s += 1 & x;
        x >>= 1;
    }
    return s;
}

template <int n_keysizes>
int* approximate_keysize(const string& str) {
    int lower = 2;
    int upper = min(50, (int) str.length() / 2);

    tuple<int,int> distances[upper-lower];  // <keysize, distance>
    for(int k = lower; k <= upper; k++) {
        distances[k] = {k,hamming_distance(str.substr(0,k),str.substr(k,k))};
    }

    sort(distances, distances+upper-lower,
        [](tuple<int,int> a, tuple<int,int> b) {
            return get<0>(b) * get<1>(a) < get<0>(a) * get<1>(b);
        });

    int* ret = new int[upper-lower];
    for(int i = 0; i < n_keysizes; i++)
        ret[i] = get<0>(distances[i]);
    return ret;
}

int main(int argc, char *argv[]) {
    if(argc == 1) {
        cerr << "usage: xor_breaker file\n";
        return 1;
    }

    ifstream ifs(argv[1]);
    string str((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    str = base64_decode(str);

    const int n_keysizes = 5;
    int* keysizes = approximate_keysize<n_keysizes>(str);
    string decoded[n_keysizes];
    string keys[n_keysizes];
    for(int i = 0; i < n_keysizes; i++) {
        string* partitions = make_partitions(str,keysizes[i]);
        for(int j = 0; j < keysizes[i]; j++) {
            float* frequency = char_frequency(partitions[j]);
            int distance = average_frequency_distance(frequency);
            partitions[j] = shift(partitions[j], distance);
            keys[i] += distance;
        }
        decoded[i] = merge_partitions(partitions,keysizes[i]);
    }
}
