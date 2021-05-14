#ifndef HLIB_INT_SEQUENCE_H_
#define HLIB_INT_SEQUENCE_H_

#include <concepts>

namespace hlib {
    //--------------------------------------------------------------------------
    // integer_sequence<class IntType, IntType...Seq>
    //--------------------------------------------------------------------------

    template <std::integral IntType>
    struct integer_sequence {
        using int_type = IntType;
    };
}

#endif