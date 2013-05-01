/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    utility.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_UTILITY_H
#define	ZEN_GUARD_UTILITY_H

//Thist declares a variable unused by the compiler
//Useful to suppress warnings
#ifdef __GNUC__
#define ZEN_UNUSED __attribute__((__unused__))
#else
#define ZEN_UNUSED
#endif

#endif	/* ZEN_GUARD_UTILITY_H */

