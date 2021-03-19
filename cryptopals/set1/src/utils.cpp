#include <string>
#include <fstream>
#include "utils.hpp"

int hamming_distance(const std::string& a, const std::string& b) {
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
