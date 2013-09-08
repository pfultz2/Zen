/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    replace.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_REPLACE_H
#define ZEN_GUARD_ALGORITHM_REPLACE_H

#include <zen/algorithm/transform.h>
#include <zen/function/partial.h>

namespace zen { 

namespace detail {

ZEN_FUNCTION_CLASS((replacer)(auto old_value, auto new_value, auto x)
    (
        x == old_value ? new_value : x
    ))

}

ZEN_FUNCTION_PIPE_OBJECT((replace)(auto r, auto old_value, auto new_value)
    if (is_range_or_sequence<r>)
    (
        zen::transform(r, partial(detail::replacer())(old_value, new_value))
    )
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(replace_test)
{
    std::vector<int> v1 = boost::assign::list_of(0)(1)(2)(3)(4);
    std::vector<int> v2 = boost::assign::list_of(0)(1)(99)(3)(4);
    
    ZEN_TEST_EQUAL(v2, zen::replace(v1, 2, 99));
    ZEN_TEST_EQUAL(v2, v1 | zen::replace(2, 99));
}

#endif

#endif
