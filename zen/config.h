/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    config.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_CONFIG_H
#define ZEN_GUARD_CONFIG_H

#ifndef ZEN_PARAMS_LIMIT
#define ZEN_PARAMS_LIMIT 8
#endif

#ifdef _MSC_VER

#define ZEN_NO_RANGE_FOR
#define ZEN_NO_VARIADIC_TEMPLATES
#define ZEN_NO_OVERRIDE_CONTROL
#define ZEN_NO_EXPRESSION_SFINAE
#define ZEN_NO_NOEXCEPT


#endif

#ifdef __clang__
#if !__has_feature(cxx_decltype)
#define ZEN_NO_DECLTYPE
#else
#define ZEN_HAS_TYPEOF
#endif
#if !__has_feature(cxx_lambdas)
#define ZEN_NO_LAMBDAS
#endif
#if !__has_feature(cxx_range_for)
#define ZEN_NO_RANGE_FOR
#endif
#if !__has_feature(cxx_rvalue_references)
#define ZEN_NO_RVALUE_REFS
#endif
#if !__has_feature(cxx_static_assert)
#define ZEN_NO_STATIC_ASSERT
#endif
#if !__has_feature(cxx_auto_type)
#define ZEN_NO_AUTO
#endif
#if !__has_feature(cxx_trailing_return)
#define ZEN_NO_TRAILING_RETURN
#endif
#if !__has_feature(cxx_variadic_templates)
#define ZEN_NO_VARIADIC_TEMPLATES
#endif

#if !__has_feature(cxx_override_control)
#define ZEN_NO_OVERRIDE_CONTROL
#endif

#endif

#ifdef __GNUC__
#define ZEN_HAS_TYPEOF
#ifndef __clang__
//#define ZEN_NO_EXPRESSION_SFINAE

#ifndef ZEN_GCC_11
#define ZEN_NO_STD_TUPLE
#define ZEN_NO_DECLTYPE
#define ZEN_NO_LAMBDAS
#define ZEN_NO_RANGE_FOR
#define ZEN_NO_RVALUE_REFS
#define ZEN_NO_STATIC_ASSERT
#define ZEN_NO_AUTO
#define ZEN_NO_TRAILING_RETURN
#define ZEN_NO_VARIADIC_TEMPLATES
#define ZEN_NO_OVERRIDE_CONTROL
#endif
#endif


#endif

#endif
