/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    lambda.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_MPL_LAMBDA_H
#define ZEN_GUARD_MPL_LAMBDA_H

#include <zen/mpl/quote.h>
#include <zen/mpl/is_placeholder_expression.h>
#include <zen/mpl/replace_args.h>

namespace zen { namespace mpl {

namespace detail {

template<class F>
struct lambda_impl
{
    template<class... Ts>
    struct apply
    : replace_args<F, Ts...>
    {};
};

}

template<class T>
struct lambda
: boost::mpl::if_<is_placeholder_expression<F>,
    detail::lambda_impl<T>,
    T
>
{};
}}

#endif