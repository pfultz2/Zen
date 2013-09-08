/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    replace_if.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_REPLACE_IF_H
#define ZEN_GUARD_ALGORITHM_REPLACE_IF_H

#include <zen/algorithm/transform.h>
#include <zen/function/partial.h>

namespace zen { 

namespace detail {

ZEN_FUNCTION_CLASS((replacer_if)(auto f, auto new_value, auto x)
    (
        f(x) ? new_value : x
    ))

}

ZEN_FUNCTION_PIPE_OBJECT((replace_if)(auto r, f, auto new_value)
    if (is_range_or_sequence<r>)
        (
            zen::transform(r, partial(detail::replacer_if())(f, new_value))
        )

    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <zen/function/always.h>

ZEN_TEST_CASE(replace_if_test)
{
    std::vector<int> v1 = boost::assign::list_of(0)(1)(2)(3)(4);
    std::vector<int> v2 = boost::assign::list_of(99)(99)(99)(99)(99);
    
    ZEN_TEST_EQUAL(v2, zen::replace_if(v1, zen::always(true), 99));
    ZEN_TEST_EQUAL(v2, v1 | zen::replace_if(zen::always(true), 99));
}

#endif

#endif
