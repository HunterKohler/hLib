#ifndef HLIB_TYPES_INT_SEQUENCE_H_
#define HLIB_TYPES_INT_SEQUENCE_H_

#include <tuple>
#include <concepts>
#include "../concepts/utils.h"

namespace hlib {

    //--------------------------------------------------------------------------
    // integral_sequence<class T, T...Seq>
    //--------------------------------------------------------------------------
    // currently made of homogeneous members
    // could have a heterogenous tuple-like structure, but it wouldnt be a
    // sequence, it may be more similar to a container.

    template <integral T, T...v>
    struct integral_sequence {
        using int_type = T;
        using type = integral_sequence<T,v...>;

        constexpr int_type size() const noexcept { return sizeof...(v); }
        constexpr int_type operator[] (int i) const noexcept {
            constexpr int_type _v[] = {v...};
            return _v[i];
        }
    };

    //--------------------------------------------------------------------------
    // get(integral_sequence)
    //--------------------------------------------------------------------------
    // rather lame with fold expressions

    template <std::size_t N, class T, T...v>
        requires (N < sizeof...(v))
    constexpr T get(const integral_sequence<T,v...>& seq) noexcept {
        return seq[N];
    }

    //--------------------------------------------------------------------------
    // concat
    //--------------------------------------------------------------------------

    // struct
    template <class T, class U> 
    struct concat;

    template <template <class T, T...> class S, class T, T...U, T...V>
    struct concat<S<T,U...>, S<T,V...>> {
        using type = S<T,U...,V...>;
    };

    // helper
    template <class T, class U> 
    using concat_t = typename concat<T,U>::type;

    //--------------------------------------------------------------------------
    // index_sequence<class T, std::size_t N>
    //--------------------------------------------------------------------------

    // struct
    template <class T, std::size_t N = 0>
    struct index_sequence {
        using type = concat_t<typename index_sequence<T,N - 1>::type,
                              integral_sequence<T,N - 1>>;
    };

    template <class T>
    struct index_sequence<T,0> { using type = integral_sequence<T>; };

    // helper
    template <class T, std::size_t N = 0> 
    using index_sequence_t = typename index_sequence<T,N>::type;

    //--------------------------------------------------------------------------
    // Integral Sequence Printer
    //--------------------------------------------------------------------------

    template <integral T, T...v>
    inline std::ostream& operator<< (std::ostream& os,
                                     const integral_sequence<T,v...>& seq) {
        if constexpr(sizeof...(v) > 0) {
            return (os << "[", (..., (os << v << ",")), os << "\b]");
        } else  {
            return os << "[]";
        }
    }

}

#endif