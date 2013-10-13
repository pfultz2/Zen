/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    max_element.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_MAX_ELEMENT_H
#define ZEN_GUARD_ALGORITHM_MAX_ELEMENT_H

#include <zen/algorithm/fold.h>


namespace zen { 

namespace detail {

ZEN_FUNCTION_CLASS((max_element_fold)(auto x, auto y)(x > y ? x : y))

}

ZEN_FUNCTION_PIPE_OBJECT((max_element)(auto r)
        if(is_range_or_sequence<r>)(fold(r, detail::max_element_fold()))
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <map>

ZEN_TEST_CASE(max_test)
{
    std::vector<int> v = boost::assign::list_of(0)(1)(2)(5)(3);

    ZEN_TEST_EQUAL(zen::max_element(v), 5);
    ZEN_TEST_EQUAL(v | zen::max_element, 5);
}

#endif

#endif
