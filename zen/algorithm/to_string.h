/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    to_string.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_TO_STRING_H
#define ZEN_GUARD_ALGORITHM_TO_STRING_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <algorithm>
#include <boost/lexical_cast.hpp>

namespace zen {

ZEN_FUNCTION_PIPE_OBJECT((to_string)(auto r)
    if (is_range_of<r, char>)(std::string(boost::begin(r), boost::end(r)))
    else (boost::lexical_cast<std::string>(r))
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <list>

ZEN_TEST_CASE(to_string_test)
{
    std::vector<char> v = boost::assign::list_of('h')('e')('l')('l')('o');
    std::string s0 = "hello";
    std::string s1 = v | zen::to_string;
    std::string s2 = zen::to_string(v);

    ZEN_TEST_EQUAL(s1, s0);
    ZEN_TEST_EQUAL(s2, s0);

    int i = 5;
    std::string s3 = "5";
    std::string s4 = i | zen::to_string;
    std::string s5 = zen::to_string(i);

    ZEN_TEST_EQUAL(s4, s3);
    ZEN_TEST_EQUAL(s5, s3);
}

#endif

#endif
