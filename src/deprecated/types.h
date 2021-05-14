#ifndef MYREGEX_TYPES_H_
#define MYREGEX_TYPES_H_

#include <iostream>
#include <concepts>
#include <type_traits>
#include <ostream>
#include <tuple>

// conditional

template <bool B, class T, class F>
struct conditional {
    using type = T;
};

template <class T, class F>
struct conditional<false, T, F> { 
    using type = F;
};

template <bool B, class T, class F>
using conditional_t = typename conditional<B,T,F>::type;

// is_same

template <class T, class U> 
struct is_same : std::false_type {};

template <class T> 
struct is_same<T,T> : std::true_type {};

template <class T, class U> 
constexpr bool is_same_v = is_same<T,U>::value;

// is_all_same

// intentionally require at least 2 arguments
template <class T, class U, class...V>
struct is_all_same : std::bool_constant<is_same_v<T,U> && (is_same_v<T,V> && ...)> {};

// using same args for clarity i suppose, not neccessity
template <class T, class U, class...V>
constexpr bool is_all_same_v = is_all_same<T,U,V...>::value;

static_assert(is_all_same_v<int,int,int>);
static_assert(!is_all_same_v<int,int,bool>);

// is_same_template

template <template <class...> class T, template <class...> class U>
struct is_same_template : std::false_type {};

template <template <class...> class T>
struct is_same_template<T,T> : std::true_type {};

template <template <class...> class T, template <class...> class U>
constexpr const bool is_same_template_v = is_same_template<T,U>::value;

template <template <class...> class T, template <class...> class U>
concept same_template_as = is_same_template_v<T,U>;

// is_specialization 

template <class T, template <class...> class U>
struct is_specialization : std::false_type {};

template <class...P, template <class...> class U>
struct is_specialization<U<P...>,U> : std::true_type {};

template <class T, template <class...> class U>
constexpr bool is_specialization_v = is_specialization<T,U>::value;

template <class T, template <class...> class U>
concept specialization_of = is_specialization_v<T,U>;

// is_from_same_template
//
// intentionally non-implemented for non templated types
// makes intention clear

template <class T, class U>
struct is_from_same_template;

template <template <class...> class T, template <class...> class U, class...A, class...B>
struct is_from_same_template<T<A...>, U<B...>> : std::false_type {};

template <template <class...> class T, class...A, class...B>
struct is_from_same_template<T<A...>, T<B...>> : std::true_type {};

template <class T, class U>
constexpr bool is_from_same_template_v = is_from_same_template<T,U>::value;

template <class T, class U>
concept from_same_template_as = is_from_same_template_v<T,U>;


// concat 

template <class T, class U>
struct concat;

template <class...T, class...U>
struct concat<std::tuple<T...>, std::tuple<U...>> {
    using type = std::tuple<T...,U...>;
};

template <class...T, class P, class Q>
struct concat<std::tuple<T...>, std::pair<P,Q>> {
    using type = std::tuple<T...,P,Q>;
};

template <class P, class Q, class...T>
struct concat<std::pair<P,Q>, std::tuple<T...>> {
    using type = std::tuple<T...,P,Q>;
};

template <class P, class Q, class U, class V>
struct concat<std::pair<P,Q>, std::pair<U,V>> {
    using type = std::tuple<P,Q,U,V>;
};

template <class T, class U>
using concat_t = typename concat<T,U>::type;

// prepend

template <class T, class U>
struct prepend;

template <class...T, class U>
struct prepend<std::tuple<T...>,U> {
    using type = std::tuple<U,T...>;
};

template <class T, class U>
using prepend_t = typename prepend<T,U>::type;

// append

template <class T, class U> 
struct append;

template <template <class...> class Template, class...M, class T>
struct append<Template<M...>,T> {
    using type = Template<M...,T>;
};

template <class T, class U>
using append_t = typename append<T,U>::type;

#endif
