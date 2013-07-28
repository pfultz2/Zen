/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    triple.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_DETAIL_TRIPLE_H
#define ZEN_GUARD_DETAIL_TRIPLE_H

struct triple
{
    typedef int result_type;

    int operator()(int t) const
    {
        return t * 3;
    };
};



#endif