#include "../include/matrix.hpp"

template<class T>
std::ostream& operator<<(std::ostream& os, const matrix<T>& m) {
    int l = 0;
    for(const std::vector<T>& v: m) {
        os << (l == 0 ? "{{" : " {");
        int i_v = 0;
        for(const T& i: v)
            os << i << (++i_v == v.size() ? "" : ", ");
        os << (++l == m.size() ? "}" : "}\n");
    }
    return os << "}\n";
}

template <class T>
class basic_matrix {
  private:
    T *mem;
    int n,m;
  public:
    basic_matrix(int _n, int _m): n{_n}, m{_m}, mem{new T[_n*_m]} {}
    basic_matrix(int _n): basic_matrix(_n,_n) {}
    ~basic_matrix() { delete[] mem; }
    T& operator()(int i, int j) { return mem[i*n+j]; }
};
