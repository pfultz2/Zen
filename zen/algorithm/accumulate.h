/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    accumulate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_ACCUMULATE_H
#define ZEN_GUARD_ALGORITHM_ACCUMULATE_H

#include <zen/algorithm/fold.h>


namespace zen { 

namespace detail {

ZEN_FUNCTION_CLASS((accumulate_fold)(auto x, auto y)(x + y))

}

ZEN_FUNCTION_PIPE_OBJECT((accumulate)(auto r, const init)
        if(is_range_or_sequence<r>)(fold(r, detail::accumulate_fold(), init))
        def(auto r)
        if(is_range_or_sequence<r>)(fold(r, detail::accumulate_fold()))
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>

ZEN_TEST_CASE(accumulate_test)
{
    std::vector<int> v = boost::assign::list_of(1)(2)(3)(4);
    ZEN_TEST_EQUAL(10, zen::accumulate(v));
    ZEN_TEST_EQUAL(10, v | zen::accumulate);
    
    ZEN_TEST_EQUAL(15, zen::accumulate(v, 5));
    ZEN_TEST_EQUAL(15, v | zen::accumulate(5));
}

#endif

#endif
