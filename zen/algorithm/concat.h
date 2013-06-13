/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    concat.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_CONCAT_H
#define ZEN_GUARD_ALGORITHM_CONCAT_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <zen/algorithm/mbind.h>
#include <algorithm>

#include <boost/bind.hpp>
#include <functional>

namespace zen { 

namespace detail {

ZEN_FUNCTION_CLASS((concat_identity)(x)(x))

}

ZEN_FUNCTION_PIPE_OBJECT((concat)(r)
    if (is_range<r>)(mbind(r, detail::concat_identity()))

)

}

#endif
