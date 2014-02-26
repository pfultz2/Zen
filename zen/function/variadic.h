/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    variadic.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_VARIADIC_H
#define ZEN_GUARD_FUNCTION_VARIADIC_H

// @begin
// variadic
// ========
// 
// Description
// -----------
// 
// The `variadic` function adaptor converts the arguments to the function to a
// tuple or fusion sequence.
// 
// Synopsis
// --------
// 
//     template<class F>
//     variadic_adaptor<F> variadic(F f);
// 
// @end

#include <zen/function/detail/remove_rvalue_reference.h>

namespace zen {

template<class F>
struct variadic_adaptor : F
{
    template<class... Ts>
    variadic_adaptor(Ts && ... x) : F(std::forward<Ts>(x)...)
    {}

    const F& base_function() const
    {
        return *this;
    }

    template<class... Ts>
    auto operator()(Ts && ... xs) const
    ZEN_RETURNS(this->base_function()(detail::make_ref_tuple(std::forward<Ts>(xs)...)));
};

template<class F>
variadic_adaptor<F> variadic(F f)
{
    return variadic_adaptor<F>(f);
}

}


#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/detail/test.h>

typedef zen::variadic_adaptor<tuple_class> vard_class;

ZEN_TEST_CASE(variadic_test)
{
    ZEN_TEST_EQUAL(3, vard_class()(2));
}
#endif

#endif
