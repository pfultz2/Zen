/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    find_end.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FIND_END_H
#define ZEN_GUARD_ALGORITHM_FIND_END_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>
#include <zen/algorithm/find.h>
#include <zen/algorithm/reverse.h>

#include <algorithm>

namespace zen {

namespace detail {

template<class Range>
auto unreverse_range(Range&& r)
{
    return zen::make_iterator_range(r.begin().base(), r.end().base());
}

}

ZEN_FUNCTION_PIPE_OBJECT((find_end)(auto&& r, const auto& x)
        if (_p<is_sub_range>(r, x) or _p<is_range>(x))
        (
            detail::unreverse_range(find(reverse(r), x))
        )
        def(auto&& r, const auto& x, auto pred)
        if (_p<is_sub_range>(r, x) or _p<is_range>(x))
        (
            detail::unreverse_range(find(reverse(r), x, pred))
        )
    )


}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <map>


ZEN_TEST_CASE(find_end_test)
{
    std::vector<int> v = {0,1,2,3,4};
    std::vector<int> sv = {1,2,3};
    
    ZEN_TEST_EQUAL(2, *(v | zen::find(2)).begin());
    
    ZEN_TEST_CHECK(zen::end(v) == (v | zen::find(5)).begin());

    ZEN_TEST_EQUAL(sv, zen::find(v, sv));
    
}

#endif

#endif
