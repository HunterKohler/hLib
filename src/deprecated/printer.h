#ifndef MYREGEX_PRINTER_H_
#define MYREGEX_PRINTER_H_

#include <ostream>

#include "types.h"

template <specialization_of<std::vector> T> 
inline std::ostream& operator<<(std::ostream& os, const T& x) { 
    os << "[";
    auto it = std::cbegin(x);
    auto end = std::cend(x);
    while(it != end) {
        os << *it;
        ++it;
        if(it != end) 
            os << ",";
    }
    return os << "]";
}

#endif
