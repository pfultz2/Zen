/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    print.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ZEN_PRINT_H
#define ZEN_GUARD_ZEN_PRINT_H

#include <zen/requires.h>
#include <zen/traits.h>
#include <sstream>

// TODO: Needs to be deprecated, and moved to the test namespace

namespace zen { namespace test { 

namespace print_detail {

ZEN_TRAIT(has_stream_out)
{
    template<class T, class U>
    auto requires(T&& x, U&& y) -> ZEN_VALID_EXPR(
        x << y
    );
};

}

template<class Stream, class T>
ZEN_FUNCTION_REQUIRES(print_detail::has_stream_out<Stream, T>())
(void) print(Stream& s, const T& x);

template<class Stream, class T>
ZEN_FUNCTION_REQUIRES(not print_detail::has_stream_out<Stream, T>())
(void) print(Stream& s, const T& x);


template<class Stream, class T>
ZEN_FUNCTION_REQUIRES(print_detail::has_stream_out<Stream, T>())
(void) print(Stream& s, const T& x)
{
    s << x;
}

template<class Stream, class T>
ZEN_FUNCTION_REQUIRES(not print_detail::has_stream_out<Stream, T>())
(void) print(Stream& s, const T& x)
{
    char sep = '{';
    for(auto&& y:x)
    {
        s << sep;
        print(s, y);
        sep = ',';
    }
    s << '}';
}

template<class T>
std::string to_string(const T& x)
{
    std::ostringstream ss;
    print(ss, x);
    return ss.str();
}

}}

#endif
