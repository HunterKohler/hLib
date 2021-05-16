#ifndef HLIB_TYPES_STANDARD_H_
#define HLIB_TYPES_STANDARD_H_

// C++20 STL <type_traits>
//      referencing draft N4860


// TEMPORARY
#include <type_traits>
#include <iostream>

namespace hlib {

    //--------------------------------------------------------------------------
    // NON STANDARD
    //--------------------------------------------------------------------------
    // NOTE Should `is_XXX` be implemented it with conditional inheritance?
    //      i.e.: inherit from `is_integral` or `is_floating_point` if that
    //      is so.
    // SEE `is_arithmetic`, `is_fundamental`, ...

    // Type aliases
    // -------------------------------------------------------------------------
    // Helpers to ensure this header compiles in dev.
    using size_t = unsigned long long int;
    using nullptr_t = decltype(nullptr);

    // remove_cv
    // -------------------------------------------------------------------------
    // Helper to ensure this header compiles in dev.
    template <class T> struct remove_cv { using type = T; };
    template <class T> struct remove_cv<const T> { using type = T; };
    template <class T> struct remove_cv<volatile T> { using type = T; };
    template <class T> struct remove_cv<const volatile T> { using type = T; };

    // remove_cv_t
    // -------------------------------------------------------------------------
    // Helper to ensure this header compiles in dev.
    template <class T> using remove_cv_t = typename remove_cv<T>::type;

    // _void_t
    // -------------------------------------------------------------------------
    namespace {
        template <class...> using _void_t = void;
    }

    // _is_referenceable 
    // -------------------------------------------------------------------------
    // [defns.referenceable]
    
    namespace {
        namespace {
            template <class T, class = void> struct _is_referenceable_helper
                : std::false_type {};
            
            template <class T> struct _is_referenceable_helper<T,_void_t<T&>>
                : std::true_type {};
        }
        template <class T> struct _is_referenceable 
            : _is_referenceable_helper<T> {};
    }


    // Named Requirements
    // -------------------------------------------------------------------------
    // Named requirements for <type_traits> header. 
    // SEE [meta.rqmts]

    // - Cpp17UnaryTypeTrait
    // - Cpp17BinaryTypeTrait
    // - Cpp17TransformationTrait

    //--------------------------------------------------------------------------
    // 20.15.3 Helper Class
    //--------------------------------------------------------------------------

    template <class T, T v> 
    struct integral_constant {
        static constexpr T value = v;

