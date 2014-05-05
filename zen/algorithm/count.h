/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    count.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_COUNT_H
#define ZEN_GUARD_ALGORITHM_COUNT_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>

#include <boost/fusion/algorithm/query/count.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <algorithm>

namespace zen {


ZEN_FUNCTION_PIPE_OBJECT((count)(const auto& r, const auto& x)
        if (_p<is_range_of>(r, x))(std::count(zen::begin(r), zen::end(r), x))
        else if (_p<boost::fusion::traits::is_sequence>(r))(boost::fusion::count(r, x))
        def(const auto& r)
        if (_p<is_range>(r))(zen::distance(r))
        else if (_p<boost::fusion::traits::is_sequence>(r))(boost::fusion::size(r))

    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <zen/algorithm/detail/is_odd.h>


ZEN_TEST_CASE(count_test)
{
    std::vector<int> v = { 1, 2, 3 };
    
    ZEN_TEST_EQUAL(1, zen::count(v, 2));
    ZEN_TEST_EQUAL(3, zen::count(v));
    ZEN_TEST_EQUAL(3, v | zen::count);
    
    ZEN_TEST_EQUAL(1, zen::count(boost::fusion::make_vector(1,2,3), 2));
    ZEN_TEST_EQUAL(3, zen::count(boost::fusion::make_vector(1,2,3)));
    ZEN_TEST_EQUAL(3, boost::fusion::make_vector(1,2,3) | zen::count);
}

#endif

#endif
