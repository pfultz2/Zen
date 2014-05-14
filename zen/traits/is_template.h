/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    is_template.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_IS_TEMPLATE_H
#define ZEN_GUARD_IS_TEMPLATE_H

#include <type_traits>

namespace zen {

template<class T, template<class...> class Template>
struct is_template
: std::false_type
{};

template<template<class...> class Template, class... Ts>
struct is_template<Template<Ts...>, Template>
: std::true_type
{};

}

#endif