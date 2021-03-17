#include <string>
#include <iostream>
#include "encoding.hpp"

namespace hex {
    std::string encode(const std::string& plain) {
        std::string encoded;
        for(char c: plain) {
            encoded += charset[c >> 4];
            encoded += charset[c % 16];
        }
        return encoded;
    }

    std::string decode(const std::string& encoded) {
        std::string plain;
        for(int i = 0; i < encoded.length(); i += 2)
            plain += (charval[encoded[i]] << 4) + charval[encoded[i+1]];
        return plain;
    };
}

namespace base46 {
    std::string encode(const std::string& plain) {
        std::string encoded;
        for(int i = 0; i < plain.length(); i += 3) {
            encoded += charset[plain[i] >> 2];
            encoded += charset[((plain[i] % (1 << 2)) << 4) + (plain[i+1] >> 4)];
            encoded += charset[((plain[i+1] % (1 << 4)) << 2) + (plain[i+2] >> 6)];
            encoded += charset[plain[i+1] % (1 << 6)];
        }
        return encoded;
    }

    // incomplete padding
    std::string decode(const std::string& encoded) {
        std::string plain;
        for(int i = 0; i < encoded.length(); i += 4) {
            plain += charval[(encoded[i] << 2) + (encoded[i+1] >> 4)];
            plain += charval[((encoded[i+1] % (1 << 4)) << 4) + (encoded[i+2] >> 2)];
            plain += charval[(encoded[i+2] % (1 << 2)) + encoded[i+3]];
        }
        return plain;
    }
}
