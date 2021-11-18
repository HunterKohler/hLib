#include <string>
#include "frequency.h"

namespace english {
    float frequency_error(const std::string& str) {
        float frequency[256] {};
        float error = 0;
        for(char c: str) {
            if(((int) c) < 0) {
                frequency[127 - c]++;
            } else {
                frequency[c]++;
            }
        }

        for(float& f: frequency)
            f /= str.length();
        for(int i = 0; i < 256; i++)
            error += std::abs(english::letter_frequency[i] - frequency[i]);

        return error;
    }
}
