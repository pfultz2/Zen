/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    placeholders.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_MPL_PLACEHOLDERS_H
#define ZEN_GUARD_MPL_PLACEHOLDERS_H

#include <functional>
#include <boost/mpl/placeholders.hpp>

// Unify placeholders

namespace zen { namespace mpl {
using namespace boost::mpl::placeholders;

struct local_placeholders
{
    typedef boost::mpl::arg<-1> _;
    typedef boost::mpl::arg<1>  _1;
    typedef boost::mpl::arg<2>  _2;
    typedef boost::mpl::arg<3>  _3;
    typedef boost::mpl::arg<4>  _4;
    typedef boost::mpl::arg<5>  _5;
    typedef boost::mpl::arg<6>  _6;
    typedef boost::mpl::arg<7>  _7;
    typedef boost::mpl::arg<8>  _8;
    typedef boost::mpl::arg<9>  _9;
};
}}

#endif
