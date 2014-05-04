/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    at.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_AT_H
#define ZEN_GUARD_ALGORITHM_AT_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>
#include <zen/algorithm/empty.h>
#include <zen/iterator/next.h>
#include <zen/range/distance.h>

#include <algorithm>

#include <zen/assert.h>

namespace zen { 

namespace detail {

template<class Iterator>
Iterator iterator_at_back(Iterator it, Iterator start, Iterator stop)
{
    while(it != stop)
    {
        ++it;
        ++start;
    }
    return start;
}

template<class Range, class I>
bool index_in_range(const Range& r, I n)
{
    long size = zen::distance(r);
    if (n < 0) return n >= -size;
    else return n < size;
}

template<class R, class I>
auto iterator_at(R& r, I n)
{
    typedef typename zen::range_iterator<R>::type iterator;
    if (is_reversible_iterator<iterator>())
    {
        ZEN_ASSERT(index_in_range(r, n));
        return zen::next(((n >= 0) ? zen::begin(r) : zen::end(r)), n);
    }
    else
    {
        if (n >= 0) return zen::next(zen::begin(r), n);
        else return iterator_at_back(zen::next(zen::begin(r), -(long)n), zen::begin(r), zen::end(r));
    }
}

}

ZEN_FUNCTION_PIPE_OBJECT((at)(auto&& r, auto n)
        if (_p<is_range>(r))
        (
            *(detail::iterator_at(r, n))
        )

    )


}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <list>
#include <forward_list>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(at_test)
{
    std::vector<int> v1 = {9,1,2,3,4};
    
    ZEN_TEST_EQUAL(9, v1 | zen::at(0));
    ZEN_TEST_EQUAL(2, v1 | zen::at(2));
    ZEN_TEST_EQUAL(4, v1 | zen::at(-1));
    ZEN_TEST_EQUAL(3, v1 | zen::at(-2));

    std::list<int> l1 = {9,1,2,3,4};

    ZEN_TEST_EQUAL(9, l1 | zen::at(0));
    ZEN_TEST_EQUAL(2, l1 | zen::at(2));
    ZEN_TEST_EQUAL(4, l1 | zen::at(-1));
    ZEN_TEST_EQUAL(3, l1 | zen::at(-2));

    std::forward_list<int> s1 = {9,1,2,3,4};

    ZEN_TEST_EQUAL(9, s1 | zen::at(0));
    ZEN_TEST_EQUAL(2, s1 | zen::at(2));
    ZEN_TEST_EQUAL(4, s1 | zen::at(-1));
    ZEN_TEST_EQUAL(3, s1 | zen::at(-2));
}

#endif

#endif
