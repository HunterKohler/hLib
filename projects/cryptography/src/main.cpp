#include <iostream>
#include "frequency.h"

int main(int argc, char const *argv[]) {
    if(argc > 1) {
        // std::string str(argv[1]);
        std::cout << english::frequency_error(argv[1]) << std::endl;
    }
}
