/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    min_element.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_MIN_ELEMENT_H
#define ZEN_GUARD_ALGORITHM_MIN_ELEMENT_H

#include <zen/algorithm/fold.h>

namespace zen { 

namespace detail {

ZEN_FUNCTION_CLASS((min_element_fold)(auto x, auto y)(x < y ? x : y))

}

ZEN_FUNCTION_PIPE_OBJECT((min_element)(auto r)
        if(is_range_or_sequence<r>)(fold(r, detail::min_element_fold()))
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <map>

ZEN_TEST_CASE(min_test)
{
    std::vector<int> v = boost::assign::list_of(0)(1)(2)(-1)(3);

    ZEN_TEST_EQUAL(zen::min_element(v), -1);
    ZEN_TEST_EQUAL(v | zen::min_element, -1);
}

#endif

#endif
