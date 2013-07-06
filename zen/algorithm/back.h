/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    back.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_BACK_H
#define ZEN_GUARD_ALGORITHM_BACK_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <zen/algorithm/empty.h>

#include <boost/fusion/sequence/intrinsic/back.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <algorithm>

#include <zen/assert.h>

namespace zen { 

// TODO: Change assert for sequence to a static assert
ZEN_FUNCTION_PIPE_OBJECT((back)(auto r)
        if (is_sequence<r>)(ZEN_ASSERT_EXPR(!zen::empty(r), boost::fusion::back(r)))
        else if (has_range_traversal<r, boost::bidirectional_traversal_tag>)
        (
            ZEN_ASSERT_EXPR(!zen::empty(r), *(--boost::end(r)))
        ) 

    )  

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(back_test)
{
    std::vector<int> v1 = boost::assign::list_of(0)(1)(2)(3)(4);
    
    ZEN_TEST_EQUAL(4, v1 | zen::back);
}

#endif

#endif
