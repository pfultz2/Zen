/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    placeholders.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_PLACEHOLDERS_H
#define ZEN_GUARD_FUNCTION_PLACEHOLDERS_H

#include <functional>

// Unify placeholders

namespace zen { namespace ph {
using namespace std::placeholders;
}}

namespace std {
    template<int N>
    struct is_placeholder<boost::mpl::arg<N>> 
    : integral_constant<int, N> 
    {};
}

#endif
