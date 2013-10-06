/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    to_basic_string.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_TO_BASIC_STRING_H
#define ZEN_GUARD_ALGORITHM_TO_BASIC_STRING_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <zen/function/implicit.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace zen { namespace detail {

template<class T>
struct to_basic_string_f;

template<class Char, class Traits, class Allocator>
struct to_basic_string_f<std::basic_string<Char, Traits, Allocator> >
{
    template<class X>
    struct result;

    template<class X, class Range>
    struct result<X(Range)>
    {
        typedef std::basic_string<Char, Traits, Allocator> type;
    };

    template<class Range>
    std::basic_string<Char, Traits, Allocator> operator()(const Range& r) const
    {
        return std::basic_string<Char, Traits, Allocator>(boost::begin(r), boost::end(r));
    }
};
}

ZEN_FUNCTION_PIPE_OBJECT((to_basic_string)(auto r)
        if (is_range<r>)(implicit<detail::to_basic_string_f>()(r))
    )
}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <list>

ZEN_TEST_CASE(to_basic_string_test)
{
    std::vector<char> v = boost::assign::list_of('h')('e')('l')('l')('o');
    std::string s = v | zen::to_basic_string;
    
    ZEN_TEST_EQUAL(v, s);
}

#endif

#endif
