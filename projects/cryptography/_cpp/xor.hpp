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

    class Keysize {
      private:
        int _size;
        float _norm_distance;
      public:
        static const int MIN = 2;
        static const int MAX = 50;
        static const int CHECK = 5;
        static const int BLOCKS = 10;
        static const int RANGE = Keysize::MAX - Keysize::MIN;

        Keysize(int, const std::string&);

        int size() const;
        float norm_distance() const;
        bool operator<(const Keysize& k) const;
    };
}

#endif
