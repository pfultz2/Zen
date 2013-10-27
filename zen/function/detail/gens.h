/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    gens.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_DETAIL_GENS_H
#define ZEN_GUARD_FUNCTION_DETAIL_GENS_H

namespace zen {
namespace detail {

template<int ...>
struct seq {};

template<int N, int ...S>
struct gens : gens<N-1, N-1, S...> {};

template<int ...S>
struct gens<0, S...> 
{
  typedef seq<S...> type;
};

template<int N>
typename gens<N>::type make_gens()
{
    return {};
}

}
}

#endif