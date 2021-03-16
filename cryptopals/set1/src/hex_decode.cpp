#include <iostream>
#include <string>


constexpr int hex[256] = {
    ['0'] = 0,  ['1'] = 1,
    ['2'] = 2,  ['3'] = 3,
    ['4'] = 4,  ['5'] = 5,
    ['6'] = 6,  ['7'] = 7,
    ['8'] = 8,  ['9'] = 9,
    ['a'] = 10, ['b'] = 11,
    ['c'] = 12, ['d'] = 13,
    ['e'] = 14, ['f'] = 15
};

int main(int argc, char *argv[]) {
    std::string inp;

    if(argc < 2) {
        std::cin >> inp;
    } else {
        for(int i = 1; i < argc; i++) {
            inp += argv[i];
        }
    }

    std::string out;
    for(int i = 0; i < inp.length(); i += 2) {
        out += (char) (16 * hex[inp[i]] + hex[inp[i+1]]);
    }

    std::cout << out << std::endl;
}
