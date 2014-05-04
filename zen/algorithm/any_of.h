/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    any_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_ANY_OF_H
#define ZEN_GUARD_ALGORITHM_ANY_OF_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>

#include <boost/fusion/algorithm/query/any.hpp>
#include <boost/fusion/support/is_sequence.hpp>

#include <algorithm>


namespace zen { 


ZEN_FUNCTION_PIPE_OBJECT((any_of)(const auto& r, auto f)
        if (_p<boost::fusion::traits::is_sequence>(r))(boost::fusion::any(r, f))
        else if (_p<is_range_unary_predicate>(r, f))(std::find_if(zen::begin(r), zen::end(r), f) != zen::end(r))

    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/sequence/io.hpp>
#include <zen/algorithm/detail/is_odd.h>
#include <zen/traits/trait_check.h>

ZEN_TEST_CASE(any_of_test)
{
    std::vector<int> v1 = {1, 2};
    std::vector<int> v2 = {2, 4};

    ZEN_TEST_CHECK(zen::any_of(v1, is_odd()));
    ZEN_TEST_CHECK(!zen::any_of(v2, is_odd()));
    
    ZEN_TEST_CHECK(zen::any_of(boost::fusion::make_vector(1,2), is_odd()));
    ZEN_TEST_CHECK(!zen::any_of(boost::fusion::make_vector(2,4), is_odd()));
}

#endif

#endif
