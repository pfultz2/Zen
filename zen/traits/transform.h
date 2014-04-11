/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    transform.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TRAITS_TRANSFORM_H
#define ZEN_GUARD_TRAITS_TRANSFORM_H

namespace zen { 

template<class T>
using transform_trait = typename T::type;

// Short form
template<class T>
using _t = typename T::type;

}

#endif
