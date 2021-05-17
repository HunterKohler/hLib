#include <string>
#include <tuple>
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

namespace base64 {
    inline char byte1(char i) { return charset[i >> 2]; }
    inline char byte2(char i, char j = 0) { return charset[((i % 4) << 4) + (j >> 4)]; }
    inline char byte3(char i, char j = 0) { return charset[((i % 16) << 2) + (j >> 6)]; }
    inline char byte4(char i) { return charset[i % 64]; }

    std::string encode(const std::string& plain) {
        std::string encoded;
        for(int i = 0; i + 2 < plain.length(); i += 3) {
            encoded.append({
                byte1(plain[i]),
                byte2(plain[i],plain[i+1]),
                byte3(plain[i+1],plain[i+2]),
                byte4(plain[i+2])
            });
        }

        if(plain.size() % 3 == 1) {
            encoded.append({
                byte1(plain.back()),
                byte2(plain.back()), '=','='
            });
        } else if(plain.size() % 3 == 2) {
            int i = plain.size() - 2;
            encoded.append({
                byte1(plain[i]),
                byte2(plain[i],plain[i+1]),
                byte3(plain[i+1]), '='
            });
        }

        return encoded;
    }

    std::string decode(const std::string& encoded) {
        std::string plain;
        for(int i = 0; i + 3 < encoded.length(); i += 4) {
            plain += (charval[encoded[i]] << 2) + (charval[encoded[i+1]] >> 4);
            plain += ((charval[encoded[i+1]] % (1 << 4)) << 4) + (charval[encoded[i+2]] >> 2);
            plain += ((charval[encoded[i+2]] % (1 << 2)) << 6) + charval[encoded[i+3]];
        }

        // this may not work but it seems to, idk why
        int l = encoded.length();
        if(encoded[l-1] == '=') plain.pop_back();
        if(encoded[l-2] == '=') plain.pop_back();

        return plain;
    }
}
