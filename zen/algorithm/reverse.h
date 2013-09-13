/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    reverse.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_REVERSE_H
#define ZEN_GUARD_ALGORITHM_REVERSE_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/iterator/reverse_iterator.hpp>
#include <zen/range/iterator_range.h>

#include <boost/fusion/algorithm/transformation/reverse.hpp>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((reverse)(auto r)
    if (has_range_traversal<r, boost::bidirectional_traversal_tag>)
    (
        zen::make_iterator_range
        (
            boost::make_reverse_iterator(boost::end(r)),
            boost::make_reverse_iterator(boost::begin(r)) 
        )
    )
    else if (is_sequence<r>)
    (
        boost::fusion::reverse(r)
    )

    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <zen/function/always.h>

ZEN_TEST_CASE(reverse_test)
{
    std::vector<int> v1 = boost::assign::list_of(0)(1)(2)(3)(4);
    std::vector<int> v2 = boost::assign::list_of(4)(3)(2)(1)(0);
    
    ZEN_TEST_EQUAL(v2, zen::reverse(v1));
    ZEN_TEST_EQUAL(v2, v1 | zen::reverse);

    boost::fusion::vector<int, int, int> vs1(1, 2, 3);
    boost::fusion::vector<int, int, int> vs2(3, 2, 1);

    ZEN_TEST_EQUAL(vs2, zen::reverse(vs1));
    ZEN_TEST_EQUAL(vs2, vs1 | zen::reverse);
}

#endif

#endif
