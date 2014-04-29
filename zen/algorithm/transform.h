/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    transform.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_TRANSFORM_H
#define ZEN_GUARD_ALGORITHM_TRANSFORM_H

#include <zen/function/builder.h>
#include <zen/range/transform.h>

#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/support/is_sequence.hpp>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((transform)(auto&& r, auto f)
    if (_p<is_range>(r))
    (
        zen::make_transform_range(std::forward<decltype(r)>(r), f)
    )
    else if (_p<boost::fusion::traits::is_sequence>(r))
    (
        boost::fusion::transform(r, f)
    )
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <zen/algorithm/detail/triple.h>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/sequence/io.hpp>

ZEN_TEST_CASE(transform_test)
{
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {3, 6, 9};
    boost::fusion::vector<int,int, int> s1(1,2,3);
    boost::fusion::vector<int,int, int> s2(3,6,9);

    ZEN_TEST_EQUAL(v1 | zen::transform(triple()), v2);
    ZEN_TEST_EQUAL(s1 | zen::transform(triple()), s2);
}

#endif

#endif
