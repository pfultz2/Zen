/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    to_lower.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_TO_LOWER_H
#define ZEN_GUARD_ALGORITHM_TO_LOWER_H

#include <zen/algorithm/transform.h>
#include <locale>

namespace zen { namespace detail {

ZEN_FUNCTION_CLASS((to_lower_selector)(auto x)(std::tolower(x, std::locale())))

}

ZEN_FUNCTION_PIPE_OBJECT((to_lower)(auto r)
    if (is_range<r>)(zen::transform(r, detail::to_lower_selector()))
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <list>

ZEN_TEST_CASE(to_lower_test)
{
    std::string s1 = "HELLO";
    std::string s2 = "hello";

    ZEN_TEST_EQUAL(s2, s1 | zen::to_lower);
    ZEN_TEST_EQUAL(s2, zen::to_lower(s1));
}

#endif

#endif
