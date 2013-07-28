/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    find_if.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FIND_IF_H
#define ZEN_GUARD_ALGORITHM_FIND_IF_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((find_if)(auto r, f)
        if (is_range<r>)(std::find_if(boost::begin(r), boost::end(r), f))
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <zen/algorithm/detail/is_odd.h>

ZEN_TEST_CASE(find_if_test)
{
    std::vector<int> v1 = boost::assign::list_of(2)(3)(4);
    
    ZEN_TEST_CHECK(v1 | zen::find_if(is_odd()), 3);
}

#endif

#endif
