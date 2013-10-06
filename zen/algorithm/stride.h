/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    stride.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_STRIDE_H
#define ZEN_GUARD_ALGORITHM_STRIDE_H

#include <zen/function/builder.h>
#include <zen/iterator/stride_iterator.h>
#include <zen/range/iterator_range.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((stride)(auto r, n)
        if (is_range<r>)(zen::make_iterator_range
            (
                zen::make_begin_stride_iterator(boost::begin(r), boost::end(r), n), 
                zen::make_end_stride_iterator(boost::begin(r), boost::end(r), n)
            ))
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <list>

ZEN_TEST_CASE(stride_test)
{
    std::vector<int> v1 = boost::assign::list_of(0)(1)(2)(3)(4)(5)(6);
    std::vector<int> v2 = boost::assign::list_of(0)(2)(4)(6);

    std::list<int> l1 = boost::assign::list_of(0)(1)(2)(3)(4)(5)(6);

    ZEN_TEST_EQUAL(zen::stride(v1, 2), v2);
    ZEN_TEST_EQUAL(v1 | zen::stride(2), v2);

    ZEN_TEST_EQUAL(zen::stride(l1, 2), v2);
    ZEN_TEST_EQUAL(l1 | zen::stride(2), v2);
}

#endif

#endif
