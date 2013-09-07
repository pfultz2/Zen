/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    indirect.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_INDIRECT_H
#define ZEN_GUARD_ALGORITHM_INDIRECT_H

#include <zen/algorithm/transform.h>

namespace zen { namespace detail {

ZEN_FUNCTION_CLASS((indirect_selector)(auto x)(*x))

}

ZEN_FUNCTION_PIPE_OBJECT((indirect)(auto r)
    if (is_range_or_sequence<r>)(zen::transform(r, detail::indirect_selector()))
)


}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/vector.hpp>
#include <zen/algorithm/equal.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>


ZEN_TEST_CASE(indirect_test)
{
    std::vector<boost::shared_ptr<int> > v1 = boost::assign::list_of(boost::make_shared<int>(1))(boost::make_shared<int>(2));
    std::vector<int> v2 = boost::assign::list_of(1)(2);

    ZEN_TEST_EQUAL(v1 | zen::indirect, v2);
}

#endif

#endif
