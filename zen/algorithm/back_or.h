/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    back_or.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_BACK_OR_H
#define ZEN_GUARD_ALGORITHM_BACK_OR_H

#include <zen/algorithm/back.h>

#include <algorithm>

#include <zen/assert.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((back_or)(auto &&r, auto&& x)
        if (_p<boost::fusion::traits::is_sequence>(r) or _p<is_reversible_range>(r))
        (
            (zen::empty(r)) ? std::forward<decltype(x)>(x) : zen::back(r)
        )
    )  

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(back_or_test)
{
    std::vector<int> v1 = {0,1,2,3,4};
    std::vector<int> v2;
    
    ZEN_TEST_EQUAL(4, v1 | zen::back_or(1));
    ZEN_TEST_EQUAL(1, v2 | zen::back_or(1));
    
    ZEN_TEST_EQUAL(4, zen::back_or(v1, 1));
    ZEN_TEST_EQUAL(1, zen::back_or(v2, 1));
}

#endif

#endif
