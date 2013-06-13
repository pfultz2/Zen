/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    iterate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_ITERATE_H
#define ZEN_GUARD_RANGE_ITERATE_H

#include <zen/range/unfold.h>
#include <boost/optional.hpp>

namespace zen { 

namespace detail {

struct just
{
    template<class T>
    boost::optional<T> operator()(T x) const
    {
        return x;
    }
};

}


ZEN_FUNCTION_OBJECT((iterate)(init, f)(unfold(init, detail::just(), f)))

}

#endif
