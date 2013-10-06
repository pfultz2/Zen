/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    values.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_VALUES_H
#define ZEN_GUARD_ALGORITHM_VALUES_H

#include <zen/algorithm/transform.h>

namespace zen { namespace detail {

ZEN_FUNCTION_CLASS((values_selector)(auto x)(x.second))

}

ZEN_FUNCTION_PIPE_OBJECT((values)(auto r)
    if (is_range_or_sequence<r>)(zen::transform(r, detail::values_selector()))
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <map>

ZEN_TEST_CASE(values_test)
{
    std::map<int, int> m = boost::assign::map_list_of(0, 1)(1, 2)(2, 3);
    std::vector<int> v = boost::assign::list_of(1)(2)(3);

    ZEN_TEST_EQUAL(v, m | zen::values);
    ZEN_TEST_EQUAL(v, zen::values(m));
}

#endif

#endif
