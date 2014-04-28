/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    cycle.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_CYCLE_H
#define ZEN_GUARD_ALGORITHM_CYCLE_H

// #include <zen/traits.h>
// #include <boost/range/begin.hpp>
// #include <boost/range/end.hpp>

#include <zen/function/builder.h>
#include <zen/range/cycle.h>
// #include <zen/range/iterator_range.h>
// #include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((cycle)(auto&& r)
    if (_p<is_range>(r))(zen::make_cycle_range(r))
    def(auto&& r, unsigned int n)
    if (_p<is_range>(r))(zen::make_cycle_range(r, n))
)

// ZEN_FUNCTION_PIPE_OBJECT((cycle)(auto&& r, unsigned int n)
//     if (_p<is_range>(r))(zen::make_cycle_range(r, n))
// )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>


ZEN_TEST_CASE(cycle_test)
{
    std::vector<int> v1 = boost::assign::list_of(1)(2);
    std::vector<int> v2 = boost::assign::list_of(1)(2)(1)(2)(1)(2);

    ZEN_TEST_EQUAL(zen::cycle(v1, 3), v2);
    ZEN_TEST_EQUAL(v1 | zen::cycle(3), v2);
    ZEN_TEST_EQUAL(v1 | zen::cycle(1), v1);
}

#endif

#endif
