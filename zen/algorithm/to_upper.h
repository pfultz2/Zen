/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    to_upper.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_TO_UPPER_H
#define ZEN_GUARD_ALGORITHM_TO_UPPER_H

#include <zen/algorithm/transform.h>
#include <locale>

namespace zen { namespace detail {

ZEN_FUNCTION_CLASS((to_upper_selector)(auto x)(std::toupper(x, std::locale())))

}

ZEN_FUNCTION_PIPE_OBJECT((to_upper)(auto r)
    if (is_range<r>)(zen::transform(r, detail::to_upper_selector()))
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <list>

ZEN_TEST_CASE(to_upper_test)
{
    std::string s1 = "hello";
    std::string s2 = "HELLO";

    ZEN_TEST_EQUAL(s2, s1 | zen::to_upper);
    ZEN_TEST_EQUAL(s2, zen::to_upper(s1));
}

#endif

#endif
