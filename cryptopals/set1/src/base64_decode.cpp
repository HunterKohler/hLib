#include <iostream>
#include <string>

#include "base64_decode.hpp"

std::string base64_decode(const std::string& str) {
    std::string ret;
    for(int i = 0; i < str.length(); i += 4) {
        ret += (base64[str[i]] << 2) + (base64[str[i+1]] >> 4);
        ret += ((base64[str[i+1]] % (1 << 4)) << 4) + (base64[str[i+2]] >> 2);
        ret += ((base64[str[i+2]] % (1 << 2)) << 6) + base64[str[i+3]];
    }

    if(str.length() > 0) {
        ret.pop_back();
        if(str[str.length()-1] == '=') ret.pop_back();
        if(str[str.length()-2] == '=') ret.pop_back();
    }

    return ret;
}
