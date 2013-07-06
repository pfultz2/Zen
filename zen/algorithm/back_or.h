/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    back_or.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_BACK_OR_H
#define ZEN_GUARD_ALGORITHM_BACK_OR_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <zen/algorithm/empty.h>
#include <zen/algorithm/back.h>

#include <algorithm>

#include <zen/assert.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((back_or)(auto r, auto x)
        if (is_range_or_sequence<r>)
        (
            (zen::empty(r)) ? zen::forward<ZEN_XTYPEOF_TPL(x)>(x) : zen::back(r)
        )
    )  

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(back_or_test)
{
    std::vector<int> v1 = boost::assign::list_of(0)(1)(2)(3)(4);
    std::vector<int> v2;
    
    ZEN_TEST_EQUAL(4, v1 | zen::back_or(1));
    ZEN_TEST_EQUAL(1, v2 | zen::back_or(1));
    
    ZEN_TEST_EQUAL(4, zen::back_or(v1, 1));
    ZEN_TEST_EQUAL(1, zen::back_or(v2, 1));
}

#endif

#endif
