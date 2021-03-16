#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string x = argv[1];
    std::string y = argv[2];
    for(int i = 0; i < x.length(); i += 2) {
        std::cout << std::hex <<
            (std::stoi(x.substr(i,2),nullptr,16)
                ^ std::stoi(y.substr(i,2),nullptr,16));
    }
}
