/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    count_if.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_COUNT_IF_H
#define ZEN_GUARD_ALGORITHM_COUNT_IF_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>

#include <boost/fusion/algorithm/query/count_if.hpp>
#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((count_if)(auto r, f)
        if (_p<is_sequence>(r))(boost::fusion::count_if(r, f))
        else if (_p<is_range>(r))(std::count_if(zen::begin(r), zen::end(r), f))
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <zen/algorithm/detail/is_odd.h>


ZEN_TEST_CASE(count_if_test)
{
    std::vector<int> v = {1, 2, 3};
    
    ZEN_TEST_EQUAL(2, zen::count_if(v, is_odd()));
    
    ZEN_TEST_EQUAL(2, zen::count_if(boost::fusion::make_vector(1,2,3), is_odd()));
}

#endif

#endif
