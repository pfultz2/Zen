/*=============================================================================
    Copyright (c) 2012 Paul Fultz II, Neil Groves
    equal.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_EQUAL_H
#define ZEN_GUARD_ALGORITHM_EQUAL_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <zen/algorithm/count.h>
#include <zen/algorithm/detail/default_equal.h>
#include <zen/function/partial.h>

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
                        BinaryPredicate                      pred,
                        IteratorCategoryTag1,
                        IteratorCategoryTag2 )
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
inline bool equal_impl( RandomAccessTraversalReadableIterator1 first1,
                        RandomAccessTraversalReadableIterator1 last1,
                        RandomAccessTraversalReadableIterator2 first2,
                        RandomAccessTraversalReadableIterator2 last2,
                        BinaryPredicate                        pred )
{
    return ((last1 - first1) == (last2 - first2))
        && std::equal(first1, last1, first2, pred);
}

template< class SinglePassTraversalReadableIterator1,
          class SinglePassTraversalReadableIterator2 >
inline bool range_equal( SinglePassTraversalReadableIterator1 first1,
                   SinglePassTraversalReadableIterator1 last1,
                   SinglePassTraversalReadableIterator2 first2,
                   SinglePassTraversalReadableIterator2 last2 )
{
    BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator1 >::iterator_category tag1;
    BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator2 >::iterator_category tag2;

    return equal_impl(first1, last1, first2, last2, tag1, tag2);
}

template< class SinglePassTraversalReadableIterator1,
          class SinglePassTraversalReadableIterator2,
          class BinaryPredicate >
inline bool range_equal( SinglePassTraversalReadableIterator1 first1,
                   SinglePassTraversalReadableIterator1 last1,
                   SinglePassTraversalReadableIterator2 first2,
                   SinglePassTraversalReadableIterator2 last2,
                   BinaryPredicate                      pred )
{
    BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator1 >::iterator_category tag1;
    BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator2 >::iterator_category tag2;

    return equal_impl(first1, last1, first2, last2, pred, tag1, tag2);
}

template<class X, class Y, class Enable = void>
struct sequence_size_equal
: boost::mpl::bool_<false>
{};

template<class X, class Y>
struct sequence_size_equal<X, Y, ZEN_CLASS_REQUIRES(is_sequence<X>, is_sequence<Y>)>
: boost::mpl::equal_to<typename boost::fusion::result_of::size<X>::type, typename boost::fusion::result_of::size<Y>::type >
{};

ZEN_FUNCTION_CLASS((fusion_equal_fold)(pred, const b, const seq)
    (
        b and pred(boost::fusion::at_c<0>(seq), boost::fusion::at_c<1>(seq))
    ));

ZEN_FUNCTION_OBJECT((equal)(const x, const y, pred)
        if (is_range<x>, is_range<y>)
        (
            range_equal(boost::begin(x), boost::end(x), boost::begin(y), boost::end(y), pred)
        )
        else if (detail::sequence_size_equal<x, y>)
        (
            boost::fusion::fold(boost::fusion::zip(x, y), true, partial(fusion_equal_fold())(pred))
        )
        else if (is_sequence<x>, is_sequence<y>)
        (
            false
        ) 
    )

}

ZEN_FUNCTION_PIPE_OBJECT((equal)(const x, const y, pred)
        if (is_range_or_sequence<x>, is_range_or_sequence<y>)
        (
            detail::equal(x, y, pred)
        )
        def(const x, const y)
        if (is_range_or_sequence<x>, is_range_or_sequence<y>)
        (
            detail::equal(x, y, detail::default_equal())
        )
    )

}

#endif
