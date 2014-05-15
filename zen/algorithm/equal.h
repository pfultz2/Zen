/*=============================================================================
    Copyright (c) 2012 Paul Fultz II, Neil Groves
    equal.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_EQUAL_H
#define ZEN_GUARD_ALGORITHM_EQUAL_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>

#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/fusion/algorithm/transformation/zip.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/equal_to.hpp>
#include <algorithm>

namespace zen { 

namespace detail {

// An implementation of equality comparison that is optimized for iterator
// traversal categories less than RandomAccessTraversal. From Neil Groves.
template< class SinglePassTraversalReadableIterator1,
          class SinglePassTraversalReadableIterator2,
          class IteratorCategoryTag1,
          class IteratorCategoryTag2,
          class BinaryPredicate >
inline bool equal_impl( SinglePassTraversalReadableIterator1 first1,
                        SinglePassTraversalReadableIterator1 last1,
                        SinglePassTraversalReadableIterator2 first2,
                        SinglePassTraversalReadableIterator2 last2,
                        BinaryPredicate                      pred)
{
    while (true)
    {
        // If we have reached the end of the left range then this is
        // the end of the loop. They are equal if and only if we have
        // simultaneously reached the end of the right range.
        if (first1 == last1)
            return first2 == last2;

        // If we have reached the end of the right range at this line
        // it indicates that the right range is shorter than the left
        // and hence the result is false.
        if (first2 == last2)
            return false;

        // continue looping if and only if the values are equal
        if (!pred(*first1, *first2))
            break;

        ++first1;
        ++first2;
    }

    // Reaching this line in the algorithm indicates that a value
    // inequality has been detected.
    return false;
}

// An implementation of equality comparison that is optimized for
// random access iterators.
template< class RandomAccessTraversalReadableIterator1,
          class RandomAccessTraversalReadableIterator2,
          class BinaryPredicate >
inline bool equal_advance_impl( RandomAccessTraversalReadableIterator1 first1,
                        RandomAccessTraversalReadableIterator1 last1,
                        RandomAccessTraversalReadableIterator2 first2,
                        RandomAccessTraversalReadableIterator2 last2,
                        BinaryPredicate                        pred )
{
    return ((last1 - first1) == (last2 - first2))
        && std::equal(first1, last1, first2, pred);
}

ZEN_FUNCTION_OBJECT((range_equal)(auto first1, auto last1, auto first2, auto last2, auto pred)
        if (_p<is_advanceable_iterator>(first1) and _p<is_advanceable_iterator>(first2))
        (equal_advance_impl(first1, last1, first2, last2, pred))
        else
        (equal_impl(first1, last1, first2, last2, pred))
    )

template<class X, class Y, class Enable = void>
struct sequence_size_equal
: boost::mpl::bool_<false>
{};

template<class X, class Y>
struct sequence_size_equal<X, Y, ZEN_CLASS_REQUIRES(boost::fusion::traits::is_sequence<X>() and boost::fusion::traits::is_sequence<Y>())>
: boost::mpl::equal_to<typename boost::fusion::result_of::size<X>::type, typename boost::fusion::result_of::size<Y>::type >
{};


ZEN_FUNCTION_OBJECT((equal)(const auto& x, const auto& y, auto pred)
        if (_p<is_range>(x) and _p<is_range>(y))
        (
            range_equal(zen::begin(x), zen::end(x), zen::begin(y), zen::end(y), pred)
        )
        else if (_p<detail::sequence_size_equal>(x, y))
        (
            boost::fusion::fold(boost::fusion::zip(x, y), true, [pred](const auto& b, const auto& seq)
            {
                return b and pred(boost::fusion::at_c<0>(seq), boost::fusion::at_c<1>(seq));
            })
        )
        else if (_p<boost::fusion::traits::is_sequence>(x) and _p<boost::fusion::traits::is_sequence>(y))
        (
            false
        ) 
    )

}

ZEN_FUNCTION_PIPE_OBJECT((equal)(const auto& x, const auto& y, auto pred)
        if ((_p<is_range>(x) and _p<is_range>(y)) or (_p<boost::fusion::traits::is_sequence>(x) and _p<boost::fusion::traits::is_sequence>(y)))
        (
            detail::equal(x, y, pred)
        )
        def(const auto& x, const auto& y)
        if ((_p<is_range>(x) and _p<is_range>(y)) or (_p<boost::fusion::traits::is_sequence>(x) and _p<boost::fusion::traits::is_sequence>(y)))
        (
            detail::equal(x, y, [](auto&& a, auto&& b) { return a == b; })
        )
    )

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(equal_test)
{
    std::vector<int> v1 = {1, 1, 1};
    std::vector<int> v2 = {1, 1, 1};
    std::vector<int> v3 = {1, 1, 1, 3};
    
    ZEN_TEST_CHECK(zen::equal(v1, v2));
    ZEN_TEST_CHECK(not zen::equal(v1, v3));
    
    boost::fusion::vector<int, int, int> fv1(1, 2, 3);
    boost::fusion::vector<int, int, int> fv2(1, 2, 3);
    boost::fusion::vector<int, int, int, int> fv3(1, 2, 3, 4);
    boost::fusion::vector<int, int, int> fv4(1, 2, 4);

    ZEN_TEST_CHECK(zen::equal(fv1, fv2));
    ZEN_TEST_CHECK(not zen::equal(fv1, fv3));
    ZEN_TEST_CHECK(not zen::equal(fv1, fv4));
}

#endif

#endif
