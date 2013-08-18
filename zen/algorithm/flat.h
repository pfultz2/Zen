/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    flat.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FLAT_H
#define ZEN_GUARD_ALGORITHM_FLAT_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <zen/iterator/flat_iterator.h>
#include <zen/range/iterator_range.h>
#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((flat)(auto r)
    if (is_range<r>)
    (
        zen::make_iterator_range
        (
            make_flat_iterator(boost::begin(r), boost::end(r)),
            make_flat_iterator(boost::end(r), boost::end(r))
        )
    )

)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>


ZEN_TEST_CASE(flat_test)
{
    std::vector<int> inner_v = boost::assign::list_of(1)(2);
    std::vector<std::vector<int> > v1;
    v1.push_back(inner_v);
    v1.push_back(inner_v);
    v1.push_back(inner_v);
    std::vector<int> v2 = boost::assign::list_of(1)(2)(1)(2)(1)(2);

    ZEN_TEST_EQUAL(v1 | zen::flat, v2);
    ZEN_TEST_EQUAL(zen::flat(v1), v2);
}

#endif

#endif
