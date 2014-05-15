/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    drop_while.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_DROP_WHILE_H
#define ZEN_GUARD_ALGORITHM_DROP_WHILE_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>
#include <zen/make.h>
#include <algorithm>
#include <zen/range/iterator_range_adaptor.h>


namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((drop_while)(auto&& r, auto f)
    if (_p<is_range>(r))
    (
        zen::forward_as<iterator_range_adaptor>(ZEN_AUTO_FORWARD(r), zen::make<iterator_range_invoke>(
            [f](auto&& self){ return std::find_if_not(self.base_begin(), self.base_end(), f); }, 
            [](auto&& self){ return self.base_end(); })
        )
    )

)


}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <zen/algorithm/detail/is_odd.h>

ZEN_TEST_CASE(drop_while_test)
{
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {2, 3};
    
    ZEN_TEST_EQUAL(v1 | zen::drop_while(is_odd()), v2);
}

#endif

#endif
