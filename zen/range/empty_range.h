/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    empty_range.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_EMPTY_RANGE_H
#define ZEN_GUARD_RANGE_EMPTY_RANGE_H

#include <zen/range/iterator_range.h>

namespace zen {

template<class Value>
struct empty_range
: iterator_range<Value *>
{
    typedef iterator_range<Value *> base;

    empty_range() : base(0,0)
    {}
};

}

#endif
