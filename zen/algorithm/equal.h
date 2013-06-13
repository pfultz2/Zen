/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    equal.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_EQUAL_H
#define ZEN_GUARD_ALGORITHM_EQUAL_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <zen/algorithm/count.h>

#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/equal_to.hpp>
#include <algorithm>

namespace zen { 

namespace detail {

template<class X, class Y, class Enable = void>
struct sequence_size_equal
: boost::mpl::bool_<false>
{};

template<class X, class Y>
struct sequence_size_equal<X, Y, ZEN_CLASS_REQUIRES(is_sequence<X>, is_sequence<Y>)>
: boost::mpl::equal_to<typename boost::fusion::result_of::size<X>::type, typename boost::fusion::result_of::size<Y>::type >
{};

}

ZEN_FUNCTION_PIPE_OBJECT((equal)(const x, const y)
        if (detail::sequence_size_equal<x, y>)
        (
            boost::fusion::equal_to(x, y)
        )
        else if (is_sequence<x>, is_sequence<y>)
        (
            false
        )
        else if (is_range<x>, is_range<y>)
        (
            (zen::count(x) == zen::count(y)) and
            std::equal(boost::begin(x), boost::end(x), boost::begin(y))
        )
    )

}

#endif
