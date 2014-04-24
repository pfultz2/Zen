/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    range_traits.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_TRAITS_H
#define ZEN_GUARD_RANGE_TRAITS_H

#include <zen/iterator/iterator_traits.h>
#include <zen/function/builder.h>
#include <boost/range/metafunctions.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace zen_detail_range_traits {

using std::begin;
using std::end;


template<class R>
decltype(auto) boost_begin(R&& r) { return boost::begin(r); }

template<class R>
decltype(auto) boost_end(R&& r) { return boost::end(r); }

template<class R>
struct boost_range_iterator
: boost::mpl::if_<std::is_const<R>, 
    boost::range_const_iterator<zen::_t<std::remove_reference<R>>>, 
    boost::range_mutable_iterator<zen::_t<std::remove_reference<R>>> 
>::type
{};

ZEN_TRAIT(is_boost_range)
{
    template<class R>
    auto requires(R&& r) -> ZEN_VALID_EXPR(
        zen::has_type<
            typename boost_range_iterator<R>::type, 
            zen::is_iterator<boost::mpl::_> >()
    );
};

ZEN_TRAIT(is_cpp_range)
{
    template<class R>
    auto requires(R&& r) -> ZEN_VALID_EXPR(
        zen::returns< zen::is_iterator<boost::mpl::_> >(begin(r)),
        zen::returns< zen::is_iterator<boost::mpl::_> >(end(r))
    );
};

template<class R>
decltype(auto) cpp_begin(R& r) { return begin(r); }

template<class R>
decltype(auto) cpp_end(R& r) { return end(r); }

template<class R>
struct cpp_range_iterator
{
    typedef decltype(begin(std::declval<typename std::remove_reference<R>::type&>())) type;
};

}
namespace zen {


template<class T>
struct is_range
: boost::mpl::or_<zen_detail_range_traits::is_boost_range<T>, zen_detail_range_traits::is_cpp_range<T>>
{};

template<class R, ZEN_REQUIRES(is_range<R>())>
struct range_iterator
: boost::mpl::eval_if<zen_detail_range_traits::is_cpp_range<R>, 
    zen_detail_range_traits::cpp_range_iterator<R>,
    zen_detail_range_traits::boost_range_iterator<R>>
{};

template<class R, ZEN_REQUIRES(is_range<R>())>
struct range_category
: iterator_category<_t<range_iterator<R>>>
{};

template<class R, ZEN_REQUIRES(is_range<R>())>
struct range_reference
: iterator_reference<_t<range_iterator<R>>>
{};

template<class R, ZEN_REQUIRES(is_range<R>())>
struct range_pointer
: iterator_pointer<_t<range_iterator<R>>>
{};

template<class R, ZEN_REQUIRES(is_range<R>())>
struct range_value
: iterator_value<_t<range_iterator<R>>>
{};

template<class R, ZEN_REQUIRES(is_range<R>())>
struct range_difference
: iterator_difference<_t<range_iterator<R>>>
{};

ZEN_FUNCTION_OBJECT((begin)(auto&& r)
        if (_p<zen_detail_range_traits::is_cpp_range>(r))(zen_detail_range_traits::cpp_begin(r))
        else if (_p<zen_detail_range_traits::is_boost_range>(r))(zen_detail_range_traits::boost_begin(r))
    )

ZEN_FUNCTION_OBJECT((end)(auto&& r)
        if (_p<zen_detail_range_traits::is_cpp_range>(r))(zen_detail_range_traits::cpp_end(r))
        else if (_p<zen_detail_range_traits::is_boost_range>(r))(zen_detail_range_traits::boost_end(r))
    )

}

#ifdef ZEN_TEST
#include <vector>
#include <zen/static_assert.h>

static_assert(zen_detail_range_traits::is_boost_range<std::vector<int>>(), "Vector should be a boost range");
static_assert(zen_detail_range_traits::is_cpp_range<std::vector<int>>(), "Vector should be a cpp range");
static_assert(zen::is_range<std::vector<int>>(), "Vector should be a range");

static_assert(not zen_detail_range_traits::is_boost_range<int>(), "Int should not be a boost range");
static_assert(not zen_detail_range_traits::is_cpp_range<int>(), "Int should not be a cpp range");
static_assert(not zen::is_range<int>(), "Int should not be a range");

// typedef decltype(zen::begin(std::vector<int>())) range_begin_test;
// typedef decltype(zen::end(std::vector<int>())) range_end_test;

ZEN_STATIC_ASSERT_SAME(typename zen_detail_range_traits::cpp_range_iterator<std::vector<int>>::type, std::vector<int>::iterator);
ZEN_STATIC_ASSERT_SAME(typename zen_detail_range_traits::boost_range_iterator<std::vector<int>>::type, std::vector<int>::iterator);
ZEN_STATIC_ASSERT_SAME(typename zen::range_iterator<std::vector<int>>::type, std::vector<int>::iterator);
#endif

#endif