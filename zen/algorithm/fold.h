/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    fold.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FOLD_H
#define ZEN_GUARD_ALGORITHM_FOLD_H


#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <numeric>

namespace zen { 

// TODO: fold without an initial value
ZEN_FUNCTION_PIPE_OBJECT((fold)(auto r, const init, f)
        if(is_range<r>)(std::accumulate(boost::begin(r), boost::end(r), init, f))
        else if(is_sequence<r>)(boost::fusion::fold(r, init, f))
        def(auto r, f)
        if (is_range<r>)(std::accumulate(++boost::begin(r), boost::end(r), *boost::begin(r), f))
    )

}

#endif
