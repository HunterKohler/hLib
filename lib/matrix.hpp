#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <array>
#include <iostream>
#include <map>

#include "vector.hpp"

template <class T>
class Matrix {
  public:
    typedef T value_type;
    typedef std::size_t size_type;

    static constexpr Matrix<T> Zero(size_type, size_type);
    static constexpr Matrix<T> Identity(size_type);

    static constexpr Matrix<T> Rotation(int...);
    static constexpr Matrix<T> Rotation(int*,int);
    static constexpr Matrix<T> Rotation(std::vector<int>);

    static constexpr Matrix<T> Diagonal(int...);
    static constexpr Matrix<T> Diagonal(int*,int);
    static constexpr Matrix<T> Diagonal(std::vector<int>);

    Matrix();
    Matrix(size_type, size_type);

    Matrix(std::initializer_list<std::initializer_list<T>>);
    Matrix(std::initializer_list<std::vector<T>>);
    Matrix(std::initializer_list<std::tuple<int,int>>);

    Matrix(std::map<std::tuple<int,int>,T>);
    Matrix(std::vector<std::vector<T>>); // test for arbitrary allocators

    T& operator()(int,int);
    T* operator[](int);

    operator T* () const;
    operator T** () const;
    operator std::map<std::tuple<int,int>,T> () const;

    size_type length() const;
    size_type width() const;

    std::tuple<size_type,size_type> size() const;

    size_type rank() const;

    bool sqaure() const;
    bool lower_triangular() const;
    bool upper_triangular() const;
    bool triangular() const;

    T trace() const;
    T tr() const;

    int determinant() const;
    int det() const;

    int span() const;
    vector<

    // span()
    // column()
    // row()
    // adjugate()
    // cofactor()
    // inverse()
    // cross()
    // minor()
    // exp()
    // full_rank()
    // row_swap()
    // row_add()

    Matrix<T> submatrix(const bool*, const bool*) const;
    Matrix<T> submatrix(const std::vector<bool>&, const std::vector<bool>&) const;

    Matrix<T>& transpose();
  private:
    T* memory;
    size_type n,m;
};

template <class T>
struct std::hash<Matrix<T>> {
    std::size_t operator() (const Matrix<T>&) const;
};

template <class T> T operator-(Matrix<T>);
template <class T> T operator!(Matrix<T>);
template <class T> T operator++(Matrix<T>);
template <class T> T operator--(Matrix<T>);

template <class T> Matrix<T> operator+(const Matrix<T>&, Matrix<T>);
template <class T> Matrix<T> operator-(const Matrix<T>&, Matrix<T>);
template <class T> Matrix<T> operator*(const Matrix<T>&, Matrix<T>);

template <class T> Matrix<T> operator*(Matrix<T>,int);
template <class T> Matrix<T> operator*(int,Matrix<T>);

template <class T> std::ostream& operator<<(std::ostream& os, const Matrix<T>&);
template <class T> std::istream& operator>>(std::istream& os, const Matrix<T>&);

template <

#endif
