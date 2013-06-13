/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    fused_for_each.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FUSED_FOR_EACH_H
#define ZEN_GUARD_ALGORITHM_FUSED_FOR_EACH_H

#include <zen/algorithm/for_each.h>
#include <zen/function/fuse.h>

namespace zen {

ZEN_FUNCTION_PIPE_OBJECT((fused_for_each)(auto r, f)
    (zen::for_each(r, zen::fuse(f)))
)

}

#endif
