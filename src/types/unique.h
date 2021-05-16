#ifndef HLIB_TYPES_UNIQUE_H_
#define HLIB_TYPES_UNIQUE_H_

namespace hlib {

    //--------------------------------------------------------------------------
    // is_same_template<template <class...> class T, 
    //                  template <class...> class U>
    //--------------------------------------------------------------------------

    // structs
    template <template <class...> class T, template <class...> class U>
    struct is_same_template : false_type {};

    template <template <class...> class T>
    struct is_same_template<T,T> : true_type {};

    // helper
    template <template <class...> class T, template <class...> class U>
    constexpr bool is_same_template_v = is_same_template<T,U>::value;

    // concept
    template <template <class...> class T, template <class...> class U>
    concept same_template_as = is_same_template<T,U>::value; 

    //--------------------------------------------------------------------------
    // is_instantiated_from<class T, template <class...> class U> 
    //--------------------------------------------------------------------------

    // structs
    template <class T, template <class...> class U>
    struct is_instantiated_from : false_type {};

    template <class...T, template <class...>  class U>
    struct is_instantiated_from<U<T...>, U> : true_type {};

    // helper
    template <class T, template <class...> class U>
    constexpr bool is_instantiated_from_v = is_instantiated_from<T,U>::value;

    // concept
    template <class T, template <class...> class U>
    concept instantiated_from = is_instantiated_from<T,U>::value;

}

#endif