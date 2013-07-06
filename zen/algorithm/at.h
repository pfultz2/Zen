/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    at.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_AT_H
#define ZEN_GUARD_ALGORITHM_AT_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <zen/algorithm/empty.h>
#include <zen/iterator/next.h>

#include <algorithm>

#include <zen/assert.h>

namespace zen { 

namespace detail {

template<class R, class I>
typename boost::range_iterator<R>::type
iterator_at(R& r, I n)
{
    // TODO: Assert index is in range
//    typename boost::range_iterator<const R>::type it;
//    if (n < 0) it = boost::end(r);
//    else it = boost::begin(r);
    return zen::next(((n > 0) ? boost::begin(r) : boost::end(r)), n);
}

}

ZEN_FUNCTION_PIPE_OBJECT((at)(auto r, n)
        if (is_range<r>)
        (
            *(detail::iterator_at(r, n))
        )

    )


}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(at_test)
{
    std::vector<int> v1 = boost::assign::list_of(0)(1)(2)(3)(4);
    
    ZEN_TEST_EQUAL(2, v1 | zen::at(2));
    ZEN_TEST_EQUAL(4, v1 | zen::at(-1));
    ZEN_TEST_EQUAL(3, v1 | zen::at(-2));
}

#endif

#endif
