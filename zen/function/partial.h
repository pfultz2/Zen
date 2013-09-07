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

#include <zen/function/adaptor.h>
#include <zen/function/conditional.h>
#include <zen/function/static.h>
#include <zen/forward.h>
#include <zen/function/invoke.h>
#include <zen/function/pipable.h>
#include <zen/function/detail/nullary_tr1_result_of.h>

#include <boost/fusion/include/join.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits.hpp>

#ifndef ZEN_NO_VARIADIC_TEMPLATES
#include <tuple>
#include <boost/fusion/adapted/std_tuple.hpp>
#define ZEN_PARTIAL_SEQUENCE std::tuple
#else
#include <boost/fusion/container/vector.hpp>
#define ZEN_PARTIAL_SEQUENCE boost::fusion::vector
#endif

#include <zen/function/reveal.h>

namespace zen { 

// Forward declare partial_adaptor, since it will be used below
template<class F, class Sequence=ZEN_PARTIAL_SEQUENCE<> >
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

struct partial_adaptor_invoke
{
    template<class>
    struct result;

    template<class X, class F, class Sequence, class T>
    struct result<X(F, Sequence, T)>
    : zen::result_of<typename zen::purify<F>::type(typename boost::fusion::result_of::as_vector<typename boost::fusion::result_of::join
    <
        typename boost::decay<Sequence>::type,
        typename boost::decay<T>::type
    >::type>::type)>
    {};

    template<class F, class Sequence, class T>
    typename result<partial_adaptor_invoke(F, Sequence, T)>::type
    operator()(F f, Sequence& seq, const T& x) const
    {
        return  f(boost::fusion::as_vector(boost::fusion::join
        (
            seq,
            x
        )));
    }
};


struct decay_elem
{
    template <typename T>
    struct unwrap_reference
    : boost::mpl::if_<boost::is_reference_wrapper<T>, typename boost::unwrap_reference<T>::type&, T>
    {};
    template<class>
    struct result;

    template<class X, class T>
    struct result<X(T)>
    : unwrap_reference<typename boost::decay<T>::type>
    {};

    template<class T>
    typename result<decay_elem(T)>::type operator()(const T& x) const
    {
        return x;
    }
};

struct partial_adaptor_join
{

    partial_adaptor_join()
    {}


    template<class, class Enable=void>
    struct result;

    template<class X, class F, class Sequence, class T>
    struct result<X(F, Sequence, T), ZEN_CLASS_REQUIRES(boost::mpl::bool_<boost::fusion::result_of::size<typename boost::decay<T>::type>::value != 0>)>
    {
        typedef partial_adaptor
        <
            variadic_adaptor<typename zen::purify<F>::type>, 
            typename boost::fusion::result_of::as_vector<typename boost::fusion::result_of::transform<typename boost::fusion::result_of::join
            <
                typename boost::decay<Sequence>::type,
                typename boost::decay<T>::type
            >::type, decay_elem>::type>::type
        > type;
    };



    template<class F, class Sequence, class T>
    ZEN_FUNCTION_REQUIRES(boost::mpl::bool_<boost::fusion::result_of::size<T>::value != 0>)
    (typename result<partial_adaptor_join(F, Sequence, T)>::type)
    operator()(F f, Sequence& seq, const T& x) const
    {
        return partial
        (
            variadic(f), 
            boost::fusion::as_vector(boost::fusion::transform(boost::fusion::join
            (
                seq,
                x
            ), decay_elem()))
        );
    }

    // TODO: Add support for nullary partial application
    // template<class X, class F, class Sequence, class T>
    // struct result<X(F, Sequence, T), ZEN_CLASS_REQUIRES(boost::mpl::bool_<boost::fusion::result_of::size<typename boost::decay<T>::type>::value == 0>)>
    // {
    //     typedef partial_adaptor<variadic_adaptor<typename zen::purify<F>::type>, typename boost::decay<Sequence>::type> type;
    // };

    // template<class F, class Sequence, class T>
    // ZEN_FUNCTION_REQUIRES(boost::mpl::bool_<boost::fusion::result_of::size<T>::value == 0>)
    // (typename result<partial_adaptor_join(F, Sequence, T)>::type)
    // operator()(F f, const Sequence& seq, const T& x) const
    // {
    //     return partial(variadic(f), seq);
    // }
};

typedef zen::conditional_adaptor<partial_adaptor_invoke, partial_adaptor_join > partial_cond;

template<class F, class Sequence, class Enable = void>
struct partial_adaptor_base : partial_cond, zen::function_adaptor_base<F>
{
    typedef zen::function_adaptor_base<F> base;
    typedef void zen_is_callable_by_result_tag;
    Sequence seq;

