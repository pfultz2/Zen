/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    back.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_BACK_H
#define ZEN_GUARD_ALGORITHM_BACK_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <zen/algorithm/empty.h>

#include <boost/fusion/sequence/intrinsic/back.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <algorithm>

#include <zen/assert.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((back)(auto r)
        if (is_sequence<r>, exclude boost::fusion::result_of::empty<r>)(boost::fusion::back(r))
        else if (has_range_traversal<r, boost::bidirectional_traversal_tag>, exclude is_sequence<r>)
        (
            ZEN_ASSERT_EXPR(!zen::empty(r), *(--boost::end(r)))
        ) 

    )  

}

#endif
