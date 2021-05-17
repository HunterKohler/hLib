#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include <vector>

// using matrix = C<C<T>>;

template <class T>
using matrix = std::vector<std::vector<T>>;

// template<class T, template<class...> class C = std::vector>
// class matrix: public C<C<T>> {
//     typedef Container C;
//     template <class ...Args>
//     matrix(Args...args):C<C<T>>(args...) {}
// };

template<class T> std::ostream& operator<<(std:: ostream& os, const matrix<T>& m);

#endif
