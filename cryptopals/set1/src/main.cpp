#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <utility>

#include "encoding.hpp"
#include "frequency.hpp"
#include "xor.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {
    std::string data = get_file_contents("dataset.txt");
    std::remove_if(data.begin(), data.end(), isspace);

    data = base64::decode(data);

    std::string message;
    std::string key;
    float error;
    std::tie(key,message,error) =  string_xor::decode(data);
    std::cout << message << std::endl << key << " " << error << std::endl;
}