    partial_adaptor_base(Sequence seq) : seq(seq)
    {}

    template<class X>
    partial_adaptor_base(X x, Sequence seq) : base(x), seq(seq)
    {}

    // MSVC Workarounds
    partial_adaptor_base(const partial_adaptor_base& rhs) : 
    partial_cond(static_cast<const partial_cond&>(rhs)), 
    zen::function_adaptor_base<F>(static_cast<const zen::function_adaptor_base<F>&>(rhs)),
    seq(rhs.seq)
    {}

    using partial_cond::operator();

    template<class>
    struct result;

    template<class X, class T>
    struct result<X(T)>
    : zen::result_of<partial_cond(F, Sequence, T)>
    {};

    template<class T>
    typename result<partial_adaptor_base(T)>::type
    operator()(const T& x) const
    {
        return (*this)(this->base::get_function(), this->seq, x);
    }

    template<class X>
    struct result<X()>
    {
        typedef partial_adaptor_base<F, Sequence> type;
    };

    const partial_adaptor_base<F, Sequence>& operator()() const
    {
        return *this;
    }
};

// Empty sequence optimization
template<class F, class Sequence>
struct partial_adaptor_base<F, Sequence, ZEN_CLASS_REQUIRES(boost::mpl::bool_<boost::fusion::result_of::size<Sequence>::value == 0>)>
: partial_cond, zen::function_adaptor_base<F>
{
    typedef void zen_is_callable_by_result_tag;
    typedef zen::function_adaptor_base<F> base;

    partial_adaptor_base()
    {}

    partial_adaptor_base(Sequence)
    {}

    template<class X>
    partial_adaptor_base(X x, Sequence) : base(x)
    {}

    // MSVC Workarounds
    partial_adaptor_base(const partial_adaptor_base& rhs) : 
    partial_cond(static_cast<const partial_cond&>(rhs)), 
    zen::function_adaptor_base<F>(static_cast<const zen::function_adaptor_base<F>&>(rhs))
    {}

    using partial_cond::operator();

    template<class>
    struct result;

    template<class X, class T>
    struct result<X(T)>
    : zen::result_of<partial_cond(F, Sequence, T)>
    {};

    template<class T>
    typename result<partial_adaptor_base(T)>::type
    operator()(const T& x) const
    {
        return (*this)(this->base::get_function(), Sequence(), x);
    }

    template<class X>
    struct result<X()>
    {
        typedef partial_adaptor_base<F, Sequence> type;
    };

    const partial_adaptor_base<F, Sequence>& operator()() const
    {
        return *this;
    }
};

}

#define ZEN_PARTIAL_ADAPTOR_BASE(F, Sequence) detail::partial_adaptor_base<F, Sequence >

template<class F, class Sequence >
struct partial_adaptor 
: zen::variadic_adaptor<ZEN_PARTIAL_ADAPTOR_BASE(zen::fuse_adaptor<F>, Sequence) >
{
    typedef ZEN_PARTIAL_ADAPTOR_BASE(zen::fuse_adaptor<F>, Sequence) base;
    template<class X>
    partial_adaptor(X x, Sequence seq) : zen::variadic_adaptor<base>(base(x, seq))
    {}

    template<class X>
    partial_adaptor(X x) : zen::variadic_adaptor<base>(base(x, x.get_sequence()))
    {}

    Sequence get_sequence() const
    {
        return this->zen::variadic_adaptor<base>::get_function().seq;
    }

    typename function_adaptor_type<F>::type get_function () const
    {
        return this->zen::variadic_adaptor<base>::get_function().get_function();
    }
};

template<class F>
struct partial_adaptor<F, ZEN_PARTIAL_SEQUENCE<> > 
: zen::variadic_adaptor<ZEN_PARTIAL_ADAPTOR_BASE(zen::fuse_adaptor<F>, ZEN_PARTIAL_SEQUENCE<>) >
{
    typedef ZEN_PARTIAL_ADAPTOR_BASE(zen::fuse_adaptor<F>, ZEN_PARTIAL_SEQUENCE<>) base;

    partial_adaptor()
    {}

    template<class X>
    partial_adaptor(X x) : zen::variadic_adaptor<base>(base(x, ZEN_PARTIAL_SEQUENCE<>()))
    {}

    // MSVC Workarounds
    partial_adaptor(const partial_adaptor& rhs) : zen::variadic_adaptor<base>(static_cast<const zen::variadic_adaptor<base>&>(rhs))
    {}

    ZEN_PARTIAL_SEQUENCE<> get_sequence() const
    {
        return ZEN_PARTIAL_SEQUENCE<>();
    }

    typename function_adaptor_type<F>::type get_function () const
    {
        return this->zen::variadic_adaptor<base>::get_function().get_function();
    }
};
// Apply partial to a pipable function, removes the pipableness
template<class F>
struct partial_adaptor<pipable_adaptor<F>, ZEN_PARTIAL_SEQUENCE<> > 
: partial_adaptor<F, ZEN_PARTIAL_SEQUENCE<> >
{
    typedef partial_adaptor<F, ZEN_PARTIAL_SEQUENCE<> > base;

    partial_adaptor()
    {}

    partial_adaptor(pipable_adaptor<F> f) : base(f.get_function())
    {}

    template<class X>
    partial_adaptor(X x) : base(x)
    {}

    // MSVC Workarounds
    partial_adaptor(const partial_adaptor& rhs) : base(static_cast<const base&>(rhs))
    {}

    ZEN_PARTIAL_SEQUENCE<> get_sequence() const
    {
        return ZEN_PARTIAL_SEQUENCE<>();
    }
};

