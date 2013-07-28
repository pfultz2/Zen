/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    triple.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_DETAIL_INCREMENT_H
#define ZEN_GUARD_DETAIL_INCREMENT_H

struct increment
{
    template<typename T>
    void operator()(T& t) const
    {
        ++t;
    }

    template<typename T, typename U>
    void operator()(const T&, U& u) const
    {
        ++u;
    }
};



#endif