#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include <vector>

template<class T> using matrix = std::vector<std::vector<T>>;
template<class T> std::ostream& operator<<(std:: ostream& os, const matrix<T>& m);

#endif
