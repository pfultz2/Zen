/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    assert.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ZEN_ASSERT_H
#define ZEN_GUARD_ZEN_ASSERT_H


#include <iostream>
#include <boost/current_function.hpp>
#include <zen/pp.h>
#include <zen/static_assert.h>
#include <zen/typeof.h>

#ifndef ZEN_HAS_ASSERTS
#ifndef NDEBUG
#define ZEN_HAS_ASSERTS 1
#else
#define ZEN_HAS_ASSERTS 0
#endif
#endif

#define ZEN_ASSERT(...) BOOST_PP_CAT(ZEN_DETAIL_ASSERT_, ZEN_PP_NARGS(__VA_ARGS__))(__VA_ARGS__)

#if ZEN_HAS_ASSERTS

#define ZEN_DETAIL_ASSERT_1(cond) \
    ((cond) ? ((void)0) : ::zen::assertion::failed(zen::assertion::void_(), #cond, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define ZEN_DETAIL_ASSERT_2(cond, msg) \
    ((cond) ? ((void)0) : ::zen::assertion::failed_msg(zen::assertion::void_(), #cond, msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define ZEN_ASSERT_EXPR(cond, expr) \
    ((cond) ? (expr) : ::zen::assertion::failed((ZEN_AVOID(expr)), #cond, "", __FILE__, __LINE__))

#else

#define ZEN_DETAIL_ASSERT_1(cond) ((void)0)
#define ZEN_DETAIL_ASSERT_2(cond, msg) ((void)0)
#define ZEN_ASSERT_EXPR(cond, expr) expr

#endif

namespace zen { namespace assertion {

typedef zen::typeof_detail::void_ void_;

template<class T>
struct result
{
    typedef T& type;
};

template<>
struct result<void_>
{
    typedef void type;
};

template<>
struct result<const void_>
{
    typedef void type;
};

template<class T>
typename result<T>::type failed_msg(T&, char const * cond, char const * msg, char const * function, char const * file, long line)
{
    std::cerr
      << "***** Internal Program Error - assertion (" << cond << ") failed in "
      << function << ":\n"
      << file << '(' << line << "): " << msg << std::endl;
    std::abort();
}

template<class T>
typename result<const T>::type failed_msg(const T&, char const * cond, char const * msg, char const * function, char const * file, long line)
{
    std::cerr
      << "***** Internal Program Error - assertion (" << cond << ") failed in "
      << function << ":\n"
      << file << '(' << line << "): " << msg << std::endl;
    std::abort();
}

template<class T>
typename result<T>::type failed(T&, char const * cond, char const * function, char const * file, long line)
{
    std::cerr
      << "***** Internal Program Error - assertion (" << cond << ") failed in "
      << function << ":\n"
      << file << '(' << line << ")" << std::endl;
    std::abort();
}

template<class T>
typename result<const T>::type failed(const T&, char const * cond, char const * function, char const * file, long line)
{
    std::cerr
      << "***** Internal Program Error - assertion (" << cond << ") failed in "
      << function << ":\n"
      << file << '(' << line << ")" << std::endl;
    std::abort();
}

#ifdef ZEN_TEST
namespace test {

int by_value();
int& by_ref();
const int& by_const_ref();
void by_void();

void assert_check()
{
    ZEN_ASSERT(true);
    ZEN_ASSERT(true, "This should work");
    static_assert(not boost::is_reference<ZEN_XTYPEOF(ZEN_ASSERT_EXPR(true, by_value()))>::value, "Failed");
    static_assert(not zen::typeof_detail::is_const2<ZEN_XTYPEOF(ZEN_ASSERT_EXPR(true, by_value()))>::value, "Failed");

    static_assert(boost::is_reference<ZEN_XTYPEOF(ZEN_ASSERT_EXPR(true, by_ref()))>::value, "Failed");
    static_assert(not zen::typeof_detail::is_const2<ZEN_XTYPEOF(ZEN_ASSERT_EXPR(true, by_ref()))>::value, "Failed");

    static_assert(boost::is_reference<ZEN_XTYPEOF(ZEN_ASSERT_EXPR(true, by_const_ref()))>::value, "Failed");
    static_assert(zen::typeof_detail::is_const2<ZEN_XTYPEOF(ZEN_ASSERT_EXPR(true, by_const_ref()))>::value, "Failed");

    static_assert(boost::is_same<ZEN_XTYPEOF(ZEN_ASSERT_EXPR(true, by_void())), void>::value, "Failed");
}

}


#endif

}}

#endif
