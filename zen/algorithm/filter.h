/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    filter.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FILTER_H
#define ZEN_GUARD_ALGORITHM_FILTER_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>
#include <zen/range/filter.h>

#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((filter)(auto&& r, auto f)
    if (_p<is_range_unary_predicate>(r, f))(zen::make_filter_range(r, f))

)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <zen/algorithm/detail/is_odd.h>

ZEN_TEST_CASE(filter_test)
{
    std::vector<int> v1 = { 1, 2, 3 };
    std::vector<int> v2 = { 1, 3 };
    
    ZEN_TEST_EQUAL(zen::filter(v1, is_odd()), v2);
    // ZEN_TEST_EQUAL(v1 | zen::filter(is_odd()), v2);
}

#endif

#endif
