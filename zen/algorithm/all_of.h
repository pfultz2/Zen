/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    all_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_ALL_OF_H
#define ZEN_GUARD_ALGORITHM_ALL_OF_H

#include <zen/algorithm/any_of.h>


namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((all_of)(const auto& r, auto f)
        if (_p<is_range_unary_predicate>(r, f) or _p<boost::fusion::traits::is_sequence>(r))
        (
            not any_of(r, [&](const auto& x){ return not f(x); })
        )
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/sequence/io.hpp>
#include <zen/algorithm/detail/is_odd.h>
#include <zen/function/reveal.h>


ZEN_TEST_CASE(all_of_test)
{
    std::vector<int> v1 = {1, 3};
    std::vector<int> v2 = {1, 2};
    
    ZEN_TEST_CHECK(zen::reveal(zen::all_of)(v1, is_odd()));
    ZEN_TEST_CHECK(!zen::all_of(v2, is_odd()));

    ZEN_TEST_CHECK(v1 | zen::all_of(is_odd()));
    
    ZEN_TEST_CHECK(zen::all_of(boost::fusion::make_vector(1,3), is_odd()));
    ZEN_TEST_CHECK(!zen::all_of(boost::fusion::make_vector(1,2), is_odd()));
}

#endif

#endif
