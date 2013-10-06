/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    to_container.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_TO_CONTAINER_H
#define ZEN_GUARD_ALGORITHM_TO_CONTAINER_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <zen/function/implicit.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace zen { namespace detail {

template<class T>
struct to_container_f
{
    template<class X>
    struct result;

    template<class X, class Range>
    struct result<X(Range)>
    {
        typedef T type;
    };

    template<class Range>
    T operator()(const Range& r) const
    {
        return T(boost::begin(r), boost::end(r));
    }
};
}

ZEN_FUNCTION_PIPE_OBJECT((to_container)(auto r)
        if (is_range<r>)(implicit<detail::to_container_f>()(r))
    )
}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <list>

ZEN_TEST_CASE(to_container_test)
{
    std::vector<int> v1 = boost::assign::list_of(1)(2)(3);
    std::list<int> l1 = zen::to_container(v1);
    std::list<int> l2 = v1 | zen::to_container;
    
    ZEN_TEST_EQUAL(v1, l1);
    ZEN_TEST_EQUAL(v1, l2);
}

#endif

#endif
