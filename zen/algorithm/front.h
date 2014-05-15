/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    front.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FRONT_H
#define ZEN_GUARD_ALGORITHM_FRONT_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>
#include <zen/algorithm/empty.h>

#include <boost/fusion/sequence/intrinsic/front.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <algorithm>

#include <zen/assert.h>

namespace zen { 

// TODO: Change assert for sequence to a static assert
ZEN_FUNCTION_PIPE_OBJECT((front)(auto&& r)
        if (_p<boost::fusion::traits::is_sequence>(r))(ZEN_ASSERT_EXPR(!zen::empty(r), boost::fusion::front(r)))
        else if (_p<is_range>(r))
        (
            ZEN_ASSERT_EXPR(!zen::empty(r), *(zen::begin(r)))
        ) 

    )  

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>

ZEN_TEST_CASE(front_test)
{
    std::vector<int> v1 = {0,1,2,3,4};
    
    ZEN_TEST_EQUAL(0, zen::front(v1));
    ZEN_TEST_EQUAL(0, v1 | zen::front);
}

#endif

#endif
