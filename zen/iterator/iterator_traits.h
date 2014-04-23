/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    iterator_traits.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ITERATOR_ITERATOR_TRAITS_H
#define ZEN_GUARD_ITERATOR_ITERATOR_TRAITS_H

#include <zen/traits/builder.h>
#include <zen/traits/is_regular.h>
#include <zen/traits/is_equality_comparable.h>
#include <zen/traits/is_totally_ordered.h>
#include <zen/requires.h>
#include <boost/iterator/iterator_categories.hpp>
#include <iterator>

namespace zen {

template<class T, class X = void>
struct has_iterator_category 
: std::false_type
{};

template<class T>
struct has_iterator_category<T*>
: std::true_type
{};

template<class Iterator>
struct has_iterator_category<Iterator, typename zen::traits_detail::holder
<
    typename Iterator::iterator_category, 
    typename Iterator::reference, 
    typename Iterator::pointer, 
    typename Iterator::value_type, 
    typename Iterator::difference_type 
>::type >
: std::true_type
{};

template<class T, class = ZEN_CLASS_REQUIRES(has_iterator_category<T>())>
struct iterator_category
{
    typedef typename std::remove_reference<T>::type iterator_type;
    typedef typename std::iterator_traits<iterator_type>::iterator_category type;
};

template<class T, class = ZEN_CLASS_REQUIRES(has_iterator_category<T>())>
struct iterator_reference
{
    typedef typename std::remove_reference<T>::type iterator_type;
    typedef typename std::iterator_traits<iterator_type>::reference type;
};

template<class T, class = ZEN_CLASS_REQUIRES(has_iterator_category<T>())>
struct iterator_pointer
{
    typedef typename std::remove_reference<T>::type iterator_type;
    typedef typename std::iterator_traits<iterator_type>::pointer type;
};

template<class T, class = ZEN_CLASS_REQUIRES(has_iterator_category<T>())>
struct iterator_value
{
    typedef typename std::remove_reference<T>::type iterator_type;
    typedef typename std::iterator_traits<iterator_type>::value_type type;
};

template<class T, class = ZEN_CLASS_REQUIRES(has_iterator_category<T>())>
struct iterator_difference
{
    typedef typename std::remove_reference<T>::type iterator_type;
    typedef typename std::iterator_traits<iterator_type>::difference_type type;
};

ZEN_TRAIT(is_iterator, 
    is_semi_regular<boost::mpl::_>)
{
    template<class I>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::returns< _t<iterator_reference<I>> >(*i),
        zen::returns< _t<std::remove_reference<I>>& >(++i)
    );
};

ZEN_TRAIT(is_input_iterator, 
    is_iterator<boost::mpl::_>, is_equality_comparable<boost::mpl::_>)
{
    template<class I>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::returns< _t<iterator_value<I>> >(*i),
        zen::returns< _t<iterator_value<I>> >(*i++),
        i++
    );
};

ZEN_TRAIT(is_output_iterator, 
    is_iterator<boost::mpl::_1>)
{
    template<class I, class T>
    auto requires(I&& i, T&& out) -> ZEN_VALID_EXPR(
        zen::is_true<is_iterator<I>>(),
        *i = out,
        *i++ = out,
        zen::returns< const _t<std::remove_reference<I>>& >(i++)
    );
};

ZEN_TRAIT(is_const_iterator,
    is_regular<boost::mpl::_>, is_input_iterator<boost::mpl::_>)
{
    template<class I, class T>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::is_true< std::is_convertible<_t<boost::iterator_traversal<I>>, boost::forward_traversal_tag> >(),
        zen::returns< _t<iterator_reference<I>> >(*i)
    );
};

ZEN_TRAIT(is_mutable_iterator,
    is_const_iterator<boost::mpl::_>)
{
    template<class I, class T>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::is_true<is_const_iterator<I>>(),
        zen::is_true< is_output_iterator<I, _t<iterator_value<I>>> >()
    );
};

ZEN_TRAIT(is_reversible_iterator,
    is_input_iterator<boost::mpl::_>)
{
    template<class I, class T>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::returns< _t<std::remove_reference<I>>& >(--i),
        i--
    );
};

ZEN_TRAIT(is_advanceable_iterator,
    is_input_iterator<boost::mpl::_>, is_totally_ordered<boost::mpl::_>)
{
    template<class I, class T>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::returns< _t<iterator_reference<I>> >(i[1]),
        zen::returns< _t<std::remove_reference<I>>& >(i += 1),
        zen::returns< _t<std::remove_reference<I>>& >(i -= 1),
        zen::returns<I>(i + 1),
        zen::returns<I>(i - 1),
        zen::returns< _t<iterator_difference<I>> >(i - i)
    );
};


}


#ifdef ZEN_TEST
#include <zen/traits/trait_check.h>
#include <vector>

ZEN_TRAIT_CHECK(zen::is_iterator<std::vector<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_input_iterator<std::vector<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_output_iterator<std::vector<int>::iterator, int>);
// ZEN_TRAIT_CHECK(zen::is_mutable_iterator<std::vector<int>::iterator>);
// ZEN_TRAIT_CHECK(zen::is_reversible_iterator<std::vector<int>::iterator>);
// ZEN_TRAIT_CHECK(zen::is_advanceable_iterator<std::vector<int>::iterator>);

// ZEN_TRAIT_CHECK(zen::is_iterator<std::vector<int>::iterator&>);
// ZEN_TRAIT_CHECK(zen::is_input_iterator<std::vector<int>::iterator&>);
// ZEN_TRAIT_CHECK(zen::is_output_iterator<std::vector<int>::iterator&, int>);
// ZEN_TRAIT_CHECK(zen::is_mutable_iterator<std::vector<int>::iterator&>);
// ZEN_TRAIT_CHECK(zen::is_reversible_iterator<std::vector<int>::iterator&>);
// ZEN_TRAIT_CHECK(zen::is_advanceable_iterator<std::vector<int>::iterator&>);

#endif

#endif