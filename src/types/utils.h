#ifndef HLIB_TYPES_UTILS_H_
#define HLIB_TYPES_UTILS_H_

namespace hlib {
    
    //--------------------------------------------------------------------------
    // conditional<bool B, class T, class F>
    //--------------------------------------------------------------------------

    // structs
    template <bool B, class T, class F> 
    struct conditional { using type = T; };

    template <class T, class F> 
    struct conditional<false,T,F> { using type = F; };

    // helper
    template <bool B, class T, class F>
    using conditional_t = typename conditional<B,T,F>::type;

    //--------------------------------------------------------------------------
    // is_same<class T, class U>
    //--------------------------------------------------------------------------

    // structs
    template <class T, class U> struct is_same : std::false_type {}; 
    template <class T> struct is_same<T,T> : std::true_type {};

    // helper
    template <class T, class U> 
    constexpr bool is_same_v = is_same<T,U>::value;

    // concept
    template <class T, class U>
    concept same_as = is_same<T,U>::value;

    //--------------------------------------------------------------------------
    // is_same_template<template <class...> class T, 
    //                  template <class...> class U>
    //--------------------------------------------------------------------------

    // structs
    template <template <class...> class T, template <class...> class U>
    struct is_same_template : std::false_type {};

    template <template <class...> class T>
    struct is_same_template<T,T> : std::true_type {};

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
    struct is_instantiated_from : std::false_type {};

    template <class...T, template <class...>  class U>
    struct is_instantiated_from<U<T...>, U> : std::true_type {};

    // helper
    template <class T, template <class...> class U>
    constexpr bool is_instantiated_from_v = is_instantiated_from<T,U>::value;

    // concept
    template <class T, template <class...> class U>
    concept instantiated_from = is_instantiated_from<T,U>::value;

}


#endif