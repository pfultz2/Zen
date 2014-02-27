/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    lazy.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_LAZY_H
#define ZEN_GUARD_FUNCTION_LAZY_H

// @begin
// lazy
// ====
// 
// Description
// -----------
// 
// The `lazy` function adaptor returns a lazy phoenix function so it can accept
// phoenix actors as parameters.
// 
// Synopsis
// --------
// 
//     template<class F>
//     lazy_adaptor<F> lazy(F f);
// 
// Example
// -------
// 
//     struct sum
//     {
//         template<class T>
//         T sum(T x, T y)
//         {
//             return x+y;
//         }
//     };
// 
//     using zen::ph::_1;
//     using zen::ph::_2;
//     assert(3 == lazy(sum())(1, 2)());
//     assert(3 == lazy(sum())(_1, _2)(1, 2));
//     assert(3 == lazy(sum())(_1, 2)(1));
// 
// @end


#include <functional>

namespace zen { 

template<class F>
struct lazy_adaptor : F
{
    lazy_adaptor() {}

    template<class X>
    lazy_adaptor(X x) : F(x)
    {}

    const F& base_function() const
    {
        return *this;
    }

    template<class... Ts>
    auto operator()(Ts&&... xs) const 
    ZEN_RETURNS(std::bind(this->base_function(), std::forward<Ts>(xs)...));
};


template<class F>
lazy_adaptor<F> lazy(F f)
{
    return lazy_adaptor<F>(f);
}

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/static.h>
#include <zen/function/placeholders.h>

zen::static_<zen::lazy_adaptor<binary_class> > binary_lazy = {};

ZEN_TEST_CASE(lazy_test)
{
    using zen::ph::_1;
    using zen::ph::_2;
    ZEN_TEST_EQUAL(3, binary_lazy(1, 2)());
    ZEN_TEST_EQUAL(3, binary_lazy(_1, _2)(1, 2));
    ZEN_TEST_EQUAL(3, binary_lazy(_1, 2)(1));
}
#endif

#endif
