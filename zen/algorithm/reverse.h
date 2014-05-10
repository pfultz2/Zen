/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    reverse.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_REVERSE_H
#define ZEN_GUARD_ALGORITHM_REVERSE_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>
#include <zen/range/reverse_range.h>

#include <boost/fusion/algorithm/transformation/reverse.hpp>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((reverse)(auto&& r)
    if (_p<is_reversible_range>(r))
    (
        zen::make_reverse_range(ZEN_AUTO_FORWARD(r))
    )
    else if (_p<boost::fusion::traits::is_sequence>(r))
    (
        boost::fusion::reverse(ZEN_AUTO_FORWARD(r))
    )
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>

ZEN_TEST_CASE(reverse_test)
{
    std::vector<int> v1 = { 0, 1, 2, 3, 4 };
    std::vector<int> v2 = { 4, 3, 2, 1, 0 };
    
    ZEN_TEST_EQUAL(v2, zen::reverse(v1));
    ZEN_TEST_EQUAL(v2, v1 | zen::reverse);

    boost::fusion::vector<int, int, int> vs1(1, 2, 3);
    boost::fusion::vector<int, int, int> vs2(3, 2, 1);

    ZEN_TEST_EQUAL(vs2, zen::reverse(vs1));
    ZEN_TEST_EQUAL(vs2, vs1 | zen::reverse);
}

#endif

#endif
