/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    front_or.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FRONT_OR_H
#define ZEN_GUARD_ALGORITHM_FRONT_OR_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <zen/algorithm/empty.h>
#include <zen/algorithm/front.h>

#include <algorithm>

#include <zen/assert.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((front_or)(auto r, auto x)
        if (is_range_or_sequence<r>)
        (
            (zen::empty(r)) ? zen::forward<ZEN_XTYPEOF_TPL(x)>(x) : zen::front(r)
        )
    )  

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(front_or_test)
{
    std::vector<int> v1 = boost::assign::list_of(0)(1)(2)(3)(4);
    std::vector<int> v2;
    
    ZEN_TEST_EQUAL(0, v1 | zen::front_or(1));
    ZEN_TEST_EQUAL(1, v2 | zen::front_or(1));
    
    ZEN_TEST_EQUAL(0, zen::front_or(v1, 1));
    ZEN_TEST_EQUAL(1, zen::front_or(v2, 1));
}

#endif

#endif
