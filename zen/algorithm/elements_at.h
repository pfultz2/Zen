/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    element_at.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_ELEMENT_AT_H
#define ZEN_GUARD_ALGORITHM_ELEMENT_AT_H

#include <zen/algorithm/at.h>
#include <zen/algorithm/transform.h>

namespace zen { 


ZEN_FUNCTION_PIPE_OBJECT((elements_at)(auto&& r, auto n)
        if (_p<is_range>(r))
        (
            r | zen::transform([n](auto&& x) -> decltype(auto)
            { 
                return zen::at(x, n);
            })
        )
    )
}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(elemets_at_test)
{
    std::vector<int> v1 = {1, 1, 1};
    std::vector<std::vector<int> > v;
    v.push_back(v1);
    v.push_back(v1);
    v.push_back(v1);
    
    ZEN_TEST_EQUAL(v1, zen::elements_at(v, 1));
    ZEN_TEST_EQUAL(v1, v | zen::elements_at(1));
}

#endif

#endif
