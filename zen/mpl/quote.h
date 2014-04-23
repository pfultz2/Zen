/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    quote.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_MPL_QUOTE_H
#define ZEN_GUARD_MPL_QUOTE_H

namespace zen { namespace mpl {

template<class F>
struct quote;

template<template<class... Args> class F>
struct quote<F<Args>>
{
    template<class... Ts>
    struct apply
    : F<Ts...>
    {};
};

}}

#endif