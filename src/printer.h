#ifndef HLIB_PRINTER_H_
#define HLIB_PRINTER_H_

#include <ostream>
#include <vector>

template <class T> 
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& x) { 
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
