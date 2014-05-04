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

#include <zen/returns.h>
#include <zen/requires.h>
#include <zen/traits/builder.h>
#include <zen/function/is_callable.h>

namespace zen { 

namespace detail {
ZEN_TRAIT(has_failure)
{
    template<class T>
    auto requires(const T&) -> ZEN_VALID_EXPR(
        zen::has_template<T::template failure>()
    );
};

template<class Sig, class Enable = void>
struct failure_for_;

template<class F, class... Ts>
struct failure_for_<F(Ts...), ZEN_CLASS_REQUIRES(has_failure<F>())>
: F::template failure<Ts...>
{};

template<class F, class... Ts>
struct failure_for_<F(Ts...), ZEN_CLASS_REQUIRES(not has_failure<F>())>
{
    typedef decltype(std::declval<F>()(std::declval<Ts>()...)) type;
};
}

template<class... Ts>
struct failure_for
: detail::failure_for_<Ts>...
{};

template<class F>
struct reveal_adaptor: F
{
    reveal_adaptor()
    {}

    template<class X>
    reveal_adaptor(X x) : F(x)
    {}

    const F& base_function() const
    {
        return *this;
    }

    
    template<class... Ts>
    auto operator()(Ts && ... xs) const
    ZEN_RETURNS(this->base_function()(std::forward<Ts>(xs)...));

    struct fail {};

    template<class... Ts>
    ZEN_FUNCTION_REQUIRES(not is_callable<F(Ts&&...)>::value)
    (typename failure_for<F(Ts&&...)>::type) operator()(Ts && ... xs) const
    {
        static_assert(not is_callable<F(Ts&&...)>::value, "Not callable");
        typedef typename failure_for<F(Ts&&...)>::type type_error;
        return this->base_function()(std::forward<Ts>(xs)...);
    }

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
