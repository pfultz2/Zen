/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    take_while.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_TAKE_WHILE_H
#define ZEN_GUARD_ALGORITHM_TAKE_WHILE_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <zen/algorithm/find_if.h>
#include <zen/range/iterator_range.h>

#include <zen/function/compose.h>
#include <functional>

namespace zen { 


ZEN_FUNCTION_PIPE_OBJECT((take_while)(auto r, f)
    if (is_range<r>)
    (
        make_iterator_range(boost::begin(r), find_if(r, zen::compose(f, std::logical_not<bool>())))
    )

)

}


#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/algorithm/equal.h>
#include <boost/assign.hpp>
#include <vector>
#include <zen/algorithm/detail/is_odd.h>

ZEN_TEST_CASE(take_while_test)
{
    std::vector<int> v1 = boost::assign::list_of(1)(2)(3);
    std::vector<int> v2 = boost::assign::list_of(1);
    
    ZEN_TEST_CHECK(zen::equal(v1 | zen::take_while(is_odd()), v2));
}

#endif

#endif
