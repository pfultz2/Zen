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
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/fusion/sequence/comparison.hpp>

// TODO: Needs to be deprecated, and moved to the test namespace

namespace zen { namespace test { 

using boost::fusion::operator==;

namespace equals_detail {

ZEN_TRAIT(has_equals)
{
    template<class T, class U>
    auto requires(T&& x, U&& y) -> ZEN_VALID_EXPR(
        x == y
    );
};

}

template<class T, class U>
ZEN_FUNCTION_REQUIRES(equals_detail::has_equals<T, U>())
(bool) equals(const T& x, const U& y);

template<class T, class U>
ZEN_FUNCTION_REQUIRES(not equals_detail::has_equals<T, U>())
(bool) equals(const T& r1, const U& r2);


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
        return zen::test::equals(x, y);
    }
};

}

template<class T, class U>
ZEN_FUNCTION_REQUIRES(equals_detail::has_equals<T, U>())
(bool) equals(const T& x, const U& y)
{
    return x == y;
}

template<class T, class U>
ZEN_FUNCTION_REQUIRES(not equals_detail::has_equals<T, U>())
(bool) equals(const T& r1, const U& r2)
{
    return zen::test::equals_detail::equal(boost::begin(r1), boost::end(r1), boost::begin(r2), boost::end(r2), equals_detail::equals_predicate());
}

}}

#endif
