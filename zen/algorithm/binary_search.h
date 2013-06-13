/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    binary_search.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_BINARY_SEARCH_H
#define ZEN_GUARD_ALGORITHM_BINARY_SEARCH_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <zen/algorithm/any_of.h>
#include <algorithm>

#include <boost/bind.hpp>
#include <functional>

namespace zen { 

namespace detail {

struct binary_search_f
{
    template<class Range, class T>
    typename boost::range_reference<Range>::type
    operator()(ZEN_FORWARD_REF(Range) r, const T& x) const
    {
        return std::binary_search(r, x);
    }

    template<class Range, class T, class Compare>
    typename boost::range_reference<Range>::type
    operator()(ZEN_FORWARD_REF(Range) r, const T& x, Compare c) const
    {
        return std::binary_search(r, x, c);
    }
};

}

zen::static_<zen::pipable_adaptor<detail::binary_search_f> > binary_search = {};

}

#endif
