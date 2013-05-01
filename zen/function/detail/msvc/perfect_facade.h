/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    perfect_facade.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_MSVC_PERFECT_FACADE_H
#define ZEN_GUARD_MSVC_PERFECT_FACADE_H

#include <zen/pp.h>
#include <zen/config.h>
#include <zen/function/result_of.h>
#include <zen/forward.h>

#define ZEN_DETAIL_PERFECT_FACADE(z, n, F, function) \
template<ZEN_PP_PARAMS_Z(z, n, class T)> \
typename zen::result_of<F(ZEN_PP_PARAMS_Z(z, n, T, && BOOST_PP_INTERCEPT))>::type \
operator()(ZEN_PP_PARAMS_Z(z, n, T, && x)) const \
{ return function( ZEN_PP_PARAMS_Z(z, n, zen::forward<T, > BOOST_PP_INTERCEPT, (x)) ); }

#define ZEN_DETAIL_PERFECT_FACADE_OP(z, n, data) ZEN_PP_MSVC_INVOKE(ZEN_DETAIL_PERFECT_FACADE, (z, n, ZEN_PP_REM data))
#define ZEN_PERFECT_FACADE(type, f) BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_PARAMS_LIMIT, ZEN_DETAIL_PERFECT_FACADE_OP, (type, f))

//Template parameters
#define ZEN_DETAIL_PERFECT_FACADE_TPL(z, n, F, function, tpl) \
template<tpl T_ ## tpl, ZEN_PP_PARAMS_Z(z, n, class T)> \
typename zen::result_of<F(ZEN_PP_PARAMS_Z(z, n, T, && BOOST_PP_INTERCEPT))>::type \
operator()(ZEN_PP_PARAMS_Z(z, n, T, && x)) const \
{ return function( ZEN_PP_PARAMS_Z(z, n, zen::forward<T, > BOOST_PP_INTERCEPT, (x)) ); }

#define ZEN_DETAIL_PERFECT_FACADE_OP_TPL(z, n, data) ZEN_PP_MSVC_INVOKE(ZEN_DETAIL_PERFECT_FACADE_TPL, (z, n, ZEN_PP_REM data))
#define ZEN_PERFECT_FACADE_TPL(type, f, tpl) BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_PARAMS_LIMIT, ZEN_DETAIL_PERFECT_FACADE_OP_TPL, (type, f, tpl))


#endif
