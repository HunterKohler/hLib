#include <sstream>
#include <iostream>
#include <string>

std::string repeating_key_xor(std::string str, std::string key) {
    std::stringstream ss;
    ss << std::hex;
    for(int i = 0; i < str.length(); i++)
        ss << (str[i] ^ key[i % key.length()]);
    return ss.str();
}


int main(int argc, char *argv[]) {
    std::cout << repeating_key_xor(argv[1],argv[2]);
}
