/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    test.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_DETAIL_IS_ODD_H
#define ZEN_GUARD_DETAIL_IS_ODD_H

struct is_odd
{
    template<class X>
    struct result;
    
    template<class X, class T>
    struct result<X(T)>
    {
        typedef bool type;
    };
    template<typename T>
    bool operator()(T t) const
    {
        return t % 2;
    }
};



#endif
