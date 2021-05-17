#ifndef HLIB_TYPES_UNIQUE_H_
#define HLIB_TYPES_UNIQUE_H_

// IDEAS
//==============================================================================
// extent_list - Gives typedef of a template list of the extent lengths of some
//               mutltidimensional array.

namespace hlib {
    using std::size_t;

    // is_same_template
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


    // is_instantiated_from
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

    // remove_n_extents
    //--------------------------------------------------------------------------
    // Conforms to Cpp17TransformationTrait.
    // Removes N extents. If type has less than N extents, remove all extents.

    // structs
    template <class T, size_t N> struct remove_n_extents 
        { using type = T; };
    
    // helper
    template <class T, size_t N>
    using remove_n_extents_t = remove_n_extents<T,N>::type; 
}

#endif