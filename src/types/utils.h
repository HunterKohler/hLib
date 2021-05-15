#ifndef HLIB_TYPES_UTILS_H_
#define HLIB_TYPES_UTILS_H_

namespace hlib {
    
    //--------------------------------------------------------------------------
    // integral_constant<class T, T v>
    //--------------------------------------------------------------------------
    // basis for the entire type library

    template <class T, T v>
    struct integral_constant {
        using value_type = T;
        using type = integral_constant<T,v>;

        static constexpr value_type value = v;

        constexpr operator value_type () const noexcept { return value; };
        constexpr value_type operator() () const noexcept { return value; };
    };

    //--------------------------------------------------------------------------
    // bool_constant<bool B>
    // true_type
    // false_type
    //--------------------------------------------------------------------------
    
    template <bool B> struct bool_constant : integral_constant<bool,B> {};
    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;
    
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
    template <class T, class U> struct is_same : false_type {}; 
    template <class T> struct is_same<T,T> : true_type {};

    // helper
    template <class T, class U> 
    constexpr bool is_same_v = is_same<T,U>::value;

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

    //--------------------------------------------------------------------------
    // remove_volatile<class T>
    //--------------------------------------------------------------------------
    
    // struct
    template <class T> struct remove_volatile { using type = T; };
    template <class T> struct remove_volatile<volatile T> { using type = T; };

    // helper
    template <class T> 
    using remove_volatile_t = typename remove_volatile<T>::type;

    //--------------------------------------------------------------------------
    // remove_const<class T>
    //--------------------------------------------------------------------------
    
    // struct
    template <class T> struct remove_const { using type = T; };
    template <class T> struct remove_const<const T> { using type = T; };

    // helper
    template <class T> using remove_const_t = remove_const<T>::type;

    //--------------------------------------------------------------------------
    // remove_cv<class T>
    //--------------------------------------------------------------------------
    // Unsure of wether to use template specialization, or to nest remove
    // volatile and remove const.

    // struct
    template <class T> struct remove_cv { using type = T; };
    template <class T> struct remove_cv<const T> { using type = T; };
    template <class T> struct remove_cv<volatile T> { using type = T; };
    template <class T> struct remove_cv<volatile const T> { using type = T; };

    // helper
    template <class T> using remove_cv_t = typename remove_cv<T>::type;

    //--------------------------------------------------------------------------
    // is_volatile<class T>
    //--------------------------------------------------------------------------

    // // struct
    // template <class T> struct is_volatile : false_type {};
    // template <class T> struct is_volatile<volatile T> : true_type {};

    // // helper
    // template <class T> 
    // constexpr bool is_volatile_v = is_volatile<T>::value;

    //--------------------------------------------------------------------------
    // is_integral<class T>
    //--------------------------------------------------------------------------

    // struct
    template <class T> struct is_integral : false_type {};

    template <> struct is_integral<bool> : true_type {};
    template <> struct is_integral<char> : true_type {};
    template <> struct is_integral<char8_t> : true_type {};
    template <> struct is_integral<char16_t> : true_type {};
    template <> struct is_integral<char32_t> : true_type {};
    template <> struct is_integral<wchar_t> : true_type {};
    template <> struct is_integral<short> : true_type {};
    template <> struct is_integral<int> : true_type {};
    template <> struct is_integral<long> : true_type {};
    template <> struct is_integral<long long> : true_type {};

    // helper
    template <class T> constexpr bool is_integral_v = is_integral<T>::value;

    //--------------------------------------------------------------------------
    // extent<class T, std::size_t N>
    //--------------------------------------------------------------------------

}


#endif