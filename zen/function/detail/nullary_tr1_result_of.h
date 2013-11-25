/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    nullary_tr1_result_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_DETAIL_ZEN_NULLARY_TR1_RESULT_OF_H
#define ZEN_GUARD_DETAIL_ZEN_NULLARY_TR1_RESULT_OF_H

#include <zen/function/result_of.h>
#include <zen/pp.h>

// TR1 requires specialization for nullary functions
#ifdef BOOST_RESULT_OF_USE_TR1

#define ZEN_NULLARY_TR1_RESULT_OF_PARAMS(name, ...) \
namespace boost { \
template<> \
struct result_of<name __VA_ARGS__ ()> \
: name::template result<name __VA_ARGS__ ()> \
{}; \
 \
 template<> \
struct result_of<const name __VA_ARGS__ ()> \
: name::template result<name __VA_ARGS__ ()> \
{}; \
 \
template<> \
struct tr1_result_of<name __VA_ARGS__ ()> \
: name::template result<name __VA_ARGS__ ()> \
{}; \
\
template<> \
struct tr1_result_of<const name __VA_ARGS__ ()> \
: name::template result<name __VA_ARGS__ ()> \
{}; \
}


// TODO: Add template version for different template types
#define ZEN_NULLARY_TR1_RESULT_OF_N(n, name) ZEN_NULLARY_TR1_RESULT_OF_PARAMS(name, <ZEN_PP_PARAMS_Z(1, n, F)>)
#define ZEN_NULLARY_TR1_RESULT_OF(name) ZEN_NULLARY_TR1_RESULT_OF_PARAMS(name,)

#else
#define ZEN_NULLARY_TR1_RESULT_OF(name)
#define ZEN_NULLARY_TR1_RESULT_OF_N(n, name)
#endif


#endif
