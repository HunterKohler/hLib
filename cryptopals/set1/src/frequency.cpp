#include <string>
#include <iostream>

#include "frequency.hpp"

float* char_frequency(const std::string& str) {
    float* frequency = new float[256]();
    for(char c: str)
        frequency[c]++;
    for(int i = 0; i < 256; i++)
        frequency[i] = frequency[i] / str.length();
    return frequency;
}

// lower better
float letter_frequency_error(const std::string& str) {
    float* frequency = char_frequency(str);
    float error = 0;
    for(int i = 0; i < 256; i++)
        error += abs(frequency[i] - english_letter_frequency[i]);
    std::cout << str << " -> " << error << std::endl;
    delete[] frequency;
    return error;
}
