#include <string>
#include <tuple>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "xor.hpp"
#include "frequency.hpp"
#include "utils.hpp"

namespace single_character_xor {
    std::string apply(std::string str, char key) {
        for(int i = 0; i < str.length(); i++)
            str[i] ^= key;
        return str;
    }

    std::tuple<char,std::string,float> decode(const std::string& str) {
        float min_error = 1e10;
        char min_char;
        for(int i = 0; i < 256; i++) {
            float error = english::frequency_error(apply(str,i));
            if(error < min_error) {
                min_error = error;
                min_char = i;
            }
        }

        return {min_char, apply(str,min_char) , min_error};
    }
}

namespace string_xor {
    std::string apply(std::string str, const std::string& key) {
        for(int i = 0; i < str.length(); i++)
            str[i] ^= key[i % key.length()];
        return str;
    }

    class Keysize {
      private:
        int _size;
        float _norm_distance;

      public:
        static const int MIN = 2;
        static const int MAX = 50;
        static const int CHECK = 5;
        static const int RANGE = Keysize::MAX - Keysize::MIN;

        Keysize(int _s, const std::string& str) : _size{_s} {
            _norm_distance = ((float) hamming_distance(
                str.substr(0,_size),
                str.substr(_size,_size)
            )) / ((float) _size);
        }

        int size() const { return _size; }
        float norm_distance() const { return _norm_distance; }

        bool operator<(const Keysize& k) const {
            return norm_distance() < k.norm_distance();
        }
    };

    std::tuple<std::string,std::string,float> decode(const std::string& str) {
        std::vector<Keysize> keysizes;
        for(int i = Keysize::MIN; i < Keysize::MAX; i++)
            keysizes.emplace_back(i,str);
        std::sort(keysizes.begin(),keysizes.end());

        int min_error_index;
        float min_error = 1e10;
        std::string min_key;
        std::string min_message;
        for(int i = 0; i < Keysize::CHECK; i++) {
            std::cout << "Checking keysize "
                << keysizes[i].size()
                << " of normalized distance "
                << keysizes[i].norm_distance()
                << std::endl;

            std::string key;
            key.resize(keysizes[i].size());
            for(int j = 0; j < keysizes[i].size(); j++) {
                std::string block;
                for(int k = j; k < str.length(); k += key.size())
                    block += str[k];

                std::tie(key[j], std::ignore, std::ignore) = single_character_xor::decode(block);
            }

            std::string message = apply(str,key);
            float error = english::frequency_error(message);

            std::cout << message << std::endl << std::string(100,'=') << std::endl << std::string(100,'=') << std::endl;
            if(error < min_error) {
                min_error = error;
                min_key = std::move(key);
                min_message = std::move(message);
            }
        }

        return {min_key,min_message,min_error};
    }
}
