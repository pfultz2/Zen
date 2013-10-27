/*=============================================================================
    Copyright (c) 2013 Paul Fultz II
    sequence.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_DETAIL_SEQUENCE_H
#define ZEN_GUARD_DETAIL_SEQUENCE_H

#ifndef ZEN_NO_VARIADIC_TEMPLATES
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

template<class X, class Y>
struct result_of_sequence_cat
{
    typedef typename std::remove_cv<typename std::decay<X>::type>::type x_type;
    typedef typename std::remove_cv<typename std::decay<Y>::type>::type y_type;
    typedef decltype(std::tuple_cat(std::declval<const x_type&>(), std::declval<const y_type&>())) type;
};

template<class X, class Y>
typename result_of_sequence_cat<X, Y>::type sequence_cat(const X& x, const Y& y)
{
    return std::tuple_cat(x, y);
}


#else
template<class X, class Y>
struct result_of_sequence_cat
: boost::fusion::result_of::as_vector<typename boost::fusion::result_of::join
<
    typename boost::decay<X>::type,
    typename boost::decay<Y>::type
>::type>
{};

template<class X, class Y>
typename result_of_sequence_cat<X, Y>::type sequence_cat(const X& x, const Y& y)
{
    return boost::fusion::as_vector(boost::fusion::join 
    ( 
        x, 
        y 
    ));
}

#endif

}}

#endif