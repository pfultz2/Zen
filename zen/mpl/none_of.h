/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    none_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_MPL_NONE_OF_H
#define ZEN_GUARD_MPL_NONE_OF_H

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/begin_end.hpp>

namespace zen { namespace mpl {

template<class Sequence, class MF>
struct none_of
: boost::is_same<typename boost::mpl::find_if<Sequence, MF>::type, typename boost::mpl::end<Sequence>::type>
{};

}}

#endif
