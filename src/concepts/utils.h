#ifndef HLIB_CONCEPTS_UTILS_H_
#define HLIB_CONCEPTS_UTILS_H_

#include <concepts>
#include "../types/utils.h"

namespace hlib {
    template <class T>
    concept integral = std::is_integral_v<T>;
}

#endif