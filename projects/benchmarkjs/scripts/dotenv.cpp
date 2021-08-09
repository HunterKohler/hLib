#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

inline bool alnum(char c) {
    return ('a' <= c && c <= 'z') 
        || ('A' <= c && c <= 'Z')
        || ('0' <= c && c <= '9');
}

inline bool alnum(std::string s) {
    for(char c: s)
        if(!alnum(c))
            return false;
    return true;
}

inline bool varname(char c) {
    return c == '_' || alnum(c);
}

inline bool varname(std::string s) {
    for(char c: s) 
        if(!alnum(c)) 
            return false; 
    return true;
}

const std::string[] strs {
    "mystr",
    "mystr=",
    "mystr=ustr",
    "_mystr=",
    "my__st_r_=u112"
};

int main() {
    
    
}
