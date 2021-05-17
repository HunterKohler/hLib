#include "Matrix.hpp"

namespace Euclidean {
    template <class T> Matrix<T>::Matrix(size_type _nm)
        : Matrix(_nm,_nm) {}
    template <class T> Matrix<T>::Matrix(size_type _n, size_type _m)
        : n{_n}, m{_m}, mem{new T[_n*_m]}
    template <class T> Matrix<T>::Matrix(size_type _nm, const T& _t)
        : Matrix(_nm,_nm,_t);
    template <class T> Matrix<T>::Matrix(size_type _n, size_type _m, const T& _t)
        : Matrix(_n,_m) {std::fill_n(mem,n*m,_t);}
    template <class T> Matrix<T>::Matrix(const Matrix<T>& _mtx)
        : Matrix(_mtx.n,_mtx.m) {std::copy(_mtx.mem,n*m,mem);}
    template <class T> Matrix<T>::Matrix(Matrix<T>&& _mtx) noexcept
        : n{_mtx.n}, m{_mtx.m}, mem{_mtx.mem} {
            _mtx.n = 0;
            _mtx.m = 0;
            _mtx.mem = nullptr;
        }

    template <class T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mtx) {
        std::tie(n,m) = mtx.dim();
        std::copy(_mtx.mem,n*m,mem);
    }

    template <class T> Matrix<T>& Matrix<T>::operator=(Matrix<T>&& mtx) noexcept {
        delete[] mem;
        n = mtx.n;
        m = mtx.m;
        mem = mtx.mem;
        mtx.n = 0;
        mtx.m = 0;
        mtx.mem = nullptr;
    }
}

int main() {

}