        using value_type = T;
        using type = integral_constant<T, v>;
        
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; }
    };

    template <bool B> 
    using bool_constant = integral_constant<bool, B>;             
    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;


    //--------------------------------------------------------------------------
    // 20.15.4.1 Primary Type Categories
    //--------------------------------------------------------------------------

    // is_void
    // -------------------------------------------------------------------------
    namespace {
        template <class> struct _is_void_helper : false_type {};
        template <> struct _is_void_helper<void> : true_type {}; 
    }

    template <class T> struct is_void 
        : _is_void_helper<remove_cv_t<T>> {};

    // is_null_pointer
    // -------------------------------------------------------------------------
    namespace {
        template <class> struct _is_null_pointer_helper : false_type {};
        template <> struct _is_null_pointer_helper<nullptr_t> : true_type {};
    }

    template <class T> struct is_null_pointer
        : _is_null_pointer_helper<remove_cv_t<T>> {};

    // is_integral
    // -------------------------------------------------------------------------
    namespace {
        template <class> struct _is_integral_helper : false_type {};
        template<> struct _is_integral_helper<signed char> : true_type {};
        template<> struct _is_integral_helper<short int> : true_type {};
        template<> struct _is_integral_helper<int> : true_type {};
        template<> struct _is_integral_helper<long int> : true_type {};
        template<> struct _is_integral_helper<long long int> : true_type {};
        template<> struct _is_integral_helper<unsigned char> : true_type {};
        template<> struct _is_integral_helper<unsigned short int> : true_type {};
        template<> struct _is_integral_helper<unsigned int> : true_type {};
        template<> struct _is_integral_helper<unsigned long int> : true_type {};
        template<> struct _is_integral_helper<unsigned long long int> : true_type {};
        template<> struct _is_integral_helper<bool> : true_type {};
        template<> struct _is_integral_helper<char> : true_type {};
        template<> struct _is_integral_helper<wchar_t> : true_type {};
        template<> struct _is_integral_helper<char8_t> : true_type {};
        template<> struct _is_integral_helper<char16_t> : true_type {};
        template<> struct _is_integral_helper<char32_t> : true_type {};
    }

    template <class T> struct is_integral
        : _is_integral_helper<remove_cv_t<T>> {};

    // is_floating_point
    // -------------------------------------------------------------------------
    namespace {
        template <class> struct _is_floating_point_helper : false_type {};
        template <> struct _is_floating_point_helper<float> : true_type {};
        template <> struct _is_floating_point_helper<double> : true_type {};
        template <> struct _is_floating_point_helper<long double> : true_type {};
    }

    template <class T> struct is_floating_point
        : _is_floating_point_helper<remove_cv_t<T>> {};

    // is_array
    // -------------------------------------------------------------------------
    // works with cv types with out removal
    template <class> struct is_array : false_type {};
    template <class T> struct is_array<T[]> : true_type {};
    template <class T, size_t N> struct is_array<T[N]> : true_type {};
    
    // is_pointer
    // -------------------------------------------------------------------------
    namespace {
        template <class> struct _is_pointer_helper : false_type {};
        template <class T> struct _is_pointer_helper<T*> : true_type {};
    }
    
    template <class T> struct is_pointer
        : _is_pointer_helper<remove_cv_t<T>> {};

    // is_lvalue_reference
    // -------------------------------------------------------------------------
    namespace {
        template <class> struct _is_lvalue_reference_helper : false_type {};
        template <class T> struct _is_lvalue_reference_helper<T&> : true_type {};
    }

    template <class T> struct is_lvalue_reference
        : _is_lvalue_reference_helper<remove_cv_t<T>> {};

    // is_rvalue_reference
    // -------------------------------------------------------------------------
    namespace {
        template <class> struct _is_rvalue_reference_helper : false_type {};
        template <class T> struct _is_rvalue_reference_helper<T&&> : true_type {};
    }

    template <class T> struct is_rvalue_reference
        : _is_rvalue_reference_helper<remove_cv_t<T>> {};
    
    template <class T> struct is_member_object_pointer; /* UNIMPLEMENTED */
    template <class T> struct is_member_function_pointer; /* UNIMPLEMENTED */
    template <class T> struct is_enum; /* UNIMPLEMENTED */
    template <class T> struct is_union; /* UNIMPLEMENTED */
    template <class T> struct is_class; /* UNIMPLEMENTED */
    template <class T> struct is_function; /* UNIMPLEMENTED */

    // 20.15.4.2 composite type categories

    // is_reference
    // -------------------------------------------------------------------------
    namespace {
        template <class> struct _is_reference_helper : false_type {};
        template <class T> struct _is_reference_helper<T&> : true_type {};
        template <class T> struct _is_reference_helper<T&&> : true_type {};
    }

    template <class T> struct is_reference 
        : _is_reference_helper<remove_cv_t<T>>{};

    // is_arithmetic
    // -------------------------------------------------------------------------
    template<class T> struct is_arithmetic
        : bool_constant<is_integral<T>::value 
                     || is_floating_point<T>::value> {};

    // is_fundamental
    // -------------------------------------------------------------------------
    template<class T> struct is_fundamental
        : bool_constant<is_arithmetic<T>::value
                     || is_void<T>::value
                     || is_null_pointer<T>::value> {};
    
    // is_object
    // -------------------------------------------------------------------------
    template<class T> struct is_object; /* UNIMPLEMENTED */

    // is_scalar
    // -------------------------------------------------------------------------
    // Arithmetic types (6.8.1), enumeration types, pointer types, 
    // pointer-to-member types (6.8.2), std::nullptr_t, and cv-qualified (6.8.3) 
    // versions of these types are collectively called scalar types.

    template<class T> struct is_scalar; /* UNIMPLEMENTED */

    // is_compound
    // -------------------------------------------------------------------------
    template<class T> struct is_compound; /* UNIMPLEMENTED */

    // is_member_pointer
    // -------------------------------------------------------------------------
    template<class T> struct is_member_pointer; /* UNIMPLEMENTED */

    //--------------------------------------------------------------------------
    // 20.15.4.3 Type Properties
    //--------------------------------------------------------------------------
    
    // is_const
    // -------------------------------------------------------------------------
    template <class> struct is_const : false_type {};
    template <class T> struct is_const<const T> : true_type {}; 

    // is_volatile
    // -------------------------------------------------------------------------
    template <class> struct is_volatile : false_type {};
    template <class T> struct is_volatile<volatile T> : true_type {};

    template <class T> struct is_trivial; /* UNIMPLEMENTED */
    template <class T> struct is_trivially_copyable; /* UNIMPLEMENTED */
    template <class T> struct is_standard_layout; /* UNIMPLEMENTED */
    template <class T> struct is_empty; /* UNIMPLEMENTED */
    template <class T> struct is_polymorphic; /* UNIMPLEMENTED */
    template <class T> struct is_abstract; /* UNIMPLEMENTED */
    template <class T> struct is_final; /* UNIMPLEMENTED */
    template <class T> struct is_aggregate; /* UNIMPLEMENTED */
    template <class T> struct is_signed; /* UNIMPLEMENTED */
    template <class T> struct is_unsigned; /* UNIMPLEMENTED */
    template <class T> struct is_bounded_array; /* UNIMPLEMENTED */
    template <class T> struct is_unbounded_array; /* UNIMPLEMENTED */
    template <class T, class... Args> struct is_constructible; /* UNIMPLEMENTED */
    template <class T> struct is_default_constructible; /* UNIMPLEMENTED */
    template <class T> struct is_copy_constructible; /* UNIMPLEMENTED */
    template <class T> struct is_move_constructible; /* UNIMPLEMENTED */
    template <class T, class U> struct is_assignable; /* UNIMPLEMENTED */
    template <class T> struct is_copy_assignable; /* UNIMPLEMENTED */
    template <class T> struct is_move_assignable; /* UNIMPLEMENTED */
    template <class T, class U> struct is_swappable_with; /* UNIMPLEMENTED */
    template <class T> struct is_swappable; /* UNIMPLEMENTED */
    template <class T> struct is_destructible; /* UNIMPLEMENTED */
    template <class T, class... Args> struct is_trivially_constructible; /* UNIMPLEMENTED */
    template <class T> struct is_trivially_default_constructible; /* UNIMPLEMENTED */
    template <class T> struct is_trivially_copy_constructible; /* UNIMPLEMENTED */
    template <class T> struct is_trivially_move_constructible; /* UNIMPLEMENTED */
    template <class T, class U> struct is_trivially_assignable; /* UNIMPLEMENTED */
    template <class T> struct is_trivially_copy_assignable; /* UNIMPLEMENTED */
    template <class T> struct is_trivially_move_assignable; /* UNIMPLEMENTED */
    template <class T> struct is_trivially_destructible; /* UNIMPLEMENTED */
    template <class T, class... Args> struct is_nothrow_constructible; /* UNIMPLEMENTED */
    template <class T> struct is_nothrow_default_constructible; /* UNIMPLEMENTED */
    template <class T> struct is_nothrow_copy_constructible; /* UNIMPLEMENTED */
    template <class T> struct is_nothrow_move_constructible; /* UNIMPLEMENTED */
    template <class T, class U> struct is_nothrow_assignable; /* UNIMPLEMENTED */
    template <class T> struct is_nothrow_copy_assignable; /* UNIMPLEMENTED */
    template <class T> struct is_nothrow_move_assignable; /* UNIMPLEMENTED */

    //--------------------------------------------------------------------------
    // 20.15.5 Type Property Queries
    //--------------------------------------------------------------------------
    
    // alignment_of
    // -------------------------------------------------------------------------
    template <class T> struct alignment_of 
        : integral_constant<size_t, alignof(T)> {};

    // rank
    // -------------------------------------------------------------------------
    template <class> struct rank 
        : integral_constant<size_t, 0> {};

    template <class T> struct rank<T[]> 
        : integral_constant<size_t, rank<T>::value + 1> {};

    template <class T, size_t N> struct rank<T[N]> 
        : integral_constant<size_t, rank<T>::value + 1> {};

    // extent
    // -------------------------------------------------------------------------
    template <class T, unsigned I = 0> struct extent 
        : integral_constant<size_t, 0> {}; 
    
    template <class T> struct extent<T[], 0>
        : integral_constant<size_t, 0> {};
    
    template <class T, size_t N> struct extent<T[N], 0>
        : integral_constant<size_t, N> {}; 

    template <class T, unsigned I> struct extent<T[],I>
        : integral_constant<size_t, extent<T,I - 1>::value> {};

    template <class T, unsigned I, size_t N> struct extent<T[N],I>
        : integral_constant<size_t, extent<T,I - 1>::value> {};

    //--------------------------------------------------------------------------
    // 20.15.6 Type Relations
    // --------------------------------------------------------------------------

    // is_same
    // -------------------------------------------------------------------------
    template <class, class> struct is_same : false_type {};
    template <class T> struct is_same<T,T> : true_type {};

    template <class Base, class Derived> struct is_base_of; /* UNIMPLEMENTED */
    template <class From, class To> struct is_convertible; /* UNIMPLEMENTED */
    template <class From, class To> struct is_nothrow_convertible; /* UNIMPLEMENTED */
    template <class T, class U> struct is_layout_compatible; /* UNIMPLEMENTED */
    template <class Base, class Derived> struct is_pointer_interconvertible_base_of; /* UNIMPLEMENTED */
    template <class Fn, class... ArgTypes> struct is_invocable; /* UNIMPLEMENTED */
    template <class R, class Fn, class... ArgTypes> struct is_invocable_r; /* UNIMPLEMENTED */
    template <class Fn, class... ArgTypes> struct is_nothrow_invocable; /* UNIMPLEMENTED */
    template <class R, class Fn, class... ArgTypes> struct is_nothrow_invocable_r; /* UNIMPLEMENTED */

    //--------------------------------------------------------------------------
    // 20.15.7.1 Const-Volatile Modifications
    //--------------------------------------------------------------------------

    // remove_const
    // -------------------------------------------------------------------------
    template <class T> struct remove_const 
        { using type = T; };

    template <class T> struct remove_const<const T> 
        { using type = T; };

    // remove_volatile
    // -------------------------------------------------------------------------
    template <class T> struct remove_volatile
        { using type = T; };
    
    template <class T> struct remove_volatile<volatile T>
        { using type = T; }; 

    // remove_cv
    // -------------------------------------------------------------------------
    // FIX redefinition due to ordering
    //
    // template <class T> struct remove_cv
    //     { using type = remove_volatile<remove_const<T>>; };
    
    // add_const
    // -------------------------------------------------------------------------
    template <class T> struct add_const
        { using type = T const; };
        
    // add_volatile
    // -------------------------------------------------------------------------
    template <class T> struct add_volatile
        { using type = T volatile; };

    // add_cv
    // -------------------------------------------------------------------------
    template <class T> struct add_cv
        { using type = T const volatile; };


    // template <class T> using remove_const_t = typename remove_const<T>::type; /* UNIMPLEMENTED */
    // template <class T> using remove_volatile_t = typename remove_volatile<T>::type; /* UNIMPLEMENTED */
    // template <class T> using remove_cv_t = typename remove_cv<T>::type; /* UNIMPLEMENTED */
    // template <class T> using add_const_t = typename add_const<T>::type; /* UNIMPLEMENTED */
    // template <class T> using add_volatile_t = typename add_volatile<T>::type; /* UNIMPLEMENTED */
    // template <class T> using add_cv_t = typename add_cv<T>::type; /* UNIMPLEMENTED */

    //--------------------------------------------------------------------------
    // 20.15.7.2 Reference Modifications
    //--------------------------------------------------------------------------
    
    // remove_reference
    // -------------------------------------------------------------------------
    template <class T> struct remove_reference
        { using type = T; };

    template <class T> struct remove_reference<T&>
        { using type = T; };

    template <class T> struct remove_reference<T&&>
        { using type = T; };

    // add_lvalue_reference
    // -------------------------------------------------------------------------
    namespace {
        template <class T, class = void> struct _add_lvalue_reference_helper
            { using type = T; };
        
        template <class T> struct _add_lvalue_reference_helper<T,_void_t<T&>>
            { using type = T&; };
    }

    template <class T> struct add_lvalue_reference
        : _add_lvalue_reference_helper<T> {};
    
    static_assert(std::is_same_v<add_lvalue_reference<int>::type, 
                                 int&>);

    // SUBSECTION
    // -------------------------------------------------------------------------

}

#endif