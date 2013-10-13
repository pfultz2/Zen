/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    inner_product.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_INNER_PRODUCT_H
#define ZEN_GUARD_ALGORITHM_INNER_PRODUCT_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <numeric>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((inner_product)(auto r1, auto r2, x)
    if (is_range<r1>, is_range<r2>)
    (
        std::inner_product(boost::begin(r1), boost::end(r1), boost::begin(r2), x)
    )
    def(auto r1, auto r2, x, op1, op2)
    if (is_range<r1>, is_range<r2>)
    (
        std::inner_product(boost::begin(r1), boost::end(r1), boost::begin(r2), x, op1, op2)
    )

)
}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <utility>

ZEN_TEST_CASE(inner_product_test)
{
    std::vector<int> a = boost::assign::list_of(0)(1)(2)(3)(4);
    std::vector<int> b = boost::assign::list_of(5)(4)(2)(3)(1);

    ZEN_TEST_EQUAL(zen::inner_product(a, b, 0), 21);
    ZEN_TEST_EQUAL(zen::inner_product(a, b, 0, std::plus<int>(), std::equal_to<int>()), 2);

    ZEN_TEST_EQUAL(a | zen::inner_product(b, 0), 21);
    ZEN_TEST_EQUAL(a | zen::inner_product(b, 0, std::plus<int>(), std::equal_to<int>()), 2);
}

#endif

#endif
