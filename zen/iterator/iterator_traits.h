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

namespace detail {

template<class Iterator>
struct iterator_traits
: std::iterator_traits<bare_t<Iterator>>
{};

template<class T>
struct iterator_traits<const T*>
: std::iterator_traits<const T*>
{};

}

ZEN_TRAIT(has_iterator_category)
{
    template<class I>
    auto requires(const I&) -> ZEN_VALID_EXPR(
        zen::has_type<typename I::iterator_category>(),
        zen::has_type<typename I::reference>(),
        zen::has_type<typename I::pointer>(),
        zen::has_type<typename I::value_type>(),
        zen::has_type<typename I::difference_type>()
    );
};

template<class T>
struct has_iterator_category<T*>
: std::true_type
{};

template<class T, class = ZEN_CLASS_REQUIRES(has_iterator_category<T>())>
struct iterator_category
{
    typedef typename detail::iterator_traits<T>::iterator_category type;
};

template<class T, class = ZEN_CLASS_REQUIRES(has_iterator_category<T>())>
struct iterator_reference
{
    typedef typename detail::iterator_traits<T>::reference type;
};

template<class T, class = ZEN_CLASS_REQUIRES(has_iterator_category<T>())>
struct iterator_pointer
{
    typedef typename detail::iterator_traits<T>::pointer type;
};

template<class T, class = ZEN_CLASS_REQUIRES(has_iterator_category<T>())>
struct iterator_value
{
    typedef typename detail::iterator_traits<T>::value_type type;
};

template<class T, class = ZEN_CLASS_REQUIRES(has_iterator_category<T>())>
struct iterator_difference
{
    typedef typename detail::iterator_traits<T>::difference_type type;
};

ZEN_TRAIT(is_iterator, 
    is_semi_regular<_>, has_iterator_category<_>)
{
    template<class I>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::returns< _t<iterator_reference<I>> >(*i),
        zen::returns< _t<std::remove_reference<I>>& >(++i)
    );
};

ZEN_TRAIT(is_input_iterator, 
    is_iterator<_>, is_equality_comparable<_>)
{
    template<class I>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::returns< _t<iterator_value<I>> >(*i),
        zen::returns< _t<iterator_value<I>> >(*i++),
        i++
    );
};

ZEN_TRAIT(is_output_iterator, 
    is_iterator<_1>)
{
    template<class I, class T>
    auto requires(I&& i, T&& out) -> ZEN_VALID_EXPR(
        *i = out,
        *i++ = out,
        zen::returns< const bare_t<I>& >(i++)
    );

    template<class I>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        this->requires(std::forward<I>(i), std::declval< _t<iterator_value<I>> >())
    );
};

ZEN_TRAIT(is_const_iterator,
    is_regular<_>, is_input_iterator<_>)
{
    template<class I>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::is_true< std::is_convertible<_t<boost::iterator_traversal<I>>, boost::forward_traversal_tag> >(),
        zen::returns< _t<iterator_reference<I>> >(*i)
    );
};

ZEN_TRAIT(is_mutable_iterator,
    is_const_iterator<_>, is_output_iterator<_>)
{
};

ZEN_TRAIT(is_reversible_iterator,
    is_input_iterator<_>)
{
    template<class I>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::returns< _t<std::remove_reference<I>>& >(--i),
        i--
    );
};

ZEN_TRAIT(is_advanceable_iterator,
    is_input_iterator<_>, is_totally_ordered<_>)
{
    template<class I>
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
#include <list>
#include <forward_list>
#include <boost/mpl/not.hpp>

ZEN_TRAIT_CHECK(zen::has_iterator_category<int*>);
ZEN_TRAIT_CHECK(zen::has_iterator_category<std::vector<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_iterator<std::vector<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_input_iterator<std::vector<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_output_iterator<std::vector<int>::iterator, int>);
ZEN_TRAIT_CHECK(zen::is_output_iterator<std::vector<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_const_iterator<std::vector<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_mutable_iterator<std::vector<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_reversible_iterator<std::vector<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_advanceable_iterator<std::vector<int>::iterator>);

ZEN_TRAIT_CHECK(zen::has_iterator_category<std::list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_iterator<std::list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_input_iterator<std::list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_output_iterator<std::list<int>::iterator, int>);
ZEN_TRAIT_CHECK(zen::is_output_iterator<std::list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_const_iterator<std::list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_mutable_iterator<std::list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_reversible_iterator<std::list<int>::iterator>);
ZEN_TRAIT_CHECK(boost::mpl::not_<zen::is_advanceable_iterator<std::list<int>::iterator>>);


ZEN_TRAIT_CHECK(zen::has_iterator_category<std::forward_list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_iterator<std::forward_list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_input_iterator<std::forward_list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_output_iterator<std::forward_list<int>::iterator, int>);
ZEN_TRAIT_CHECK(zen::is_output_iterator<std::forward_list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_const_iterator<std::forward_list<int>::iterator>);
ZEN_TRAIT_CHECK(zen::is_mutable_iterator<std::forward_list<int>::iterator>);
ZEN_TRAIT_CHECK(boost::mpl::not_<zen::is_reversible_iterator<std::forward_list<int>::iterator>>);
ZEN_TRAIT_CHECK(boost::mpl::not_<zen::is_advanceable_iterator<std::forward_list<int>::iterator>>);

// ZEN_TRAIT_CHECK(zen::is_iterator<std::vector<int>::iterator&>);
// ZEN_TRAIT_CHECK(zen::is_input_iterator<std::vector<int>::iterator&>);
// ZEN_TRAIT_CHECK(zen::is_output_iterator<std::vector<int>::iterator&, int>);
// ZEN_TRAIT_CHECK(zen::is_mutable_iterator<std::vector<int>::iterator&>);
// ZEN_TRAIT_CHECK(zen::is_reversible_iterator<std::vector<int>::iterator&>);
// ZEN_TRAIT_CHECK(zen::is_advanceable_iterator<std::vector<int>::iterator&>);

#endif

#endif