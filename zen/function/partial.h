/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    partial.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_PARTIAL_H
#define ZEN_GUARD_FUNCTION_PARTIAL_H

// @begin
// partial
// ========
// 
// Description
// -----------
// 
// The `partial` function adaptor allows partial application of the function.
// If the function can not be called with all the parameters, it will return a
// function. It will continually do this until the function can be called. By
// default, the `partial` captures all of it variables by value, just like
// bind. `boost::ref` can be used to capture references instead.
// 
// Synopsis
// --------
// 
//     template<class F>
//     partial_adaptor<F> partial(F f);
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
//     assert(3 == partial(sum())(1)(2));
// 
// @end

#include <zen/function/conditional.h>
#include <zen/function/static.h>
#include <zen/function/invoke.h>
#include <zen/function/pipable.h>
#include <zen/function/fuse.h>



namespace zen { 

// Forward declare partial_adaptor, since it will be used below
template<class F, class Sequence=std::tuple<> >
struct partial_adaptor;

template<class F>
partial_adaptor<F> partial(F f)
{
    return partial_adaptor<F>(f);
}

template<class F, class Sequence>
partial_adaptor<F, Sequence> partial(F f, Sequence seq)
{
    return partial_adaptor<F, Sequence>(f, seq);
}

namespace detail {

template<class Derived, class F, class Sequence>
struct partial_adaptor_invoke
{
    const F& get_function() const
    {
        return static_cast<const F&>(static_cast<const Derived&>(*this));
    }

    const Sequence& get_sequence() const
    {
        return static_cast<const Sequence&>(static_cast<const Derived&>(*this));
    }

    template<class T>
    auto operator()(const T& x) const ZEN_RETURNS
    (
        this->get_function()(std::tuple_cat
        (
            this->get_sequence(),
            x
        ))
    );
};

struct decay_elem_f
{
    template <class T>
    struct unwrap_reference
    {
        typedef T type;
    };
    template <class T>
    struct unwrap_reference<std::reference_wrapper<T>>
    {
        typedef T& type;
    };

    template<class T>
    typename unwrap_reference<typename std::decay<T>::type>::type 
    operator()(T&& x) const
    {
        return std::forward<T>(x);
    }
};
static decay_elem_f decay_elem = {};

template<class... T>
auto make_as_decay_tuple(T&&... x) ZEN_RETURNS
(
    make_ref_tuple(decay_elem(std::forward<T>(x))...)
);

template<class Derived, class F, class Sequence>
struct partial_adaptor_join
{
    const F& get_function() const
    {
        return static_cast<const F&>(static_cast<const Derived&>(*this));
    }

    const Sequence& get_sequence() const
    {
        return static_cast<const Sequence&>(static_cast<const Derived&>(*this));
    }

    template<class... T>
    auto operator()(T&&... x) const ZEN_RETURNS
    (
        partial
        (
            this->get_function(), 
            std::tuple_cat
            (
                this->get_sequence(),
                make_as_decay_tuple(std::forward<T>(x)...)
            )
        )
    );
};
template<class F, class Sequence>
using partial_adaptor_base = conditional_adaptor
<
    variadic_adaptor<partial_adaptor_invoke<partial_adaptor<F, Sequence>, fuse_adaptor<F>, Sequence> >,
    partial_adaptor_join<partial_adaptor<F, Sequence>, F, Sequence> 
>;
}

template<class F, class Sequence>
struct partial_adaptor : detail::partial_adaptor_base<F, Sequence>, fuse_adaptor<F>, Sequence
{
    typedef detail::partial_adaptor_base<F, Sequence> base;
    const F& base_function() const
    {
        return *this;
    }

    const Sequence& get_sequence() const
    {
        return *this;
    }

    using detail::partial_adaptor_base<F, Sequence>::operator();

    partial_adaptor()
    {}

    template<class X>
    partial_adaptor(X&& x) : fuse_adaptor<F>(std::forward<X>(x))
    {}

    template<class X, class S>
    partial_adaptor(X&& x, S&& seq) : fuse_adaptor<F>(std::forward<X>(x)), Sequence(std::forward<S>(seq))
    {}
};
// Make partial_adaptor work with pipable_adaptor by removing its pipableness
template<class F>
struct partial_adaptor<pipable_adaptor<F>, std::tuple<>>
: partial_adaptor<F, std::tuple<>>
{
    typedef partial_adaptor<F, std::tuple<>> base;
    partial_adaptor()
    {}

    template<class X>
    partial_adaptor(X&& x) : base(std::forward<X>(x))
    {}

    template<class X, class S>
    partial_adaptor(X&& x, S&& seq) : base(std::forward<X>(x), std::forward<S>(seq))
    {}
};

template<class F>
struct partial_adaptor<static_<pipable_adaptor<F>>, std::tuple<>>
: partial_adaptor<F, std::tuple<>>
{
    typedef partial_adaptor<F, std::tuple<>> base;
    partial_adaptor()
    {}

    template<class X>
    partial_adaptor(X&& x) : base(std::forward<X>(x))
    {}

    template<class X, class S>
    partial_adaptor(X&& x, S&& seq) : base(std::forward<X>(x), std::forward<S>(seq))
    {}
};
}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/detail/test.h>
#include <zen/function/static.h>

zen::static_<zen::partial_adaptor<binary_class> > binary_partial = {};

zen::static_<zen::partial_adaptor<unary_class> > unary_partial = {};

zen::static_<zen::partial_adaptor<mutable_class> > mutable_partial = {};

zen::static_<zen::partial_adaptor<void_class> > void_partial = {};

zen::static_<zen::partial_adaptor<mono_class> > mono_partial = {};

ZEN_TEST_CASE(partial_test)
{
    zen::partial_adaptor<void_class>()(1);

    void_partial(1);
    void_partial()(1);
    ZEN_TEST_EQUAL(3, binary_partial(1)(2));
    ZEN_TEST_EQUAL(3, binary_partial(1, 2));
    ZEN_TEST_EQUAL(3, unary_partial()(3));
    ZEN_TEST_EQUAL(3, unary_partial(3));
    ZEN_TEST_EQUAL(3, mono_partial(2));
    ZEN_TEST_EQUAL(3, mono_partial()(2));

    int i1 = 1;
    ZEN_TEST_EQUAL(3, binary_partial(2)(i1));
    ZEN_TEST_EQUAL(3, mutable_partial(std::ref(i1))(2));
    ZEN_TEST_EQUAL(3, i1);
    int i2 = 1;
    ZEN_TEST_EQUAL(3, mutable_partial(i2, 2));
    ZEN_TEST_EQUAL(3, i2);
    
}
#endif

#endif
