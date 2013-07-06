/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    contains.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_CONTAINS_H
#define ZEN_GUARD_ALGORITHM_CONTAINS_H

#include <zen/algorithm/find.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((contains)(auto r, const x)
        if (is_range<r>)(zen::find(r, x) != boost::end(r))
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <map>


ZEN_TEST_CASE(contains_test)
{
    std::vector<int> v = boost::assign::list_of(0)(1)(2)(3)(4);
    std::map<int, int> m = boost::assign::map_list_of(0, 1)(1, 2)(2, 3)(3, 4)(4, 5)(5, 6);
    std::string s = "Hello World!";
    
    ZEN_TEST_CHECK(v | zen::contains(2));
    ZEN_TEST_CHECK(m | zen::contains(2));
    ZEN_TEST_CHECK(s | zen::contains("World"));
    
    ZEN_TEST_CHECK(not (v | zen::contains(7)));
    ZEN_TEST_CHECK(not (m | zen::contains(7)));
    ZEN_TEST_CHECK(not (s | zen::contains("foo")));
}

#endif

#endif