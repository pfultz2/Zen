/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    flat.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FLAT_H
#define ZEN_GUARD_ALGORITHM_FLAT_H

#include <zen/function/builder.h>
#include <zen/range/flat_range.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((flat)(auto&& r)
    // TODO: Check it is a range of range
    if (_p<is_range>(r))(zen::make_flat_range(ZEN_AUTO_FORWARD(r)))

)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/reverse.h>
#include <vector>
#include <forward_list>

ZEN_TEST_CASE(flat_test)
{
    std::vector<int> inner_v = { 1, 2 };
    std::vector<std::vector<int> > v1;
    v1.push_back(inner_v);
    v1.push_back(inner_v);
    v1.push_back(inner_v);
    std::vector<int> v2 = { 1, 2, 1, 2, 1, 2 };

    ZEN_TEST_EQUAL(zen::flat(v1), v2);
    ZEN_TEST_EQUAL(v1 | zen::flat, v2);
    ZEN_TEST_EQUAL(v1 | zen::flat | zen::reverse, v2 | zen::reverse);
    
    std::forward_list<int> inner_l = { 1, 2 };
    std::vector<std::forward_list<int> > l1;
    l1.push_back(inner_l);
    l1.push_back(inner_l);
    l1.push_back(inner_l);
    ZEN_TEST_EQUAL(zen::flat(l1), v2);
    // ZEN_TEST_EQUAL(l1 | zen::flat | zen::reverse, v2 | zen::reverse);

}

#endif

#endif
