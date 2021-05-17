#ifndef MATRIX_H_
#define MATRIX_H_

namespace Euclidean {
    template <class T>
    class Matrix {
      public:
        typedef T value_type;
        typedef std::size_t size_type;
        typedef std::tuple<size_type,size_type> pair_type;
      private:
        T* mem;
        int n,m;

      public:
        Matrix(size_type);
        Matrix(size_type, const T&);
        Matrix(size_type, size_type);
        Matrix(size_type, size_type, const T&);
        Matrix(const Matrix<T>&);
        Matrix(Matrix<T>&&);
        ~Matrix();

        Matrix<T>& operator=(const Matrix<T>&);
        Matrix<T>& operator=(Matrix<T>&&);

        Matrix<T>& operator*=(const Matrix<T>&);
        Matrix<T>& operator*=(const T& i);
        Matrix<T>& operator/=(const T& i);
        Matrix<T>& operator+=(const Matrix<T>&);
        Matrix<T>& operator-=(const Matrix<T>&);

        Matrix<T> operator+(const Matrix<T>&);
        Matrix<T> operator-(const Matrix<T>&);
        Matrix<T> operator*(const T&);
        Matrix<T> operator*(const Matrix<T>&);
        Matrix<T> operator/(const T&);
        Matrix<T> operator/(const Matrix<T>&);
        Matrix<T> operator~();
        Matrix<T> operator-();
        T& operator()(int,int);
        T& operator[](pair_type);

        size_type rows();
        size_type columns();
        pair_type dim();
    };
}








#endif
