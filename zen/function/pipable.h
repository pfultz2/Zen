/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    pipable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_PIPABLE_H
#define ZEN_GUARD_FUNCTION_PIPABLE_H

// @begin
// pipable
// =======
// 
// Description
// -----------
// 
// The `pipable` function adaptor provides an extension method. The first
// parameter of the function can be piped into the function using the `|`
// operator. This can be especially convient when there are a lot of nested
// function calls. Functions that are made pipable can still be called the
// traditional way without piping in the first parameter.
// 
// Synopsis
// --------
// 
//     template<class F>
//     pipable_adaptor<F> pipable(F f);
// 
// Example
// -------
// 
//     struct sum
//     {
//         template<class T>
//         T sum(T x, T y) const
//         {
//             return x+y;
//         }
//     };
// 
//     assert(3 == 1 | pipable(sum())(2));
//     assert(3 == pipable(sum())(1, 2));
// 
// @end

#include <zen/function/conditional.h>
#include <zen/function/static.h>
#include <zen/function/variadic.h>
#include <zen/function/invoke.h>

namespace zen { 
 
template<class F>
struct pipable_adaptor;

// A possible implementation using generic lambdas
#if 0 // ZEN_NO_GENERIC_LAMBDA

template<class F>
struct pipe_closure : F
{
    template<class X>
    pipe_closure(X&& f) : F(std::forward<X>(f))
    {}

    const F& base_function() const
    {
        return *this;
    }
};

template<class A, class F>
decltype(auto) operator|(A&& a, const pipe_closure<F>& p)
{
    return p(std::forward<A>(a));
}

template<class F>
pipe_closure<F> make_pipe_closure(F&& x)
{
    return pipe_closure<F>(std::forward<F>(x));
}

template<class Derived, class F>
struct pipe_closure_factory
{
    const F& get_function() const
    {
        return static_cast<const F&>(static_cast<const Derived&>(*this));
    }

    template<class... Ts>
    auto operator()(Ts&&... xs) const
    {
        return make_pipe_closure([ys = std::forward<Ts>(xs)...](auto&& x)
        {
            return this->get_function()(x, std::forward<Ts>(ys)...);
        });
    }
};


template<class F>
using pipable_adaptor_base = pipe_closure_factory<F, pipe_closure_factory<pipable_adaptor<F>, F> >;
#else
namespace detail {

template<class F, class Sequence>
struct pipe_closure : F, Sequence
{
    
    template<class X, class S>
    pipe_closure(X&& f, S&& seq) : F(std::forward<X>(f)), Sequence(std::forward<S>(seq))
    {}

    const F& base_function() const
    {
        return *this;
    }

    const Sequence& get_sequence() const
    {
        return *this;
    }

    template<class A>
    decltype(auto) operator()(A&& a) const
    {
        return zen::invoke(this->base_function(), std::tuple_cat
        (
            std::forward_as_tuple(std::forward<A>(a)),
            this->get_sequence()
        ));
    }
};


template<class Derived, class F>
struct pipe_closure_factory
{
    const F& get_function() const
    {
        return static_cast<const F&>(static_cast<const Derived&>(*this));
    }

    template<class T>
    pipe_closure<F, T> 
    operator()(T&& t) const
    {
        return pipe_closure<F, bare_t<T>>(this->get_function(), std::forward<T>(t)) ;
    }
};
    
template<class F>
using pipable_adaptor_base = conditional_adaptor<F, variadic_adaptor<detail::pipe_closure_factory<pipable_adaptor<F>, F> > >;
template<class A, class F, class Sequence>
decltype(auto) operator|(A&& a, const pipe_closure<F, Sequence>& p)
{
    return p(std::forward<A>(a));
}
#endif
}

template<class F>
struct pipable_adaptor 
: detail::pipable_adaptor_base<F>
{
    typedef detail::pipable_adaptor_base<F> base;

    pipable_adaptor()
    {}

    template<class X>
    pipable_adaptor(X&& x) : base(std::forward<X>(x), {})
    {}

    const F& base_function() const
    {
        return *this;
    }

    // MSVC Workaround
    // pipable_adaptor(const pipable_adaptor& rhs) : base(static_cast<const base&>(rhs))
    // {}
};


template<class F>
pipable_adaptor<F> pipable(F f)
{
    return pipable_adaptor<F>(f);
}

// Operators for static_ adaptor
template<class A, class F>
decltype(auto) operator|(A&& a, static_<F> f)
{
    return f.base_function().base_function()(std::forward<A>(a));
}
}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/detail/test.h>
#include <zen/function/static.h>

zen::static_<zen::pipable_adaptor<binary_class> > binary_pipable = {};

zen::static_<zen::pipable_adaptor<unary_class> > unary_pipable = {};

zen::static_<zen::pipable_adaptor<mutable_class> > mutable_pipable = {};

zen::static_<zen::pipable_adaptor<void_class> > void_pipable = {};

zen::static_<zen::pipable_adaptor<mono_class> > mono_pipable = {};

ZEN_TEST_CASE(pipable_test)
{
    void_pipable(1);
    1 | void_pipable;
    ZEN_TEST_EQUAL(3, 1 | binary_pipable(2));
    ZEN_TEST_EQUAL(3, binary_pipable(1, 2));
    ZEN_TEST_EQUAL(3, 3 | unary_pipable);
    ZEN_TEST_EQUAL(3, 3 | unary_pipable());
    ZEN_TEST_EQUAL(3, unary_pipable(3));
    int i1 = 1;
    ZEN_TEST_EQUAL(3, 2 | binary_pipable(i1));
    ZEN_TEST_EQUAL(3, i1 | mutable_pipable(2));
    ZEN_TEST_EQUAL(3, i1);
    int i2 = 1;
    ZEN_TEST_EQUAL(3, mutable_pipable(i2, 2));
    ZEN_TEST_EQUAL(3, i2);
    ZEN_TEST_EQUAL(3, mono_pipable(2));
    ZEN_TEST_EQUAL(3, 2| mono_pipable);
}
#endif

#endif
