/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    element_at_c.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_ELEMENT_AT_C_H
#define ZEN_GUARD_ALGORITHM_ELEMENT_AT_C_H

#include <zen/function/builder.h>
#include <zen/algorithm/at_c.h>
#include <zen/algorithm/transform.h>

namespace zen { 

namespace detail {

template<int N>
struct elements_at_c_base
{
    ZEN_FUNCTION_CLASS((selector)(auto r) 
        if (is_range_or_sequence<r>)(zen::at_c<N>(r))
    );
    ZEN_FUNCTION_CLASS((apply_base)(auto r) 
    if (is_range_or_sequence<r>)
    (
        r | zen::transform(selector())
    ));
    typedef pipable_adaptor<apply_base> apply;
};
    
}

template<int N, class S>
typename zen::result_of<typename detail::elements_at_c_base<N>::apply(S)>::type
elements_at_c(S& s)
{
    return typename detail::elements_at_c_base<N>::apply()(s);
}

template<int N>
typename detail::elements_at_c_base<N>::apply
elements_at_c()
{
    return typename detail::elements_at_c_base<N>::apply();
}

}



#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(elments_at_c_test)
{
    boost::fusion::vector<int, int, int> inner_v(1, 2, 3);
    std::vector<boost::fusion::vector<int, int, int> > v1;
    v1.push_back(inner_v);
    v1.push_back(inner_v);
    v1.push_back(inner_v);

    std::vector<int> v2 = boost::assign::list_of(2)(2)(2);

    ZEN_TEST_EQUAL(zen::elements_at_c<1>(v1), v2);
    ZEN_TEST_EQUAL(v1 | zen::elements_at_c<1>(), v2);
}

#endif

#endif
