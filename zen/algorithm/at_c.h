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

ZEN_FUNCTION_PIPE_OBJECT((at_c_impl)(auto&& r, auto n) 
        if (_p<boost::fusion::traits::is_sequence>(r))(boost::fusion::at_c<n>(r))
        else if (_p<is_range>(r))(r | zen::at(n))
    );
    
}

template<int N, class... X>
auto at_c(X&&... x) ZEN_RETURNS
(
    detail::at_c_impl(std::forward<X>(x)..., std::integral_constant<int, N>())
);

}



#ifdef ZEN_TEST
#include <zen/test.h>
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
