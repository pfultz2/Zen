 /*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    drop.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_DROP_H
#define ZEN_GUARD_ALGORITHM_DROP_H

#include <zen/algorithm/at.h>
#include <zen/make.h>
#include <zen/range/iterator_range_adaptor.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((drop)(auto&& r, auto n)
    if (_p<is_range>(r))
    (
        zen::forward_as<iterator_range_adaptor>(ZEN_AUTO_FORWARD(r), zen::make<iterator_range_invoke>(
            [n](auto&& self){ return detail::iterator_at(self.base_range(), n); }, 
            [](auto&& self){ return self.base_end(); })
        )
    )

)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>

ZEN_TEST_CASE(drop_test)
{
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {2, 3};
    
    ZEN_TEST_EQUAL(v1 | zen::drop(1), v2);
    ZEN_TEST_EQUAL(zen::drop(v1, 1), v2);
}

#endif

#endif
