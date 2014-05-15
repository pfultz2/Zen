/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    find.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FIND_H
#define ZEN_GUARD_ALGORITHM_FIND_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>
#include <zen/range/iterator_range.h>
#include <zen/algorithm/detail/make_find_range.h>

#include <algorithm>


namespace zen {

ZEN_TRAIT(has_iterator_find, is_range<_1>)
{
    template<class R, class T>
    auto requires(R&& r, T&& x) -> ZEN_VALID_EXPR(
        zen::returns< _t<range_iterator<R>> >(r.find(std::forward<T>(x)))
    );
};

ZEN_TRAIT(has_index_find, is_advanceable_range<_1>)
{
    template<class R, class T>
    auto requires(R&& r, T&& x) -> ZEN_VALID_EXPR(
        zen::returns< std::size_t >(r.find(std::forward<T>(x)))
    );
};

namespace detail {

template<class Range, class Index>
auto map_index_to_iterator(Range&& r, const Index i)
{
    typedef bare_t<Range> range;
    if (i == range::npos) return zen::end(r);
    else return zen::begin(r) + i;
}

template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
auto search(ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last, 
                        BinaryPredicate p)
{
    for (;;++first) 
    {
        ForwardIt1 it = first;
        for (ForwardIt2 s_it = s_first; ; ++it, ++s_it) 
        {
            if (s_it == s_last) return zen::make_iterator_range(first, it);
            if (it == last) return zen::make_iterator_range(last, last);
            if (!p(*it, *s_it)) break;
        }
    }
}

template<class ForwardIt1, class ForwardIt2>
auto search(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last)
{
    return detail::search(first, last, s_first, s_last, [](const auto& x, const auto& y) { return x == y; });
}

}

// TODO: Add find for fusion sequences
// TODO: Add overload for binary predicate
// TODO: Add checks for binary predicate
ZEN_FUNCTION_PIPE_OBJECT((find)(auto&& r, const auto& x)
        if (_p<has_iterator_find>(r, x))(detail::make_find_range(r, r.find(x)))
        else if (_p<has_index_find>(r, x))(detail::make_find_range(r, detail::map_index_to_iterator(r, r.find(x))))
        else if (_p<is_sub_range>(r, x))(detail::search(zen::begin(r), zen::end(r), zen::begin(x), zen::end(x)))
        else if (_p<is_range>(r))(detail::make_find_range(r, std::find(zen::begin(r), zen::end(r), x)))
        def(auto&& r, const auto& x, auto pred)
        if (_p<is_sub_range>(r, x))(detail::search(zen::begin(r), zen::end(r), zen::begin(x), zen::end(x), pred))
        else if (_p<is_range>(r))
        (
            detail::make_find_range(r, std::find_if(zen::begin(r), zen::end(r), [&x, pred](const auto& y) { return pred(x, y); }))
        )
    )   

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <map>


ZEN_TEST_CASE(find_test)
{
    std::vector<int> v = {0,1,2,3,4};
    std::vector<int> sv = {1,2,3};
    std::map<int, int> m = { {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6} };
    
    ZEN_TEST_EQUAL(2, *(v | zen::find(2)).begin());
    ZEN_TEST_EQUAL(3, (m | zen::find(2)).begin()->second);
    ZEN_TEST_EQUAL('H', *(std::string("Hello World") | zen::find("Hello")).begin());
    
    ZEN_TEST_CHECK(zen::end(v) == (v | zen::find(5)).begin());
    ZEN_TEST_CHECK(zen::end(m) == (m | zen::find(6)).begin());

    ZEN_TEST_EQUAL(sv, zen::find(v, sv));
    
}

#endif


#endif
