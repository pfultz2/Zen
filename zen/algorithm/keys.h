/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    keys.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_KEYS_H
#define ZEN_GUARD_ALGORITHM_KEYS_H

#include <zen/algorithm/transform.h>

namespace zen { namespace detail {

ZEN_FUNCTION_CLASS((keys_selector)(auto x)(x.first))

}

ZEN_FUNCTION_PIPE_OBJECT((keys)(auto r)
    if (is_range_or_sequence<r>)(zen::transform(r, detail::keys_selector()))
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <map>

ZEN_TEST_CASE(keys_test)
{
    std::map<int, int> m = boost::assign::map_list_of(0, 1)(1, 2)(2, 3);
    std::vector<int> v = boost::assign::list_of(0)(1)(2);

    ZEN_TEST_EQUAL(v, m | zen::keys);
    ZEN_TEST_EQUAL(v, zen::keys(m));
}

#endif

#endif
