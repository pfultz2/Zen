/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    any_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_MPL_ANY_OF_H
#define ZEN_GUARD_MPL_ANY_OF_H

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/begin_end.hpp>


namespace zen { namespace mpl {

template<class Sequence, class MF>
struct any_of
: boost::mpl::not_
<
    boost::is_same<typename boost::mpl::find_if<Sequence, MF>::type, typename boost::mpl::end<Sequence>::type>
>
{};

}}

#ifdef ZEN_TEST
#include <boost/mpl/vector.hpp>
#include <zen/static_assert.h>

namespace zen { namespace mpl_any_of_test {

struct foo {};
struct bar {};

template<class T, class Enable = void>
struct is_foo : boost::mpl::bool_<false>
{};

template<>
struct is_foo<foo> : boost::mpl::bool_<true>
{};

typedef boost::mpl::vector<foo, foo, foo> all_foo;
typedef boost::mpl::vector<foo, bar, foo> some_foo;
typedef boost::mpl::vector<bar, bar> no_foo;

typedef is_foo<boost::mpl::arg<1> > is_foo_lambda;

static_assert((zen::mpl::any_of<all_foo, is_foo_lambda >::type::value), "Failed");
static_assert((zen::mpl::any_of<some_foo, is_foo_lambda >::type::value), "Failed");
static_assert((!zen::mpl::any_of<no_foo, is_foo_lambda >::type::value), "Failed");

}}

#endif

#endif
