#include <iostream>
#include <string>


constexpr int hex[256] = {
    ['0'] = 0,  ['1'] = 1,
    ['2'] = 2,  ['3'] = 3,
    ['4'] = 4,  ['5'] = 5,
    ['6'] = 6,  ['7'] = 7,
    ['8'] = 8,  ['9'] = 9,
    ['A'] = 10, ['B'] = 11,
    ['C'] = 12, ['D'] = 13,
    ['E'] = 14, ['F'] = 15
};

int main(int argc, char *argv[]) {
    std::string inp;

    if(argc < 2) {
        std::cin >> inp;
    } else {
        inp = argv[1];
    }

    std::string out;
    for(int i = 0; i < inp.length(); i++) {
        out += 16 * hex[inp[i]] + hex[inp[i+1]];
    }

    std::cout << out << std::endl;
}
