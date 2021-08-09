#ifndef LIB_STRUCTS_N_VECTOR_H_
#define LIB_STRUCTS_N_VECTOR_H_

#include <vector>

// previously a member of competition-library

template <class T, std::size_t N>
class n_vector: public std::vector<n_vector<T,N - 1>> {
  public:
    std::size_t dimension() const;
    n_vector();
  private:
    std::size_t _N;
};

template <class T>
class n_vector<T,1>: public std::vector<T> {
    public:
      std::size_t dimension() const;
      n_vector();
    private:
      std::size_t _N;
};

#endif
