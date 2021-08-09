#include "./n_vector.h"

// previously a member of competition-library

template <class T, std::size_t N> using nv = n_vector<T,N>;

template <class T, std::size_t N> nv<T,N>::n_vector(): _N{N}, std::vector<nv<T,N - 1>>() {}
template <class T, std::size_t N> std::size_t nv<T,N>::dimension() const { return _N; }

template <class T> nv<T,1>::n_vector(): _N{1}, std::vector<T>() {}
template <class T> std::size_t nv<T,1>::dimension() const { return _N; }

int main(){}
