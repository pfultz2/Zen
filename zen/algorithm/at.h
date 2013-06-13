/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    at.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_AT_H
#define ZEN_GUARD_ALGORITHM_AT_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <zen/algorithm/empty.h>

#include <algorithm>

#include <zen/assert.h>

namespace zen { 

namespace detail {

template<class R, class I>
ZEN_FUNCTION_REQUIRES(has_range_traversal<R, boost::random_access_traversal_tag>)
(typename boost::range_iterator<R>::type)
iterator_at(R& r, I n)
{
    typename boost::range_iterator<const R>::type it;
    if (n < 0) it = boost::end(r);
    else it = boost::begin(r);
    return it += n;
}

}

ZEN_FUNCTION_PIPE_OBJECT((at)(r, n)
        if (has_range_traversal<r, boost::random_access_traversal_tag>)
        (
            ZEN_ASSERT_EXPR(!zen::empty(r), detail::iterator_at(r))
        )

    )


}

#endif
