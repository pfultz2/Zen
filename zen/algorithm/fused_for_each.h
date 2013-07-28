/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    fused_for_each.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FUSED_FOR_EACH_H
#define ZEN_GUARD_ALGORITHM_FUSED_FOR_EACH_H

#include <zen/algorithm/for_each.h>
#include <zen/function/fuse.h>

namespace zen {

ZEN_FUNCTION_PIPE_OBJECT((fused_for_each)(auto r, f)
    (zen::for_each(r, zen::fuse(f)))
)

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <map>
#include <zen/algorithm/equal.h>
#include <zen/algorithm/detail/increment.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

ZEN_FUNCTION_CLASS((fused_increment)(const x, y)(++(*y)))

ZEN_TEST_CASE(fused_for_each_test)
{
    std::map<int, boost::shared_ptr<int> > m1 = boost::assign::map_list_of(0, boost::make_shared<int>(1))(1, boost::make_shared<int>(2));
    std::map<int, boost::shared_ptr<int> > m2 = boost::assign::map_list_of(0, boost::make_shared<int>(2))(1, boost::make_shared<int>(3));

    m1 | zen::fused_for_each(fused_increment());
    ZEN_TEST_EQUAL(m1, m2);
}

#endif

#endif
