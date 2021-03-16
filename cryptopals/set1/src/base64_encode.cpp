#include <iostream>
#include <string>

constexpr char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char *argv[]) {
    std::string inp;

    if(argc < 2) {
        std::cin >> inp;
    } else {
        for(int i = 1; i < argc; i++) {
            inp += argv[i];
            inp += " ";
        }
        inp.pop_back();
    }

    int padding = 0;
    if(inp.length() % 3 == 1) {
        padding = 2;
        inp += "\0\0";
    } else if(inp.length() % 3 == 2) {
        padding = 1;
        inp += "\0";
    }

    std::string out;
    for(int i = 0; i < inp.length(); i += 3) {
        out += base64[inp[i] >> 2];
        out += base64[((inp[i] % (1 << 2)) << 4) + (inp[i+1] >> 4)];
        out += base64[((inp[i+1] % (1 << 4)) << 2) + (inp[i+2] >> 6)];
        out += base64[(inp[i+2] % (1 << 6))];
    }

    if(padding == 1) {
        out.pop_back();
        out += "=";
    } else if(padding == 2) {
        out.pop_back();
        out.pop_back();
        out += "==";
    }

    std::cout << out << std::endl;
}
