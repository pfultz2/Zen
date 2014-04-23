/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    is_placeholder_expression.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_MPL_IS_PLACEHOLDER_EXPRESSION_H
#define ZEN_GUARD_MPL_IS_PLACEHOLDER_EXPRESSION_H

#include <zen/mpl/replace_args.h>
#include <boost/mpl/not.hpp>

namespace zen { namespace mpl {

namespace detail {

struct replace_all
{
    struct r {};
    template<class>
    struct apply
    {
        typedef r type;
    };
};

}

template <class T>
struct is_placeholder_expression
: boost::mpl::not_<std::is_same<typename detail::replace_args_impl<T, detail::replace_all>::type, T>>
{};

}}


#ifdef ZEN_TEST

template<class T>
struct zen_placeholder_test
{};
static_assert(not zen::mpl::is_placeholder_expression<zen_placeholder_test<int>>::value, "Placeholder expression");
static_assert(zen::mpl::is_placeholder_expression<zen::mpl::_1>::value, "Placeholder expression");
static_assert(zen::mpl::is_placeholder_expression<zen_placeholder_test<zen::mpl::_>>::value, "Placeholder expression");
static_assert(zen::mpl::is_placeholder_expression<zen_placeholder_test<zen::mpl::_1>>::value, "Placeholder expression");

#endif

#endif