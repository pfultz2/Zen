/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    search_n.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_SEARCH_N_H
#define ZEN_GUARD_ALGORITHM_SEARCH_N_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <zen/range/iterator_range.h>
#include <zen/algorithm/detail/default_equal.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <algorithm>

namespace zen { namespace detail {

template<class ForwardIt, class Size, class T, class BinaryPredicate>
iterator_range<ForwardIt> search_n(ForwardIt first, ForwardIt last,
                    Size count, const T& value, BinaryPredicate p)
{
    for(; first != last; ++first) 
    {
        if (!p(*first, value)) 
        {
            continue;
        }
 
        ForwardIt candidate = first;
        Size cur_count = 0;
 
        while (true) {

            ++cur_count;
            if (cur_count == count) 
            {
                // success
                return make_iterator_range(candidate, first+1);
            }
            ++first;
            if (first == last) 
            {
                // exhausted the list
                return make_iterator_range(last, last);
            }
            if (!p(*first, value)) 
            {
                // too few in a row
                break;
            }
        }
    }
    return make_iterator_range(last, last);
}
}

ZEN_FUNCTION_PIPE_OBJECT((search_n)(auto r, n, const x)
        if (is_range_of<r, x>)
        (
            detail::search_n(boost::begin(r), boost::end(r), n, x, detail::default_equal())
        )
        def(auto r, n, x, pred)
        if (is_range_of<r, x>)
        (
            detail::search_n(boost::begin(r), boost::end(r), n, x, pred)
        )
    )
}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <string>
#include <zen/algorithm/empty.h>

ZEN_TEST_CASE(search_n_test)
{
    std::string sequence = "1001010100010101001010101";
    std::string s = "000";

    ZEN_TEST_CHECK(zen::empty(zen::search_n(sequence, 4, '0')));
    ZEN_TEST_CHECK(!zen::empty(zen::search_n(sequence, 3, '0')));
    ZEN_TEST_EQUAL(zen::search_n(sequence, 3, '0'), s);

    ZEN_TEST_CHECK(zen::empty(sequence | zen::search_n(4, '0')));
    ZEN_TEST_CHECK(!zen::empty(sequence | zen::search_n(3, '0')));
    ZEN_TEST_EQUAL(sequence | zen::search_n(3, '0'), s);
}

#endif

#endif
