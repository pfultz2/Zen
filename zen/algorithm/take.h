/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    take.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_TAKE_H
#define ZEN_GUARD_ALGORITHM_TAKE_H

#include <zen/algorithm/at.h>
#include <zen/range/iterator_range.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((take)(auto r, n)
    if (is_range<r>)(make_iterator_range(boost::begin(r), detail::iterator_at(r, n)))

)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>

ZEN_TEST_CASE(take_test)
{
    std::vector<int> v1 = boost::assign::list_of(1)(2)(3);
    std::vector<int> v2 = boost::assign::list_of(1)(2);
    
    ZEN_TEST_CHECK(zen::equal(v1 | zen::take(2), v2));
    ZEN_TEST_CHECK(zen::equal(zen::take(v1, 2), v2));
}

#endif

#endif
