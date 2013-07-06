/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    count.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_COUNT_H
#define ZEN_GUARD_ALGORITHM_COUNT_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/fusion/algorithm/query/count.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <algorithm>

namespace zen {

namespace detail {


struct count
{
    typedef std::ptrdiff_t result_type;
    template<class R>
    ZEN_FUNCTION_REQUIRES(is_range<R>)
    (std::ptrdiff_t) operator()(const R& r) const
    {
        // TODO: Create a distance that recognizes iterator_traversals
        return std::distance(boost::begin(r), boost::end(r));
    }

    template<class R, class T>
    ZEN_FUNCTION_REQUIRES(is_range<R>)
    (std::ptrdiff_t) operator()(const R& r, const T& x) const
    {
        return std::count(boost::begin(r), boost::end(r), x);
    }

    template<class R>
    ZEN_FUNCTION_REQUIRES(is_sequence<R>, exclude is_range<R>)
    (std::ptrdiff_t) operator()(const R& r) const
    {
        return boost::fusion::size(r);
    }

    template<class R, class T>
    ZEN_FUNCTION_REQUIRES(is_sequence<R>, exclude is_range<R>)
    (std::ptrdiff_t) operator()(const R& r, const T& x) const
    {
        return boost::fusion::count(r, x);
    }

};
}

static_<pipable_adaptor<detail::count> > count = {};

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <zen/algorithm/detail/is_odd.h>


ZEN_TEST_CASE(count_test)
{
    std::vector<int> v = boost::assign::list_of(1)(2)(3);
    
    ZEN_TEST_EQUAL(1, zen::count(v, 2));
    ZEN_TEST_EQUAL(3, zen::count(v));
    
    ZEN_TEST_EQUAL(1, zen::count(boost::fusion::make_vector(1,2,3), 2));
    ZEN_TEST_EQUAL(3, zen::count(boost::fusion::make_vector(1,2,3)));
}

#endif

#endif
