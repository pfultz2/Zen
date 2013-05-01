/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    debug.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ZEN_DEBUG_H
#define ZEN_GUARD_ZEN_DEBUG_H

#include <zen/traits.h>
#include <zen/requires.h>
#include <boost/lexical_cast.hpp>
#include <zen/foreach.h>

namespace zen { 

template<class T>
ZEN_FUNCTION_REQUIRES(exclude is_range<T>, exclude is_pair<T>)
(std::string) debug_string(const T& x)
{
    return boost::lexical_cast<std::string>(x);
}

template<class Range>
ZEN_FUNCTION_REQUIRES(is_range<Range>, exclude is_string<Range>)
(std::string) debug_string(const Range& r);

template<class Pair>
ZEN_FUNCTION_REQUIRES(is_pair<Pair>)
(std::string) debug_string(const Pair& p)
{
    return debug_string(p.first) + "=" + debug_string(p.second);
}

template<class Range>
ZEN_FUNCTION_REQUIRES(is_range<Range>, exclude is_string<Range>)
(std::string) debug_string(const Range& r)
{
    std::string out;
    std::string delim = "[";
    ZEN_FOREACH(const auto& x, r)
    {
        out += delim + debug_string(x);
    }
    out += "]";
    return out;
}

}

#endif
