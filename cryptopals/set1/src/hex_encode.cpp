#include <iostream>
#include <string>

constexpr char hex[] = "0123456789abcdef";

int main(int argc, char *argv[]) {
    std::string inp;

    if(argc == 1) {
        std::cin >> inp;
    } else {
        inp = argv[1];
    }

    std::string out;
    for(char c: inp) {
        out += hex[((int) c) >> 4];
        out += hex[((int) c) % 16];
    }

    std::cout << out << std::endl;
}
