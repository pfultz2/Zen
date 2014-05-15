/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    fold.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FOLD_H
#define ZEN_GUARD_ALGORITHM_FOLD_H


#include <zen/function/builder.h>
#include <zen/range/range_traits.h>
#include <zen/algorithm/empty.h>
#include <zen/assert.h>

#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <numeric>

namespace zen {

namespace detail {

ZEN_TRAIT(is_fold_callable, is_range<_2>)
{
    template<class F, class R>
    auto requires(F&& f, R&& r) -> ZEN_VALID_EXPR(
        zen::returns< _t<range_value<R>> >(f(*zen::begin(r), *zen::begin(r)))
    );
};

}

ZEN_FUNCTION_PIPE_OBJECT((fold)(auto&& r, auto f, const auto init)
        if(_p<is_range>(r) and _p<detail::is_fold_callable>(f, r))
        (std::accumulate(zen::begin(r), zen::end(r), init, f))
        else if(_p<boost::fusion::traits::is_sequence>(r))
        (boost::fusion::fold(r, init, f))
        def(auto&& r, auto f)
        if (_p<is_range>(r) and _p<detail::is_fold_callable>(f, r))
        (
            ZEN_ASSERT_EXPR(!zen::empty(r),
            std::accumulate(++zen::begin(r), zen::end(r), *zen::begin(r), f))
        )
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/reveal.h>
#include <vector>

ZEN_FUNCTION_CLASS((fold_test_summer)(const auto x, const auto y)(x + y))

ZEN_TEST_CASE(fold_test)
{
    std::vector<int> v = {1, 2, 3, 4};
    ZEN_TEST_EQUAL(10, zen::fold(v, fold_test_summer()));
    ZEN_TEST_EQUAL(10, v | zen::fold(fold_test_summer()));
    
    ZEN_TEST_EQUAL(15, zen::fold(v, fold_test_summer(), 5));
    ZEN_TEST_EQUAL(15, v | zen::fold(fold_test_summer(), 5));
}

#endif

#endif
