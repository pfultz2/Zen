/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    invoke.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_INVOKE_H
#define ZEN_GUARD_FUNCTION_INVOKE_H

// @begin
// invoke
// ======
// 
// Description
// -----------
// 
// Calls a function object with the arguments from a fusion sequence.
// 
// Synopsis
// --------
// 
//     template<class F, class Sequence>
//     typename invoke_result<F, Sequence>::type
//     invoke(F f, const Sequence& seq);
// 
// Example
// -------
// 
//     std::plus<int> add;
//     assert(invoke(add,boost::fusion::make_vector(1,1)) == 2);
// 
// @end

#include <zen/pp.h>
#include <zen/config.h>
#include <zen/forward.h>
#include <zen/typeof.h>
#include <zen/function/result_of.h>
#include <zen/requires.h>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace zen { 

namespace detail {

template<class S>
struct decay_seq
: boost::remove_cv<typename boost::decay<S>::type>
{};

template<class S>
struct seq_size
: boost::fusion::result_of::size<typename decay_seq<S>::type>
{};

}

#ifndef ZEN_NO_VARIADIC_TEMPLATES

//
// invoke
//
namespace detail {

template<int ...>
struct seq {};

template<int N, int ...S>
struct gens : gens<N-1, N-1, S...> {};

template<int ...S>
struct gens<0, S...> 
{
  typedef seq<S...> type;
};

template<class T>
struct sequence_gens
: gens<detail::seq_size<T>::value> {};


template<class F, class T, class S, class Enable = void>
struct invoke_result_impl
{};

template<class F, class T, int ...N>
struct invoke_result_impl<F, T, seq<N...> >
: zen::result_of<F(typename boost::fusion::result_of::at_c<typename boost::add_const<T>::type, N>::type...)>
{};

template<class F, class T, int ...N>
// typename zen::result_of<F(typename boost::fusion::result_of::at_c<const T, N>::type...)>::type 
typename invoke_result_impl<F, T, seq<N...> >::type
invoke_impl(F f, const T & t, seq<N...>)
{
    return f(boost::fusion::at_c<N>(t)...);
}

}

template<class F, class T>
struct invoke_result
: detail::invoke_result_impl<F, typename boost::decay<T>::type, typename detail::sequence_gens<T>::type> {};

template<class F, class Sequence>
typename invoke_result<F, Sequence>::type 
invoke(F f, const Sequence & t)
{
    return detail::invoke_impl(f, t, typename detail::sequence_gens<Sequence>::type() );
}

#else

namespace detail {

template<class Sequence>
struct invoke_element
{
    template<int N>
    struct at_c
    : boost::fusion::result_of::at_c<typename boost::add_const<typename boost::decay<Sequence>::type>::type, N>
    {};
};

template<int N>
struct invoke_impl
{};

template<class T>
const T& invoke_forward(const T& x)
{
    return x;
}

template<class T>
T& invoke_forward(T& x)
{
    return x;
}
#ifndef ZEN_NO_RVALUE_REFS
#define ZEN_INVOKE_M(z, n, data) invoke_forward(boost::fusion::at_c<n>(s))
#else
#define ZEN_INVOKE_M(z, n, data) boost::fusion::at_c<n>(s)
#endif
#define ZEN_INVOKE(z, n, data) \
template<> \
struct invoke_impl<n> \
{ \
    template<class F> struct result; \
    template<class F, class Sequence> \
    struct result<F(Sequence)> \
    : zen::result_of<F(ZEN_PP_PARAMS_Z(z, n, typename invoke_element<Sequence>::template at_c<0, >::type BOOST_PP_INTERCEPT))>\
    {}; \
    template<class F, class Sequence> \
    static typename result<F(const Sequence&)>::type call(F f, const Sequence& BOOST_PP_EXPR_IF(n, s)) \
    { \
        return f(BOOST_PP_ENUM_ ## z(n, ZEN_INVOKE_M, ~)); \
    } \
};
BOOST_PP_REPEAT_1(ZEN_PARAMS_LIMIT, ZEN_INVOKE, ~)
}

template<class F, class Sequence>
struct invoke_result
: detail::invoke_impl<detail::seq_size<Sequence>::value >::template result<F(Sequence)>
{};

template<class F, class Sequence>
typename invoke_result<F, const Sequence&>::type invoke(F f, const Sequence& s)
{
    return detail::invoke_impl<detail::seq_size<Sequence>::value >::call(f, s);
}

#endif

}

#endif
