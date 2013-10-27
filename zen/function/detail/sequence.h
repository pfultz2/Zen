/*=============================================================================
    Copyright (c) 2013 Paul Fultz II
    sequence.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_DETAIL_SEQUENCE_H
#define ZEN_GUARD_DETAIL_SEQUENCE_H

#include <zen/function/identity.h>
#include <zen/function/detail/tuple_reference.h>

#ifndef ZEN_NO_VARIADIC_TEMPLATES
#include <zen/function/detail/gens.h>
#include <tuple>
#include <boost/fusion/adapted/std_tuple.hpp>
#define ZEN_FUNCTION_SEQUENCE std::tuple
#else
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/join.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#define ZEN_FUNCTION_SEQUENCE boost::fusion::vector
#endif

namespace zen { namespace detail {

#ifndef ZEN_NO_VARIADIC_TEMPLATES

template<class X, class Y, class F, class XS, class YS>
struct result_of_sequence_cat_impl;

template<class X, class Y, class F, int... N, int... M>
struct result_of_sequence_cat_impl<X, Y, F, seq<N...>, seq<M...> >
{
    typedef std::tuple
    <
        typename tuple_reference<typename zen::result_of<F(typename std::tuple_element<N, X>::type)>::type>::type..., 
        typename tuple_reference<typename zen::result_of<F(typename std::tuple_element<M, Y>::type)>::type>::type...
    > type; 
};

template<class X, class Y, class F, int... N, int... M>
typename result_of_sequence_cat_impl<X, Y, F, seq<N...>, seq<M...> >::type sequence_cat_impl(const X& x, const Y& y, F f, seq<N...>, seq<M...>)
{
    return typename result_of_sequence_cat_impl<X, Y, F, seq<N...>, seq<M...> >::type
    (
        f(std::get<N>(x))...,
        f(std::get<M>(y))...
    );
}

template<class X, class Y, class F=zen::identity_function>
struct result_of_sequence_cat
{
    typedef typename std::remove_cv<typename std::decay<X>::type>::type x_type;
    typedef typename std::remove_cv<typename std::decay<Y>::type>::type y_type;
    const static std::size_t x_size = std::tuple_size<x_type>::value;
    const static std::size_t y_size = std::tuple_size<y_type>::value;

    typedef typename result_of_sequence_cat_impl<x_type, y_type, F, typename gens<x_size>::type, typename gens<y_size>::type>::type type;
};

template<class X, class Y, class F>
typename result_of_sequence_cat<X, Y, F>::type sequence_cat(const X& x, const Y& y, F f)
{
    typedef result_of_sequence_cat<X, Y, F> result;
    return sequence_cat_impl(x, y, f, make_gens<result::x_size>(), make_gens<result::y_size>());
}

// Optimization for non transformations
// template<class X, class Y>
// struct result_of_sequence_cat<X, Y, zen::identity_function>
// {
//     typedef typename std::remove_cv<typename std::decay<X>::type>::type x_type;
//     typedef typename std::remove_cv<typename std::decay<Y>::type>::type y_type;
//     typedef decltype(std::tuple_cat(std::declval<const x_type&>(), std::declval<const y_type&>())) type;
// };

// template<class X, class Y>
// typename result_of_sequence_cat<X, Y>::type sequence_cat(const X& x, const Y& y)
// {
//     return std::tuple_cat(x, y);
// }


#else
template<class X, class Y, class F=zen::identity_function>
struct result_of_sequence_cat
: boost::fusion::result_of::as_vector<typename boost::fusion::result_of::transform<typename boost::fusion::result_of::join
<
    typename boost::decay<X>::type,
    typename boost::decay<Y>::type
>::type, F>::type>
{};

template<class X, class Y, class F>
typename result_of_sequence_cat<X, Y, F>::type sequence_cat(const X& x, const Y& y, F f)
{
    return boost::fusion::as_vector(boost::fusion::transform(boost::fusion::join 
    ( 
        x, 
        y 
    ), f));
}

#endif
template<class X, class Y>
typename result_of_sequence_cat<X, Y>::type sequence_cat(const X& x, const Y& y)
{
    return sequence_cat(x, y, identity);
}


}}

#endif