/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    reveal.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_REVEAL_H
#define ZEN_GUARD_FUNCTION_REVEAL_H

// @begin
// reveal
// ======
// 
// Description
// -----------
// 
// The `reveal` function adaptor turns substitution failures into compile errors.
// Sometimes an error in a function that causes a substitution failure, will
// remove the function from valid overloads thus masking the error inside the
// function. The `reveal` adaptor reveals these errors by forcing a compile
// error, instead of a substitution failure.
// 
// Synopsis
// --------
// 
//     template<class F>
//     reveal_adaptor<F> reveal(F f);
// 
// @end

#include <zen/function/conditional.h>

namespace zen { 

namespace detail {

template<class Derived, class F>
struct reveal_adaptor_base
{

    reveal_adaptor_base()
    {}

    const F& get_function() const
    {
        return static_cast<const Derived&>(*this);
    }

    struct fail
    {};

    template<class... T>
    fail operator()(T &&... x) const
    {
        this->get_function()(std::forward<T>(x)...);
        return fail();
    }
};

}

template<class F>
struct reveal_adaptor
: zen::conditional_adaptor<F, detail::reveal_adaptor_base<reveal_adaptor<F>, F> >
{
    typedef zen::conditional_adaptor<F, detail::reveal_adaptor_base<reveal_adaptor<F>, F> > base;
    reveal_adaptor()
    {}

    template<class X>
    reveal_adaptor(X x) : base(x, {})
    {}
};

template<class F>
reveal_adaptor<F> reveal(F f)
{
    return reveal_adaptor<F>(f);
}

}

#if 0
#include <zen/test.h>

ZEN_TEST_CASE(reveal_test)
{
}

#endif

#endif
