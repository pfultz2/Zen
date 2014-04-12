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

ZEN_TRAITS(is_iterator)
{
    template<class I>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::is_true<is_semi_regular<I>>(),
        zen::returns< _t<iterator_reference<I>> >(*i),
        zen::returns< _t<std::remove_reference<I>>& >(++i)
    );
}

ZEN_TRAITS(is_input_iterator)
{
    template<class I>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::is_true<is_iterator<I>>(),
        zen::is_true<is_equality_comparable<I>>(),
        zen::returns< _t<iterator_value<I>> >(*i),
        zen::returns< _t<iterator_value<I>> >(*i++),
        i++
    );
}

ZEN_TRAITS(is_output_iterator)
{
    template<class I, class T>
    auto requires(I&& i, T&& out) -> ZEN_VALID_EXPR(
        zen::is_true<is_iterator<I>>(),
        *i = out,
        *i++ = out,
        zen::returns< const _t<std::remove_reference<I>>& >(i++)
    );
}

ZEN_TRAITS(is_const_iterator)
{
    template<class I, class T>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::is_true<is_regular<I>>(),
        zen::is_true<is_input_iterator<I>>(),
        zen::is_true< std::is_convertible<_t<boost::iterator_traversal<I>>, boost::forward_traversal_tag> >(),
        zen::returns< _t<iterator_reference<I>> >(*i)
    );
}

ZEN_TRAITS(is_mutable_iterator)
{
    template<class I, class T>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::is_true<is_const_iterator<I>>(),
        zen::is_true< is_output_iterator<I, _t<iterator_value<I>>> >()
    );
}

ZEN_TRAITS(is_reversible_iterator)
{
    template<class I, class T>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::is_true<is_input_iterator<I>>(),
        zen::returns< _t<std::remove_reference<I>>& >(--i)
        i--
    );
}

ZEN_TRAITS(is_advanceable_iterator)
{
    template<class I, class T>
    auto requires(I&& i) -> ZEN_VALID_EXPR(
        zen::is_true<is_input_iterator<I>>(),
        zen::is_true<is_totally_ordered<I>>(),
        zen::returns< _t<iterator_reference<I>> >(i[1]),
        zen::returns< _t<std::remove_reference<I>>& >(i += 1),
        zen::returns< _t<std::remove_reference<I>>& >(i -= 1),
        zen::returns<I>(i + 1),
        zen::returns<I>(i - 1),
        zen::returns< _t<iterator_difference<I>> >(i - i)
    );
}


}

#endif