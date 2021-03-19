#ifndef XOR_H_
#define XOR_H_

#include <string>

namespace single_character_xor {
    std::string apply(std::string str, char key);
    std::tuple<char,std::string,float> decode(const std::string& str);
}

namespace string_xor {
    std::string apply(std::string, const std::string&);
    std::tuple<std::string,std::string,float> decode(const std::string&);
}

#endif
