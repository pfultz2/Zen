/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    static.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_STATIC_H
#define ZEN_GUARD_FUNCTION_STATIC_H

// @begin
// static
// ======
// 
// Description
// -----------
// 
// The `static_` adaptor is a static function adaptor that allows any default-
// constructible function object to be static-initialized.
// 
// Synopsis
// --------
// 
//     template<class F>
//     class static_;
// 
// Example
// -------
// 
//     // In C++03 this class can't be static-initialized, because of the 
//     // default constructor.
//     struct times_function
//     {
//         double factor;
//         times2_function() : factor(2)
//         {}
//         template<class T>
//         T operator()(T x) const
//         {
//             return x*factor;
//         }
//     };
// 
//     static_<times_function> times2 = {};
// 
//     assert(6 == times2(3));
// 
// @end

#include <zen/returns.h>
#include <zen/function/reveal.h>

namespace zen { 

template<class F>
struct static_
{
    const F& base_function() const
    {
        static F f;
        return f;
    }

    template<class... Ts>
    struct failure
    : failure_for<F(Ts...)>
    {};

    template<class... Ts>
    auto operator()(Ts && ... xs) const
    ZEN_RETURNS(this->base_function()(std::forward<Ts>(xs)...));
};
}
#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/detail/test.h>

zen::static_<binary_class> binary_static = {};

zen::static_<void_class> void_static = {};

zen::static_<mono_class> mono_static = {};

ZEN_TEST_CASE(static_test)
{
    void_static(1);
    ZEN_TEST_EQUAL(3, binary_static(1, 2));
    ZEN_TEST_EQUAL(3, mono_static(2));
}
#endif

#endif
