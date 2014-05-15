/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    find_if.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FIND_IF_H
#define ZEN_GUARD_ALGORITHM_FIND_IF_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>
#include <zen/algorithm/detail/make_find_range.h>
#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((find_if)(auto&& r, auto f)
        if (_p<is_range>(r))
        (
            detail::make_find_range(ZEN_AUTO_FORWARD(r), std::find_if(zen::begin(r), zen::end(r), f))
        )
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <zen/algorithm/detail/is_odd.h>

ZEN_TEST_CASE(find_if_test)
{
    std::vector<int> v1 = {2, 3, 4};
    std::vector<int> v2 = {3};

    ZEN_TEST_EQUAL(v1 | zen::find_if(is_odd()), v2);
}

#endif

#endif
