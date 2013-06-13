/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    generate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_GENERATE_H
#define ZEN_GUARD_RANGE_GENERATE_H

#include <zen/range/unfold.h>
#include <boost/bind.hpp>

namespace zen {

namespace detail {

struct ignore {};

struct identity
{
    template<class T>
    T operator()(T x) const
    {
        return x;
    }
};

}

ZEN_FUNCTION_OBJECT((generate)(gen)
    (
        unfold(detail::ignore(), boost::bind(gen), detail::identity())
    ))

}

#endif
