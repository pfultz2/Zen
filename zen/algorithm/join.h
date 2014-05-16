/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    join.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_JOIN_H
#define ZEN_GUARD_ALGORITHM_JOIN_H

#include <zen/function/builder.h>
#include <zen/range/join_range.h>
#include <zen/range/iterator_range.h>

#include <boost/fusion/algorithm/transformation/join.hpp>

namespace zen { 
// TODO: Make this varidiac
ZEN_FUNCTION_PIPE_OBJECT((join)(auto&& x, auto&& y)
    if (_p<is_range>(x) and _p<is_range>(y))(zen::forward_as<join_range>(ZEN_AUTO_FORWARD(x), ZEN_AUTO_FORWARD(y)))
    else if (_p<boost::fusion::traits::is_sequence>(x) and _p<boost::fusion::traits::is_sequence>(y))(boost::fusion::join(x, y))
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>


ZEN_TEST_CASE(join_test)
{
    std::vector<int> v1 = { 1, 2 };
    std::vector<int> v2 = { 3, 4 };
    std::vector<int> v3 = { 1, 2, 3, 4 };
    // TODO: Add test for fusion sequence    
    ZEN_TEST_EQUAL(v1 | zen::join(v2), v3);
    ZEN_TEST_EQUAL(zen::join(v1, v2), v3);
}

#endif

#endif
