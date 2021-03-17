#include <iostream>
#include <string>

constexpr char hex[] = "0123456789abcdef";

int main(int argc, char *argv[]) {
    std::string inp;

    if(argc == 1) {
        std::cin >> inp;
    } else {
        for(int i = 1; i < argc; i++) {
            inp += argv[i];
        }
    }

    std::string out;
    for(char c: inp) {
        out += hex[((int) c) >> 4];
        out += hex[((int) c) % 16];
    }

    std::cout << out << std::endl;
}
