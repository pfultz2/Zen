/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    at_c.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_AT_C_H
#define ZEN_GUARD_ALGORITHM_AT_C_H

#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <zen/algorithm/at.h>
#include <zen/function/builder.h>

namespace zen { 

namespace detail {

template<int N>
struct at_c_base
{
    ZEN_FUNCTION_CLASS((apply_base)(auto r) 
        if (is_sequence<r>)(boost::fusion::at_c<N>(r))
        else if (is_range<r>)(r | zen::at(N))
    );
    typedef pipable_adaptor<apply_base> apply;
};
    
}

template<int N, class S>
typename zen::result_of<typename detail::at_c_base<N>::apply(S)>::type
at_c(S& s)
{
    return typename detail::at_c_base<N>::apply()(s);
}

template<int N>
typename detail::at_c_base<N>::apply
at_c()
{
    return typename detail::at_c_base<N>::apply();
}

}



#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(at_c_test)
{
    boost::fusion::vector<int, int, int> v(1, 2, 3);
    ZEN_TEST_EQUAL(zen::at_c<1>(v), 2);
    ZEN_TEST_EQUAL(v | zen::at_c<1>(), 2);
}

#endif

#endif
