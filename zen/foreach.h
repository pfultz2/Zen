/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    foreach.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ZEN_FOREACH_H
#define ZEN_GUARD_ZEN_FOREACH_H

#include <boost/foreach.hpp>
#include <zen/typeof.h>
#include <zen/pp.h>

#define ZEN_FOREACH_KEYWORD(x) BOOST_PP_CAT(ZEN_FOREACH_KEYWORD_, x)
#define ZEN_FOREACH_KEYWORD_const (const)
#define ZEN_FOREACH_KEYWORD_volatile (volatile)
#define ZEN_FOREACH_KEYWORD_auto (())

#define ZEN_FOREACH_PROCESS_AUTO(x, col) \
DETAIL_ZEN_FOREACH_PROCESS_AUTO_INVOKE_M(BOOST_PP_WHILE(DETAIL_ZEN_FOREACH_PROCESS_AUTO_INVOKE_P, DETAIL_ZEN_FOREACH_PROCESS_AUTO_INVOKE_OP, (, x, col, ZEN_PP_TRUE())))
#ifndef _MSC_VER
#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_INVOKE_P(d, state) DETAIL_ZEN_FOREACH_PROCESS_AUTO_P state
#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_INVOKE_OP(d, state) DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP state
#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_INVOKE_M(state) DETAIL_ZEN_FOREACH_PROCESS_AUTO_M state
#else
#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_INVOKE_P(d, state) ZEN_PP_MSVC_INVOKE(DETAIL_ZEN_FOREACH_PROCESS_AUTO_P, state)
#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_INVOKE_OP(d, state) ZEN_PP_MSVC_INVOKE(DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP, state)
#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_INVOKE_M(state) ZEN_PP_MSVC_INVOKE(DETAIL_ZEN_FOREACH_PROCESS_AUTO_M, state)
#endif

#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_M(head, tail, col, eof) head tail
#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_P(head, tail, col, eof) eof
#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP(head, tail, col, eof) DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_I(head, tail, col, ZEN_FOREACH_KEYWORD(tail))

#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_I(head, tail, col, x) \
BOOST_PP_IIF(ZEN_PP_IS_PAREN(x), DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_KEYWORD, DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_UFO)(head, tail, col, x)

#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_KEYWORD(head, tail, col, x) DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_KEYWORD_I(head, tail, col, x, BOOST_PP_SEQ_HEAD(x))
#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_UFO(head, tail, col, x) (head, tail, col, ZEN_PP_FALSE())

#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_KEYWORD_I(head, tail, col, x, key) \
BOOST_PP_IIF(ZEN_PP_IS_PAREN(key), DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_AUTO, DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_CV)(head, tail, col, x, key)

#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_AUTO(head, tail, col, x, key) (head ZEN_TYPEOF((*boost::begin(col))) ZEN_PP_EAT key, BOOST_PP_SEQ_TAIL(x), col, ZEN_PP_FALSE())
#define DETAIL_ZEN_FOREACH_PROCESS_AUTO_OP_CV(head, tail, col, x, key) (head key, BOOST_PP_SEQ_TAIL(x), col, ZEN_PP_TRUE())

#define ZEN_FOREACH(var, col) BOOST_FOREACH(ZEN_FOREACH_PROCESS_AUTO(var, col), col)

namespace zen { 
}

#ifdef ZEN_FOREACH_TEST

ZEN_FOREACH_PROCESS_AUTO(const auto& x, range)
ZEN_FOREACH_PROCESS_AUTO(const int& x, range)
ZEN_FOREACH_PROCESS_AUTO(int x, range)
ZEN_FOREACH_PROCESS_AUTO(auto const & x, range)

ZEN_FOREACH(const auto& x, range)

#endif

#endif
