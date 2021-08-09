#include <string>
#include <fstream>
#include <random>
#include "utils.h"

int hamming_distance(const std::string& a, const std::string& b) {
    return hamming_distance(std::string_view(a),std::string_view(b));
}

int hamming_distance( const std::string_view& a, const std::string_view& b) {
    if(a.length() > b.length())
        return hamming_distance(b,a);
    int sum = 0;
    for(int i = 0; i < a.length(); i++)
        sum += bitcount(a[i] ^ b[i]);
    for(int i = a.length(); i < b.length(); i++)
        sum += bitcount(b[i]);
    return sum;
}

int bitcount(int i) {
    int count = 0;
    while(i > 0) {
        count += i & 1;
        i >>= 1;
    }
    return count;
}

std::string get_file_contents(const char *filename) {
    std::ifstream fin(filename, std::ios::in | std::ios::binary);
    std::string contents;

    fin.seekg(0,std::ios::end);
    contents.resize(fin.tellg());
    fin.seekg(0,std::ios::beg);
    fin.read(&contents[0],contents.size());

    return contents;
}

std::mt19937 _random_int_mt((std::random_device()()));
int random_int() { return _random_int_mt(); }
int random_int(int a) { return random_int(0,a); }
int random_int(int a, int b) { return ( random_int() % (b-a + 1)) + a; }
