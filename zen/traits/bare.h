/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    bare.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TRAITS_BARE_H
#define ZEN_GUARD_TRAITS_BARE_H

namespace zen { 

template<class T>
struct bare 
: std::remove_cv<typename std::remove_reference<T>::type>
{};

template<class T>
using bare_t = typename bare<T>::type;

}

#endif
