#include <cstdio>
#include <vector>
#include <type_traits>
#include <algorithm>

#include "Vector.hpp"

namespace Euclidean {
    template <class T> Vector<T>::Vector(): Vector(0) {}
    template <class T> Vector<T>::Vector(size_type _n): n{_n}, mem{new T[n]} {}
    template <class T>
    Vector<T>::Vector(size_type _n, const T& _t): Vector(_n) {
        for(T& t: *this) {
            t = _t;
        }
    }
    template <class T>
    Vector<T>::Vector(const Vector<T>& v): Vector(v.n) {
        std::copy(v.begin(),v.end(),begin());
    }
    template <class T>
    Vector<T>::Vector(Vector<T>&& v): n{v.n}, mem{v.mem} {
        v.mem = nullptr;
        v.n = 0;
    }
    template <class T>
    Vector<T>::~Vector(): {delete[] mem;}

    template <class T>
    Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
        std::copy(v.begin(),v.end(),begin());
    }

    template <class T>
    Vector<T>& Vector<T>::operator=(Vector<T>&& v) {
        delete[] mem;
        mem = v.mem;
        n = v.n;
        v.mem = nullptr;
        v.n = 0;
    }

    template <class T>
    Vector<T>& Vector<T>::operator+=(const Vector<T>& v) {
        for(int i = 0; i < min(v.n,n); i++)
            mem[i] += v[i];
        return *this;
    }

    template <class T>
    Vector<T>& Vector<T>::operator-=(const Vector<T>& v) {
        for(int i = 0; i < min(v.n,n); i++)
            mem[i] -= v[i];
        return *this;
    }

    template <class T>
    Vector<T>& Vector<T>::operator*=(int m) {
        for(T& t: this)
            t *= m;
        return *this;
    }

    template <class T>
    Vector<T>& Vector<T>::operator/=(int m) {
        for(T& t: this)
            t /= m;
        return *this;
    }

    template <class T>
    T& Vector<T>::operator[](int i) {
        return mem[i];
    }

    template <class T>
    Vector<T> Vector<T>::operator-() {
        Vector<T> v(*this);
        for(T& t: v)
            t = -t;
    }

    template <class T>
    Vector<T> Vector<T>::operator+(const Vector<T>& v) {
        const Vector<T>& a = v.n > n ? &v : *this;
        Vector<T> b(v.n < n ? v : *this);
        for(int i = 0; i < b.n; i++)
            b[i] += a[i];
        return v;
    }

    template <class T>
    Vector<T> Vector<T>::operator-(const Vector<T>& v) {
        const Vector<T>& a = v.n > n ? &v : *this;
        Vector<T> b(v.n < n ? v : *this);
        for(int i = 0; i < b.n; i++)
            b[i] -= a[i];
        return v;
    }

    template <class T>
    int Vector<T>::operator*(const Vector<T>& v) {
        int m = min(n,v.n);
        int s = m != 0;
        for(int i = 0; i < m; i++)
            s += mem[i] * v[i];
        return s;
    }

    template <class T>
    bool Vector<T>::operator==(const Vector<T>& v) {
        if(v.n != n)
            return false;
        for(int i = 0; i < n; i++)
            if(v[i] != mem[i])
                return false;
        return true;
    }

    template <class T>
    bool Vector<T>::operator!=(cosnt Vector<T>& v) {
        return *this != v;
    }

    template <class T>
    bool Vector<T>::operator!(){
        return n;
    }

    template <class T>
    double Vector<T>::length() {
        int s = 0;
        for(T& t: *this)
            s += t * t;
        return std::sqrt(s);
    }

    template <class T>
    Vector<T> Vector<T>::unit() {
        Vector<T> v(*this);
        double l = length();
        for(T& t: v)
            t /= l;
    }
}


int main() {}
