/*=============================================================================
    Copyright (c) 2013 Paul Fultz II
    tuple_reference.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_DETAIL_TUPLE_REFERENCE_H
#define ZEN_GUARD_DETAIL_TUPLE_REFERENCE_H

#include <zen/static_assert.h>


namespace zen{
namespace detail {

// This is used to avoid rvalue references in fusion sequences, 
// since they don't work right now
template<class T>
struct tuple_reference
{
    typedef T type;
};
#ifndef ZEN_NO_RVALUE_REFS
template<class T>
struct tuple_reference<T&&>
: tuple_reference<T>
{};
#endif
}}

#endif