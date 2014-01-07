/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    equals.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ZEN_EQUALS_H
#define ZEN_GUARD_ZEN_EQUALS_H

#include <zen/requires.h>
#include <zen/traits.h>

// TODO: Needs to be deprecated, and moved to the test namespace

namespace zen { 

template<class T, class U>
ZEN_FUNCTION_REQUIRES(not is_pair<T>() and not is_pair<U>() and not is_range<T>() and not is_range<U>())
(bool) equals(const T& x, const U& y);

template<class Range1, class Range2>
ZEN_FUNCTION_REQUIRES(is_range<Range1>() and is_range<Range2>())
(bool) equals(const Range1& r1, const Range2& r2);

template<class Pair1, class Pair2>
ZEN_FUNCTION_REQUIRES(is_pair<Pair1>() and is_pair<Pair2>() and not is_range<Pair1>() and not is_range<Pair2>())
(bool) equals(const Pair1& p1, const Pair2& p2);


namespace equals_detail {

template <class InputIterator1, class InputIterator2, class Predicate>
bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Predicate pred )
{
  while ((first1 != last1) && (first2 != last2)) 
  {
    if (!pred(*first1,*first2))
      return false;
    ++first1; ++first2;
  }
  return ((first1 == last1) && (first2 == last2));
}

struct equals_predicate
{
    template<class T>
    bool operator()(const T& x, const T& y) const
    {
        return zen::equals(x, y);
    }
};

}

template<class T, class U>
ZEN_FUNCTION_REQUIRES(not is_pair<T>() and not is_pair<U>() and not is_range<T>() and not is_range<U>())
(bool) equals(const T& x, const U& y)
{
    return x == y;
}

template<class Range1, class Range2>
ZEN_FUNCTION_REQUIRES(is_range<Range1>() and is_range<Range2>())
(bool) equals(const Range1& r1, const Range2& r2)
{
    return zen::equals_detail::equal(boost::begin(r1), boost::end(r1), boost::begin(r2), boost::end(r2), equals_detail::equals_predicate());
}

template<class Pair1, class Pair2>
ZEN_FUNCTION_REQUIRES(is_pair<Pair1>() and is_pair<Pair2>() and not is_range<Pair1>() and not is_range<Pair2>())
(bool) equals(const Pair1& p1, const Pair2& p2)
{
    return zen::equals(p2.first, p1.first) && zen::equals(p2.second, p2.second);
}

}

#endif
