#ifndef HLIB_SEQUENCE_H_
#define HLIB_SEQUENCE_H_

#include <ostream>
#include <concepts>
#include <type_traits>

#include "types.h"

namespace hlib {

    template <template <class MemberType, MemberType...Members> class Template, class MemberType, MemberType...Members>
        std::ostream& operator<<(std::ostream& os, const Template<MemberType, Members...>& seq) {
        if constexpr (sizeof...(Members) > 0) {
            return os << "[", (...,(os << Members << ", ")) << "\b\b]";
        } else {
            return os << "[]";
        }
    }

    namespace experimental {

    }

    template <class IntType, IntType...Ints>
    struct integer_sequence {
        using int_type = IntType;

        constexpr std::size_t size() { 
            return sizeof...(Ints); 
        }
    };

    // prepend sequence

    template <class Template, auto Member>
    struct prepend_sequence;

    template <template <class MemberType, MemberType...Members> class Template, class MemberType, MemberType...Members, MemberType NewMember>
    struct prepend_sequence<Template<MemberType, Members...>, NewMember>  {
        using type = Template<MemberType, NewMember, Members...>;
    };

    template <class Template, auto NewMember>
    using prepend_sequence_t = typename prepend_sequence<Template,NewMember>::type;


    // append sequence

    template <class Sequence, auto NewMember>
    struct append_sequence;

    template <template <class MemberType, MemberType...> class Template, class MemberType, MemberType...Members, MemberType NewMember>
    struct append_sequence<Template<MemberType, Members...>, NewMember> {
        using type = Template<MemberType, Members..., NewMember>;
    };

    template <class Sequence, auto NewMember>
    using append_sequence_t = typename append_sequence<Sequence, NewMember>::type;

    // reverse 

    // template <class T>
    // struct reverse;

    // template <template <class...> class Template, class Head, class...Tail>
    // struct reverse<Template<Head,Tail...>> { 
    //     using type = append_t<reverse<Template<Tail...>>, Head>;
    // };

    // range sequence
    namespace {
        // implementation
        template <class IntType, IntType Begin, IntType End, IntType Step, bool LessThan>
        struct range_sequence_impl;

        template <class IntType, IntType Begin, IntType End, IntType Step>
        struct range_sequence_impl<IntType,Begin,End,Step,false> {
            using type = integer_sequence<IntType>;
        };

        template <class IntType, IntType Begin, IntType End, IntType Step>
        struct range_sequence_impl<IntType,Begin,End,Step,true> {
            using type = prepend_sequence_t<typename range_sequence_impl<IntType, (Begin + Step), End, Step, (Begin + Step < End)>::type, Begin>;
        };
    }

    template <class IntType, IntType Begin, IntType End, IntType Step = 1>
    struct range_sequence_base {
        using int_type = IntType;

        static constexpr int_type begin = Begin;
        static constexpr int_type end = End;
        static constexpr int_type step = Step;

        using type = typename range_sequence_impl<int_type, begin, end, step, (begin < end)>::type;
    };

    template <class IntType, IntType...Params>
    struct range_sequence;

    template <class IntType, IntType Begin, IntType End, IntType Step>
    struct range_sequence<IntType, Begin, End, Step> : range_sequence_base<IntType,Begin,End,Step> {};

    template <class IntType, IntType Begin, IntType End>
    struct range_sequence<IntType, Begin, End> : range_sequence_base<IntType,Begin,End> {};

    template <class IntType, IntType End> 
    struct range_sequence<IntType, End> : range_sequence_base<IntType,0,End> {};

    template <class IntType, IntType...Params>
    using range_sequence_t = typename range_sequence<IntType,Params...>::type; 

    namespace experimental {
        // heterogeneous sequence

        template <auto...Member>
        struct heterogeneous_sequence { 
            // using type = ????
        };

        // homogeneous sequence

        template <auto Member0, decltype(Member0)...MemberN>
        struct homogeneous_sequence { 
            using type = decltype(Member0); 
        };
    }

    template <class T, class U>
    struct concat_sequence;

    template <template <class MemberType, MemberType...M> class Sequence,
              class MemberType,
              MemberType...M1,
              MemberType...M2>
    struct concat_sequence<Sequence<MemberType,M1...>,
                           Sequence<MemberType,M2...>> {
        using type = Sequence<MemberType,M1...,M2...>;
    };

    template <class T, class U>
    using concat_sequence_t = typename concat_sequence<T,U>::type;

    namespace {
        template <class IntType, IntType Left, IntType Right>
        struct index_sequence_impl  {
            using type = concat_sequence_t<typename index_sequence_impl<IntType, Left, (Left + Right) / 2>::type,
                                           typename index_sequence_impl<IntType, ((Left + Right) / 2) + 1, Right>::type>;
        };

        template <class IntType, IntType Mid>
        struct index_sequence_impl<IntType, Mid, Mid>  {
            using type = integer_sequence<IntType, Mid>;
        };

        template <class IntType, IntType Begin, IntType End>
            requires (0 <= Begin) && (Begin <= End)
        struct index_sequence_base {
            using int_type = IntType;

            static constexpr int_type begin = Begin;
            static constexpr int_type end = End;

            using type = typename index_sequence_impl<int_type, begin, end>::type;
        };
    }

    template <class IntType, IntType...Params>
    struct index_sequence;

    template <class IntType, IntType Begin, IntType End>
    struct index_sequence<IntType,Begin,End> : index_sequence_base<IntType, Begin, End> {};

    template <class IntType, IntType End>
    struct index_sequence<IntType,End> : index_sequence_base<IntType, 0, End> {};

    template <class IntType, IntType...Params>
    using index_sequence_t = typename index_sequence<IntType,Params...>::type;
}

#endif