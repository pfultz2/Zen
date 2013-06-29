/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    fold.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FOLD_H
#define ZEN_GUARD_ALGORITHM_FOLD_H


#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <zen/assert.h>

#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <numeric>

namespace zen {

namespace detail {

template<class R, class F, class Enable = void>
struct is_fold_callable
: boost::false_type
{};

template<class R, class F>
struct is_fold_callable<R, F, ZEN_CLASS_REQUIRES(is_range<R>)>
: is_callable<F(typename boost::range_reference<R>::type, typename boost::range_reference<R>::type)>
{};

}

// TODO: fold over sequence without default value
ZEN_FUNCTION_PIPE_OBJECT((fold)(auto r, f, const init)
        if(is_range<r>)(ZEN_ASSERT_EXPR(!boost::empty(r), std::accumulate(boost::begin(r), boost::end(r), init, f)))
        else if(is_sequence<r>)(boost::fusion::fold(r, init, f))
        def(auto r, f)
        if (is_range<r>, detail::is_fold_callable<r, f>)
        (
            ZEN_ASSERT_EXPR(!boost::empty(r),
            std::accumulate(++boost::begin(r), boost::end(r), *boost::begin(r), f))
        )
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>

ZEN_FUNCTION_CLASS((fold_test_summer)(auto x, auto y)(x + y))

ZEN_TEST_CASE(fold_test)
{
    std::vector<int> v = boost::assign::list_of(1)(2)(3)(4);
    ZEN_TEST_EQUAL(10, zen::fold(v, fold_test_summer()));
    ZEN_TEST_EQUAL(10, v | zen::fold(fold_test_summer()));
    
    ZEN_TEST_EQUAL(15, zen::fold(v, fold_test_summer(), 5));
    ZEN_TEST_EQUAL(15, v | zen::fold(fold_test_summer(), 5));
}

#endif

#endif
