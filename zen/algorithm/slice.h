/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    slice.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_SLICE_H
#define ZEN_GUARD_ALGORITHM_SLICE_H

#include <zen/algorithm/at.h>
#include <zen/range/iterator_range.h>

// TODO: Add stride
namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((slice)(auto r, n, m)
    if (is_range<r>)(zen::make_iterator_range(detail::iterator_at(r, n), detail::iterator_at(r, m)))
    def (auto r, n)
    if (is_range<r>)(make_iterator_range(detail::iterator_at(r, n), boost::end(r)))

)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>

ZEN_TEST_CASE(slice_test)
{
    std::vector<int> v1 = boost::assign::list_of(1)(2)(3)(4)(5);
    std::vector<int> v2 = boost::assign::list_of(1)(2);
    std::vector<int> v3 = boost::assign::list_of(3)(4)(5);
    
    
    ZEN_TEST_EQUAL(v1 | zen::slice(0, 2), v2);
    ZEN_TEST_EQUAL(zen::slice(v1, 0, 2), v2);

    ZEN_TEST_EQUAL(v1 | zen::slice(2), v3);
    ZEN_TEST_EQUAL(zen::slice(v1, 2), v3);
}

#endif

#endif
