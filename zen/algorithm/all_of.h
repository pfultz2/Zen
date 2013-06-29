/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    all_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_ALL_OF_H
#define ZEN_GUARD_ALGORITHM_ALL_OF_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <zen/algorithm/any_of.h>
#include <algorithm>

#include <zen/function/compose.h>
#include <functional>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((all_of)(const r, f)
        if (is_range_or_sequence<r>)
        (
            not any_of(r, zen::compose(f, std::logical_not<bool>()))
        )
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <zen/algorithm/detail/is_odd.h>


ZEN_TEST_CASE(all_of_test)
{
    std::vector<int> v1 = boost::assign::list_of(1)(3);
    std::vector<int> v2 = boost::assign::list_of(1)(2);
    
    ZEN_TEST_CHECK(zen::all_of(v1, is_odd()));
    ZEN_TEST_CHECK(!zen::all_of(v2, is_odd()));
    
    ZEN_TEST_CHECK(zen::all_of(boost::fusion::make_vector(1,3), is_odd()));
    ZEN_TEST_CHECK(!zen::all_of(boost::fusion::make_vector(1,2), is_odd()));
}

#endif

#endif
