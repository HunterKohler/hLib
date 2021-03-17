#include <string>
#include <iostream>

#include "xor.hpp"
#include "frequency.hpp"
#include "encoding.hpp"

std::string operator^(std::string a, char b) {
    for(int i = 0; i < a.length(); i++)
        a[i] = a[i] ^ b;
    return a;
}

std::string operator^(char a, std::string b) {
    return b ^ a;
}

char single_character_xor_key(const std::string& str) {
    float min_error = (1 << 30);
    int min_error_index;
    for(int i = 0; i < 256; i++) {
        float error = letter_frequency_error(str ^ ((char) i));
        if(error < min_error) {
            min_error = error;
            min_error_index = i;
        }
    }

    return min_error_index;
}

std::string single_character_xor(const std::string& str) {
    return single_character_xor_key(str) ^ str;
}

int main() {
    std::string str = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    std::cout
        << single_character_xor(hex::decode(str)) << std::endl
        << single_character_xor_key(hex::decode(str)) << std::endl;

    std::cout << letter_frequency_error("Yuuqst}:WY=i:vsq:{:juot~:u|:x{yut");

}
