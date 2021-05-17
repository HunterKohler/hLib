#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <type_traits>
#include <algorithm>
#include <cstddef>

template <class T, bool B> struct make_const;
template <class T> struct make_const<T,true> {typedef const T type;};
template <class T> struct make_const<T,false> {typedef T type;};
template <class T, bool B> using make_const_t = typename make_const<T,B>::type;

// LegacyRandomAccess https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
template <class T, bool is_const = false>
class RandomAccessIterator  {
  public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef make_const_t<T,is_const> value_type;
    typedef make_const_t<T,is_const>& reference_type;
    typedef make_const_t<T,is_const>* pointer_type;

  private:
    pointer_type ptr;
    difference_type offset;
    difference_type dir;

  public:
    inline RandomAccessIterator(
        pointer_type _ptr,
        bool rev = false
    ): ptr{_ptr}, dir{rev ? -1 : 1} {}
    inline RandomAccessIterator(
        pointer_type _ptr,
        difference_type _offset,
        bool rev = false
    ): RandomAccessIterator(_ptr,rev), offset {_offset} {}

    inline void reverse() {dir *= -1;};

    inline RandomAccessIterator<value_type> operator+(int i) const {return {ptr + (dir * i),offset,dir};}
    inline RandomAccessIterator<value_type> operator-() const {return {ptr,offset,dir * -1};}
    inline RandomAccessIterator<value_type> operator-(int i) const {return {ptr - (dir * i),offset,dir};}
    inline difference_type operator-(const RandomAccessIterator<T>& it) const {return ptr - it.ptr;}
    inline RandomAccessIterator<value_type> operator++() const {return {ptr + dir,offset,dir};}
    inline RandomAccessIterator<value_type> operator--() const {return {ptr - dir,offset,dir};}
    inline reference_type operator[](int i) const {return *(ptr + (dir * i) + offset);}
    inline reference_type operator*() const {return *(ptr + offset);}
    inline reference_type operator->() const {return *(ptr + offset);}
    inline bool operator<(const RandomAccessIterator<value_type>& it) const {return ptr < it.ptr;}
    inline bool operator>(const RandomAccessIterator<value_type>& it) const {return ptr > it.ptr;}
    inline bool operator<=(const RandomAccessIterator<value_type>& it) const {return ptr <= it.ptr;}
    inline bool operator>=(const RandomAccessIterator<value_type>& it) const {return ptr >= it.ptr;}
    inline bool operator==(const RandomAccessIterator<value_type>& it) const {return ptr == it.ptr;}
    inline bool operator!=(const RandomAccessIterator<value_type>& it) const {return ptr != it.ptr;}
    inline RandomAccessIterator<value_type>& operator+=(int i) {ptr += (dir * i); return *this;}
    inline RandomAccessIterator<value_type>& operator-=(int i) {ptr -= (dir * i); return *this;}

    friend RandomAccessIterator operator+(int i, const RandomAccessIterator& it) {return it + i;}
};

namespace Euclidean {
    template <class T>
    class Vector {
      public:
        typedef T value_type;
        typedef std::size_t size_type;
        typedef RandomAccessIterator<T> iterator;
        typedef RandomAccessIterator<T,true> const_iterator;

        Vector();
        Vector(size_type _n);
        Vector(size_type _n, const T& _t);
        Vector(const Vector<T>& v);
        Vector(Vector<T>&& v);
        ~Vector();

        // operators
        Vector<T> operator-();
        // auto operator+(const Vector<T>&) -> Vector<>; // addition
        // auto operator-(const Vector<T>&) -> Vector<>; // subtraction
        // auto operator*(const Vector<T>&) -> Vector<>; // dot product
        // auto operator^(const Vector<T>&) -> Vector<>; // cross product
        // Vector<T> operator%(const Vector<T>&); // resize to Vector length
        // Vector<T> operator%(length_type); // resize to length
        // bool operator|(const Vector<T>&); // isparrallel
        // bool operator&(const Vector<T>&); // purperndicular
        // bool operator!(); // isnull
        // bool operator==(const Vector<T>&); // equal
        // bool operator!=(const Vector<T>&); // not equal
        // constexpr T& operator[](length_type i) {return mem[i];}

        // assignment
        Vector<T>& operator=(const Vector<T>&); // copy assignment
        Vector<T>& operator=(Vector<T>&&); // move assignment
        Vector<T>& operator+=(const Vector<T>&); // addition
        Vector<T>& operator-=(const Vector<T>&); // subtraction
        Vector<T>& operator*=(length_type); // multiplication
        // Vector<T>& operator%=(const Vector<T>&); // resize to Vector length
        // Vector<T>& operator%=(length_type); // resize to length

        inline size_type dim() const {return n;}
        inline size_type dimension() const {return n;}

        inline iterator begin() {return iterator(mem);}
        inline iterator end() {return iterator(mem+n);}
        inline iterator rbegin() {return iterator(mem+n,-1,true);}
        inline iterator rend() {return iterator(mem,-1,true);}
        inline const_iterator cbegin() {return const_iterator(mem);}
        inline const_iterator cend() {return const_iterator(mem+n);}
        inline const_iterator crbegin() {return const_iterator(mem+n,-1,true);}
        inline const_iterator crend() {return const_iterator(mem,-1,true);}

      private:
        size_type n;
        T* mem;
    };
}

#endif
