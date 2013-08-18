/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    delimit.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_DELIMIT_H
#define ZEN_GUARD_ALGORITHM_DELIMIT_H

#include <zen/algorithm/join.h>
#include <zen/algorithm/flat.h>
#include <zen/algorithm/transform.h>
#include <zen/algorithm/drop.h>
#include <zen/algorithm/count.h>
#include <zen/function/partial.h>

namespace zen { 
// TODO: Add support for delimiting single elements
ZEN_FUNCTION_PIPE_OBJECT((delimit)(auto x, auto d)
    if (is_range<x>, is_range<d>)
    (
        x | zen::transform(zen::partial(join)(boost::ref(d))) | zen::flat | zen::drop(zen::count(d))
    )
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>

ZEN_TEST_CASE(delimit_test)
{
    std::vector<int> inner_v = boost::assign::list_of(1)(2);
    std::vector<int> delimiter = boost::assign::list_of(0)(0);
    std::vector<std::vector<int> > v1;
    v1.push_back(inner_v);
    v1.push_back(inner_v);
    v1.push_back(inner_v);
    std::vector<int> v2 = boost::assign::list_of(1)(2)(0)(0)(1)(2)(0)(0)(1)(2);

    ZEN_TEST_EQUAL(v1 | zen::delimit(delimiter), v2);
    ZEN_TEST_EQUAL(zen::delimit(v1, delimiter), v2);
}

#endif

#endif
