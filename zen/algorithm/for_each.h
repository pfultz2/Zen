/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    for_each.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FOR_EACH_H
#define ZEN_GUARD_ALGORITHM_FOR_EACH_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((for_each)(auto r, f)
        if(is_range<r>)(std::for_each(boost::begin(r), boost::end(r), f))
        else if(is_sequence<r>)(boost::fusion::for_each(r, f))
    )


}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <zen/algorithm/equal.h>
#include <zen/algorithm/detail/increment.h>


ZEN_TEST_CASE(for_each_test)
{
    std::vector<int> v1 = boost::assign::list_of(1)(2);
    std::vector<int> v2 = boost::assign::list_of(2)(3);
    boost::fusion::vector<int,int> s1(1,2);
    boost::fusion::vector<int,int> s2(2,3);

    v1 | zen::for_each(increment());
    s1 | zen::for_each(increment());
    ZEN_TEST_EQUAL(v1, v2);
    ZEN_TEST_EQUAL(s1, s2);
}

#endif

#endif
