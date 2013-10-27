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

#include <zen/function/adaptor.h>
#include <zen/function/conditional.h>
#include <zen/function/static.h>
#include <zen/forward.h>
#include <zen/function/invoke.h>
#include <zen/function/detail/nullary_tr1_result_of.h>
#include <zen/function/detail/sequence.h>

#include <boost/fusion/include/join.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/type_traits.hpp>

namespace zen { 
 

namespace detail {

template<class F, class Sequence = ZEN_FUNCTION_SEQUENCE<>, class Enable = void>
struct pipe_closure_base : F
{
    typedef typename boost::remove_cv<typename boost::decay<Sequence>::type>::type sequence; 
    sequence seq;
    
	// We need the static_cast to the base class, 
	// because MSVC generates an incorrect copy constructor
	pipe_closure_base(const pipe_closure_base& rhs) : F(static_cast<const F&>(rhs)), seq(rhs.seq) {}

    template<class X, class S>
    pipe_closure_base(X f, const S& seq) : F(f), seq(seq) {};

    const sequence& get_sequence() const
    {
        return seq;
    }

};

template<class F, class Sequence>
struct pipe_closure_base<F, Sequence, ZEN_CLASS_REQUIRES(boost::mpl::bool_<boost::fusion::result_of::size<Sequence>::value == 0>)> : F
{    
    
    template<class X, class S>
    pipe_closure_base(X x, S) : F(x) {};

    // We need the static_cast to the base class, 
	// because MSVC generates an incorrect copy constructor
	pipe_closure_base(const pipe_closure_base& rhs) : F(static_cast<const F&>(rhs)) 
    {}

    Sequence get_sequence() const
    {
        return Sequence();
    }

};

template<class F, class Sequence>
struct pipe_closure : pipe_closure_base<F, Sequence>
{
    
    template<class X, class S>
    pipe_closure(X f, const S& seq) : pipe_closure_base<F, Sequence>(f, seq) {};

    template<class A>
    struct pipe_result
    : zen::invoke_result<F, typename zen::detail::result_of_sequence_cat
        <
            ZEN_FUNCTION_SEQUENCE<typename tuple_reference<A>::type>,
            typename boost::decay<Sequence>::type
        >::type>
    {};


// TODO: Use rvalue references when boost::fusion can handle them
// TODO: Update invoke to work on Forward Sequences
#define ZEN_PIPE_CLOSURE_OP(T) \
    template<class A> \
    friend typename pipe_result<T>::type \
    operator|(ZEN_FORWARD_REF(T) a, const pipe_closure<F, Sequence>& p) \
    { \
        return zen::invoke(p, zen::detail::sequence_cat \
        ( \
            ZEN_FUNCTION_SEQUENCE<typename tuple_reference<ZEN_FORWARD_REF(T)>::type>(zen::forward<T>(a)), \
            p.get_sequence() \
        )); \
    }
    ZEN_PIPE_CLOSURE_OP(A)
#ifdef ZEN_NO_RVALUE_REFS
    ZEN_PIPE_CLOSURE_OP(const A)
#endif
};

template<class F>
struct make_pipe_closure : function_adaptor_base<F>
{
    make_pipe_closure()
    {};

    template<class X>
    make_pipe_closure(X x) : function_adaptor_base<F>(x)
    {};

    template<class X>
    struct result;

    template<class X, class T>
    struct result<X(T)>
    {
        typedef pipe_closure<F, typename boost::remove_cv<typename boost::decay<T>::type>::type> type;
    };

    template<class T>
    pipe_closure<F, T> 
    operator()(const T& t) const
    {
        return pipe_closure<F, T>(this->get_function(), t);
    }
};
    
}

template<class F, class FunctionBase=conditional_adaptor<F, variadic_adaptor<detail::make_pipe_closure<F> > > >
struct pipable_adaptor 
: detail::pipe_closure<FunctionBase, ZEN_FUNCTION_SEQUENCE<> >
{
    typedef detail::pipe_closure<FunctionBase, ZEN_FUNCTION_SEQUENCE<> > base;

    pipable_adaptor() : base(FunctionBase(), ZEN_FUNCTION_SEQUENCE<>())
    {};

    template<class X>
    pipable_adaptor(X x) : base(x, ZEN_FUNCTION_SEQUENCE<>())
    {};

    // MSVC Workaround
    pipable_adaptor(const pipable_adaptor& rhs) : base(static_cast<const base&>(rhs))
    {}
};


template<class F>
pipable_adaptor<F> pipable(F f)
{
    return pipable_adaptor<F>(f);
}

// Operators for static_ adaptor
#define ZEN_PIPE_STATIC_OP(T) \
template<class A, class F> \
typename F::template pipe_result<T>::type \
operator|(ZEN_FORWARD_REF(T) a, static_<F> f) \
{ \
    return f(zen::forward<T>(a)); \
}
ZEN_PIPE_STATIC_OP(A)
#ifdef ZEN_NO_RVALUE_REFS
ZEN_PIPE_STATIC_OP(const A)
#endif
}

ZEN_NULLARY_TR1_RESULT_OF_N(2, zen::pipable_adaptor)

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
