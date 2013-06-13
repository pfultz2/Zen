/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    reverse.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_REVERSE_H
#define ZEN_GUARD_ALGORITHM_REVERSE_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/iterator/reverse_iterator.hpp>
#include <zen/range/iterator_range.h>

#include <boost/fusion/algorithm/transformation/reverse.hpp>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((reverse)(auto r)
    if (has_range_traversal<r, boost::bidirectional_traversal_tag>)
    (
        make_iterator_range
        (
            boost::make_reverse_iterator(boost::end(r)),
            boost::make_reverse_iterator(boost::begin(r)) 
        )
    )
    else if (is_sequence<r>)
    (
        boost::fusion::reverse(r)
    )

    )

}

#endif
