/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    indirect.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_INDIRECT_H
#define ZEN_GUARD_ALGORITHM_INDIRECT_H

#include <zen/algorithm/transform.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((indirect)(auto&& r)
    if (_p<is_range>(r) or _p<boost::fusion::traits::is_sequence>(r))
    (
        zen::transform(r, [](auto&& x) -> auto& { return *x; })
    )
)


}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>


ZEN_TEST_CASE(indirect_test)
{
    std::vector<boost::shared_ptr<int> > v1 = { boost::make_shared<int>(1), boost::make_shared<int>(2)};
    std::vector<int> v2 = { 1, 2 };

    ZEN_TEST_EQUAL(v1 | zen::indirect, v2);
}

#endif

#endif
