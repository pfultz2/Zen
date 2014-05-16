/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    invoke.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_INVOKE_H
#define ZEN_GUARD_FUNCTION_INVOKE_H

// @begin
// invoke
// ======
// 
// Description
// -----------
// 
// Calls a function object with the arguments from a fusion sequence.
// 
// Synopsis
// --------
// 
//     template<class F, class Sequence>
//     typename invoke_result<F, Sequence>::type
//     invoke(F f, const Sequence& seq);
// 
// Example
// -------
// 
//     std::plus<int> add;
//     assert(invoke(add,boost::fusion::make_vector(1,1)) == 2);
// 
// @end

#include <zen/config.h>
#include <zen/returns.h>
#include <zen/traits/bare.h>
#include <zen/requires.h>
#include <zen/function/detail/gens.h>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <tuple>

namespace zen { 

//
// invoke
//
namespace detail {

template<class T>
struct is_native_tuple
: std::false_type
{};

template<class... Ts>
struct is_native_tuple<std::tuple<Ts...> >
: std::true_type
{};

template<class... Ts>
struct is_native_tuple<std::pair<Ts...> >
: std::true_type
{};

template<class S>
struct seq_size
: boost::mpl::if_<is_native_tuple<S>, 
    std::tuple_size<S>,
    boost::fusion::result_of::size<S>
>::type
{};

template<class T>
struct sequence_gens
: gens<detail::seq_size<bare_t<T>>::value> {};

template<class F, class T, int ...N, ZEN_REQUIRES(detail::is_native_tuple<bare_t<T>>())>
auto invoke_impl(F f, T && t, seq<N...>) ZEN_RETURNS
(
    f(ZEN_AUTO_FORWARD(std::get<N>(t))...)
);

template<class F, class T, int ...N, ZEN_REQUIRES(not detail::is_native_tuple<bare_t<T>>())>
auto invoke_impl(F f, const T & t, seq<N...>) ZEN_RETURNS
(
    f(boost::fusion::at_c<N>(t)...)
);

}

template<class F, class Sequence>
auto invoke(F f, Sequence && t) ZEN_RETURNS
(
    detail::invoke_impl(f, std::forward<Sequence>(t), typename detail::sequence_gens<Sequence>::type())
);


}

#endif
