/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    traits.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ZEN_TRAITS_H
#define ZEN_GUARD_ZEN_TRAITS_H

#include <boost/range/iterator.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/has_range_iterator.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <zen/static_assert.h>
#include <zen/requires.h>

namespace zen { 

BOOST_MPL_HAS_XXX_TRAIT_DEF(type)

using boost::fusion::traits::is_sequence;

namespace detail {

template<class T1 = void, class T2 = void, class T3 = void, class T4 = void, class T5 = void>
struct holder
{
    typedef void type;
};

}

template<class T, class X = void>
struct is_iterator 
: boost::mpl::bool_<false>
{};

template<class T>
struct is_iterator<T*>
: boost::mpl::bool_<true>
{};

template<class Iterator>
struct is_iterator<Iterator, typename zen::detail::holder
<
    typename Iterator::iterator_category, 
    typename Iterator::reference, 
    typename Iterator::pointer, 
    typename Iterator::value_type, 
    typename Iterator::difference_type 
>::type >
: boost::mpl::bool_<true>
{};

template<class T, class Traversal, class Enable = void>
struct has_iterator_traversal 
: boost::mpl::bool_<false>
{};

template<class T, class Traversal>
struct has_iterator_traversal<T, Traversal, ZEN_CLASS_REQUIRES(is_iterator<T>)> : 
boost::is_convertible<typename boost::iterator_traversal<T>::type, Traversal>::type
{};



template<class T>
struct is_range : boost::mpl::if_
< 
    boost::is_const<T>,
    boost::has_range_const_iterator<typename boost::remove_const<T>::type>,
    boost::mpl::and_<boost::has_range_iterator<T>, boost::has_range_const_iterator<T> > 
>::type
{};

template<class T, class U>
struct is_range<std::pair<T, U> > 
: boost::mpl::and_<is_iterator<T>, is_iterator<U> >::type
{};

template<class Range, class T, class Enable = void>
struct is_range_of 
: boost::mpl::bool_<false>
{};

template<class Range, class T>
struct is_range_of<Range, T, ZEN_CLASS_REQUIRES(is_range<Range>)> 
: boost::is_convertible<T, typename boost::range_value<Range>::type>
{};

template<class Range1, class Range2, class Enable = void>
struct is_sub_range
: boost::mpl::bool_<false>
{};

template<class Range, class SubRange>
struct is_sub_range<Range, SubRange, ZEN_CLASS_REQUIRES(is_range<Range>, is_range<SubRange>)>
: boost::is_convertible<typename boost::range_value<SubRange>::type, typename boost::range_value<Range>::type>
{};

template<class T, class Traversal, class Enable = void>
struct has_range_traversal 
: boost::mpl::bool_<false>
{};

template<class T, class Traversal>
struct has_range_traversal<T, Traversal, ZEN_CLASS_REQUIRES(is_range<T>)> : 
boost::is_convertible<typename boost::iterator_traversal<typename boost::range_iterator<T>::type>::type, Traversal>::type
{};


template<class T>
struct is_pair 
: boost::mpl::bool_<false>
{};

template<class K, class V>
struct is_pair<std::pair<K, V> > 
: boost::mpl::bool_<true>
{};

template<class T>
struct is_string 
: boost::mpl::bool_<false>
{};

template<class C, class T, class A>
struct is_string<std::basic_string<C, T, A> >
: boost::mpl::bool_<true>
{};

template<class T, class Enable = void>
struct is_map_range 
: boost::mpl::bool_<false>
{};

template<class T>
struct is_map_range<T, ZEN_CLASS_REQUIRES(is_range<T>)> 
: is_pair<typename boost::range_value<T>::type >
{};

template<class T>
struct is_range_or_sequence
: boost::mpl::or_<is_range<T>, is_sequence<T> >
{};


template<class T>
struct purify
: boost::remove_cv<typename boost::decay<T>::type>
{};

}

#ifndef ZEN_TEST
#include <map>
#include <vector>
#include <list>
static_assert(zen::is_range<int>::value == false, "Error");
static_assert(zen::is_range<std::vector<int> >::value, "Error");
static_assert(zen::is_range<const std::vector<int> >::value, "Error");
static_assert((zen::is_range<std::pair<int, int> >::value == false), "Error");
static_assert((zen::is_range<std::pair<std::vector<int>::iterator, std::vector<int>::iterator> >::value), "Error");
static_assert((zen::is_range<std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator> >::value), "Error");
static_assert((zen::has_range_traversal<std::vector<int>, boost::random_access_traversal_tag>::value), "Error");
static_assert((zen::has_range_traversal<std::vector<int>, boost::bidirectional_traversal_tag>::value), "Error");
static_assert((zen::has_range_traversal<std::list<int>, boost::forward_traversal_tag>::value), "Error");
static_assert((not zen::has_range_traversal<std::list<int>, boost::random_access_traversal_tag>::value), "Error");
#endif

#endif
