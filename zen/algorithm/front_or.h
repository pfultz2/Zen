/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    front_or.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FRONT_OR_H
#define ZEN_GUARD_ALGORITHM_FRONT_OR_H

#include <zen/algorithm/front.h>

#include <algorithm>

#include <zen/assert.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((front_or)(auto &&r, auto&& x)
        if (_p<boost::fusion::traits::is_sequence>(r) or _p<is_range>(r))
        (
            (zen::empty(r)) ? std::forward<decltype(x)>(x) : zen::front(r)
        )
    )  

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(front_or_test)
{
    std::vector<int> v1 = {0,1,2,3,4};
    std::vector<int> v2;
    
    ZEN_TEST_EQUAL(0, v1 | zen::front_or(1));
    ZEN_TEST_EQUAL(1, v2 | zen::front_or(1));
    
    ZEN_TEST_EQUAL(0, zen::front_or(v1, 1));
    ZEN_TEST_EQUAL(1, zen::front_or(v2, 1));
}

#endif

#endif
