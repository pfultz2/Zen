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

#ifndef ZEN_HAS_ASSERTS
#ifndef NDEBUG
#define ZEN_HAS_ASSERTS 1
#else
#define ZEN_HAS_ASSERTS 0
#endif
#endif

#ifndef _MSC_VER
#define ZEN_ASSERT(...) BOOST_PP_CAT(ZEN_DETAIL_ASSERT_, ZEN_PP_NARGS(__VA_ARGS__))(__VA_ARGS__)
#else
#define ZEN_ASSERT(...) ZEN_PP_MSVC_INVOKE(BOOST_PP_CAT(ZEN_DETAIL_ASSERT_, ZEN_PP_NARGS(__VA_ARGS__)), (__VA_ARGS__))
#endif

#if ZEN_HAS_ASSERTS

#define ZEN_DETAIL_ASSERT_1(cond) \
    ((cond) ? ((void)0) : ::zen::assertion::failed(#cond, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define ZEN_DETAIL_ASSERT_2(cond, msg) \
    ((cond) ? ((void)0) : ::zen::assertion::failed_msg(#cond, msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define ZEN_ASSERT_EXPR(cond, expr) \
    ((cond) ? (expr) : ::zen::assertion::failed_expr<decltype(expr)>(#cond, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

#else

#define ZEN_DETAIL_ASSERT_1(cond) ((void)0)
#define ZEN_DETAIL_ASSERT_2(cond, msg) ((void)0)
#define ZEN_ASSERT_EXPR(cond, expr) expr

#endif

namespace zen { namespace assertion {

void failed_msg(char const * cond, char const * msg, char const * function, char const * file, long line)
{
    std::cerr
      << "***** Internal Program Error - assertion (" << cond << ") failed in "
      << function << ":\n"
      << file << '(' << line << "): " << msg << std::endl;
    std::abort();
}

void failed(char const * cond, char const * function, char const * file, long line)
{
    std::cerr
      << "***** Internal Program Error - assertion (" << cond << ") failed in "
      << function << ":\n"
      << file << '(' << line << ")" << std::endl;
    std::abort();
}

template<class T>
struct result
{
    typedef T&& type;
};

template<>
struct result<void>
{
    typedef void type;
};

template<class T>
typename result<T>::type failed_expr(char const * cond, char const * function, char const * file, long line)
{
    std::cerr
      << "***** Internal Program Error - assertion (" << cond << ") failed in "
      << function << ":\n"
      << file << '(' << line << ")" << std::endl;
    std::abort();
}

#ifdef ZEN_TEST
namespace zen { namespace test_assert {


int by_value();
int& by_ref();
const int& by_const_ref();
int&& by_rvalue_ref();
void by_void();

void assert_check()
{
    ZEN_ASSERT(true);
    ZEN_ASSERT(true, "This should work");
    static_assert(std::is_same<decltype(ZEN_ASSERT_EXPR(true, by_value())), decltype(by_value())>::value, "Failed");
    static_assert(std::is_same<decltype(ZEN_ASSERT_EXPR(true, by_ref())), decltype(by_ref())>::value, "Failed");
    static_assert(std::is_same<decltype(ZEN_ASSERT_EXPR(true, by_const_ref())), decltype(by_const_ref())>::value, "Failed");
    static_assert(std::is_same<decltype(ZEN_ASSERT_EXPR(true, by_rvalue_ref())), decltype(by_rvalue_ref())>::value, "Failed");
    static_assert(std::is_same<decltype(ZEN_ASSERT_EXPR(true, by_void())), decltype(by_void())>::value, "Failed");

}

}}


#endif

}}

#endif
