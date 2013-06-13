/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    zip.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_ZIP_H
#define ZEN_GUARD_ALGORITHM_ZIP_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <zen/typeof.h>
#include <zen/function/invoke.h>
#include <zen/range/iterator_range.h>

#include <boost/iterator/zip_iterator.hpp>
#include <boost/fusion/algorithm/transformation/zip.hpp>

namespace zen { 

namespace detail {
#if !defined(ZEN_NO_VARIADIC_TEMPLATES) && !defined(ZEN_NO_TRAILING_RETURN)
template<class T, int ...N>
auto make_boost_tuple_impl(T && t, seq<N...>) ZEN_RETURNS(boost::make_tuple(boost::fusion::at_c<N>(zen::forward<T>(t))...));

template<class F, class Sequence>
auto make_boost_tuple(Sequence && t) ZEN_RETURNS
(
    detail::make_boost_tuple_impl(std::forward<Sequence>(t), typename detail::sequence_gens<Sequence>::type() ) 
);

struct fusion_zip
{
    template<class... T>
    auto operator()(const T & ...x) ZEN_RETURNS(boost::fusion::zip(x...));
};

// template<class... Range>
// auto zip(Range && ...r) ZEN_RETURNS
// (
//     make_iterator_range
//     (
//         boost::make_zip_iterator(boost::make_tuple(boost::begin(r)...)),
//         boost::make_zip_iterator(boost::make_tuple(boost::end(r)...))
//     )
// );
#else

#endif

ZEN_FUNCTION_CLASS((begin_select)(auto r)(boost::begin(r)))
ZEN_FUNCTION_CLASS((end_select)(auto r)(boost::end(r)))

//ZEN_FUNCTION_CLASS((zip_impl)(t))

}



}

#endif
