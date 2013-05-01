/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    placeholders.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_PLACEHOLDERS_H
#define ZEN_GUARD_FUNCTION_PLACEHOLDERS_H

#include <boost/phoenix/core/argument.hpp>

namespace zen { namespace ph {

using namespace boost::phoenix::placeholders;

}}

#ifndef ZEN_MAKE_PHOENIX_PLACEHOLDERS_STD
#define ZEN_MAKE_PHOENIX_PLACEHOLDERS_STD 0
#endif

#if ZEN_MAKE_PHOENIX_PLACEHOLDERS_STD
#include <functional>
#include <zen/pp.h>
namespace std {
#define ZEN_PLACEHOLDERS_STD_TRAIT(z, n, data) \
template<> \
struct is_placeholder<zen::ph:: _##n> \
: std::integral_constant<int, n> {};
BOOST_PP_REPEAT_FROM_TO_1(1, BOOST_PHOENIX_ARG_LIMIT, ZEN_PLACEHOLDERS_STD_TRAIT, ~)
}


#endif


#endif
