/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    fused_for_each.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FUSED_FOR_EACH_H
#define ZEN_GUARD_ALGORITHM_FUSED_FOR_EACH_H

#include <zen/algorithm/for_each.h>
#include <zen/function/fuse.h>

namespace zen {

ZEN_FUNCTION_PIPE_OBJECT((fused_for_each)(auto&& r, auto f)
    (zen::for_each(ZEN_AUTO_FORWARD(r), zen::fuse(f)))
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <map>
#include <zen/algorithm/detail/increment.h>
#include <boost/fusion/adapted/std_pair.hpp>

ZEN_FUNCTION_CLASS((fused_increment)(const auto& x, auto& y)(++y))

ZEN_TEST_CASE(fused_for_each_test)
{
    std::map<int, int > m1 = { {0, 1}, {1, 2} };
    std::map<int, int > m2 = { {0, 2}, {1, 3} };

    m1 | zen::fused_for_each(fused_increment());
    ZEN_TEST_EQUAL(m1, m2);
}

#endif

#endif
