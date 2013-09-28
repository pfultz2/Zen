/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    split_if.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_SPLIT_IF_H
#define ZEN_GUARD_ALGORITHM_SPLIT_IF_H

#include <zen/algorithm/drop_while.h>
#include <zen/algorithm/take_while.h>
#include <zen/range/iterator_range.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((split_if)(auto r, n)
    if (is_range<r>)(std::make_pair(take_while(r, n), drop_while(r, n)))

)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <zen/algorithm/detail/is_odd.h>

ZEN_TEST_CASE(split_if_test)
{
    std::vector<int> v = boost::assign::list_of(1)(2)(3)(4);
    std::vector<int> v1 = boost::assign::list_of(1);
    std::vector<int> v2 = boost::assign::list_of(2)(3)(4);
    
    ZEN_TEST_EQUAL(zen::split_if(v, is_odd()).first, v1);
    ZEN_TEST_EQUAL(zen::split_if(v, is_odd()).second, v2);
}
#endif

#endif