template<class F>
struct partial_adaptor<static_<pipable_adaptor<F> >, ZEN_PARTIAL_SEQUENCE<> > 
: partial_adaptor<F, ZEN_PARTIAL_SEQUENCE<> >
{
    typedef partial_adaptor<F, ZEN_PARTIAL_SEQUENCE<> > base;

    partial_adaptor()
    {}

    template<class X>
    partial_adaptor(X x) : base(x)
    {}

    // MSVC Workarounds
    partial_adaptor(const partial_adaptor& rhs) : base(static_cast<const base&>(rhs))
    {}

    ZEN_PARTIAL_SEQUENCE<> get_sequence() const
    {
        return ZEN_PARTIAL_SEQUENCE<>();
    }
};



// Optimizations for fuse adaptors
template<class F, class Sequence >
struct partial_adaptor<zen::fuse_adaptor<F>, Sequence>
: ZEN_PARTIAL_ADAPTOR_BASE(zen::fuse_adaptor<F>, Sequence)
{
    typedef ZEN_PARTIAL_ADAPTOR_BASE(zen::fuse_adaptor<F>, Sequence) base;
    template<class X>
    partial_adaptor(X x, Sequence seq) : base(x, seq)
    {}

    template<class X>
    partial_adaptor(X x) : base(x, x.get_sequence())
    {}

    Sequence get_sequence() const
    {
        return this->seq;
    }

    typename function_adaptor_type<F>::type get_function () const
    {
        return this->base::get_function().get_function();
    }
};

template<class F>
struct partial_adaptor<zen::fuse_adaptor<F>, ZEN_PARTIAL_SEQUENCE<> > 
: ZEN_PARTIAL_ADAPTOR_BASE(zen::fuse_adaptor<F>, ZEN_PARTIAL_SEQUENCE<>)
{
    typedef ZEN_PARTIAL_ADAPTOR_BASE(zen::fuse_adaptor<F>, ZEN_PARTIAL_SEQUENCE<>) base;

    partial_adaptor()
    {}

    template<class X>
    partial_adaptor(X x) : base(x)
    {}

    // MSVC Workarounds
    partial_adaptor(const partial_adaptor& rhs) : base(static_cast<const base&>(rhs))
    {}

    ZEN_PARTIAL_SEQUENCE<> get_sequence() const
    {
        return ZEN_PARTIAL_SEQUENCE<>();
    }

    typename function_adaptor_type<F>::type get_function () const
    {
        return this->base::get_function().get_function();
    }
};

}

ZEN_NULLARY_TR1_RESULT_OF_N(2, zen::partial_adaptor)


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
    // TODO: Add supoort for nullary partial application
    zen::partial_adaptor<void_class>()(1);

    void_partial(1);
    // void_partial()(1);
    ZEN_TEST_EQUAL(3, binary_partial(1)(2));
    ZEN_TEST_EQUAL(3, binary_partial(1, 2));
    // ZEN_TEST_EQUAL(3, unary_partial()(3));
    ZEN_TEST_EQUAL(3, unary_partial(3));
    ZEN_TEST_EQUAL(3, mono_partial(2));
    // ZEN_TEST_EQUAL(3, mono_partial()(2));

    int i1 = 1;
    ZEN_TEST_EQUAL(3, binary_partial(2)(i1));
    ZEN_TEST_EQUAL(3, mutable_partial(boost::ref(i1))(2));
    ZEN_TEST_EQUAL(3, i1);
    int i2 = 1;
    ZEN_TEST_EQUAL(3, mutable_partial(i2, 2));
    ZEN_TEST_EQUAL(3, i2);
    
}
#endif

#endif
