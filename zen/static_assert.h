/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    static_assert.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/


#ifndef ZEN_GUARD_STATIC_ASSERT_H
#define ZEN_GUARD_STATIC_ASSERT_H

#include <zen/config.h>
#include <zen/pp.h>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/if.hpp>

#ifdef ZEN_NO_STATIC_ASSERT
#include <boost/static_assert.hpp>
#define ZEN_DETAIL_STATIC_ASSERT_SEQ(seq) \
BOOST_STATIC_ASSERT((BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_POP_BACK(seq))))

#define ZEN_STATIC_ASSERT(...) ZEN_DETAIL_STATIC_ASSERT_SEQ(ZEN_PP_ARGS_TO_SEQ(__VA_ARGS__))

#ifndef ZEN_USE_STATIC_ASSERT_KEYWORD
#define ZEN_USE_STATIC_ASSERT_KEYWORD 1
#endif

#if ZEN_USE_STATIC_ASSERT_KEYWORD
#define static_assert ZEN_STATIC_ASSERT
#endif

#else
#define ZEN_STATIC_ASSERT static_assert
#endif


namespace zen {

template<class T>
struct STATIC_ASSERTION_FAILURE;

namespace detail {

template<class T>
struct static_depend
{
    typedef static_depend type;
    static const bool value = false;
};    

template<int N>
struct static_assert_test
{};
struct static_assert_ignore {};

template<class T>
struct static_mpl_assert
: boost::mpl::if_<T, static_assert_ignore, STATIC_ASSERTION_FAILURE<T> >::type
{};

}


#define ZEN_STATIC_MPL_ASSERT(...) typedef zen::detail::static_assert_test<sizeof(zen::detail::static_mpl_assert<__VA_ARGS__>)> BOOST_PP_CAT(zen_static_mpl_assert_typedef_, __LINE__)
#define ZEN_STATIC_ASSERT_SAME(...) ZEN_STATIC_MPL_ASSERT(boost::is_same<__VA_ARGS__>)

#define ZEN_STATIC_DEBUG(T, msg) static_assert(zen::detail::static_depend<T>::value, msg)

}

#endif
