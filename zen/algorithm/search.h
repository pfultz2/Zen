/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    search.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_SEARCH_H
#define ZEN_GUARD_ALGORITHM_SEARCH_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <zen/range/iterator_range.h>
#include <zen/algorithm/detail/default_equal.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <algorithm>

namespace zen { namespace detail {

template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
iterator_range<ForwardIt1> search(ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last, 
                        BinaryPredicate p)
{
    for (; ; ++first) 
    {
        ForwardIt1 it = first;
        for (ForwardIt2 s_it = s_first; ; ++it, ++s_it) 
        {
            if (s_it == s_last) 
            {
                return make_iterator_range(first, it);
            }
            if (it == last) 
            {
                return make_iterator_range(last, last);
            }
            if (!p(*it, *s_it)) 
            {
                break;
            }
        }
    }
}
}

ZEN_FUNCTION_PIPE_OBJECT((search)(auto r, auto s)
        if (is_range<r>, is_range<s>)
        (
            detail::search(boost::begin(r), boost::end(r), boost::begin(s), boost::end(s), detail::default_equal())
        )
        def(auto r, auto s, pred)
        if (is_range<r>, is_range<s>)
        (
            detail::search(boost::begin(r), boost::end(r), boost::begin(s), boost::end(s), pred)
        )
    )
}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <string>
#include <zen/algorithm/empty.h>

ZEN_TEST_CASE(search_test)
{
    std::string str = "why waste time learning, when ignorance is instantaneous?";
    std::string s1 = "learning";
    std::string s2 = "lemming";

    ZEN_TEST_CHECK(!zen::empty(zen::search(str, s1)));
    ZEN_TEST_CHECK(zen::empty(zen::search(str, s2)));

    ZEN_TEST_CHECK(!zen::empty(str | zen::search(s1)));
    ZEN_TEST_CHECK(zen::empty(str | zen::search(s2)));
}

#endif

#endif
