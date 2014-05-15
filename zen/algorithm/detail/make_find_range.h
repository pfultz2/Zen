/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    make_find_range.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_MAKE_FIND_RANGE_H
#define ZEN_GUARD_MAKE_FIND_RANGE_H

namespace zen { namespace detail {

template<class Range, class Iterator>
auto make_find_range(Range&& r, Iterator it)
{
    auto last = it;
    if (it != zen::end(r)) ++last;
    return make_iterator_range(it, last);
}

}}

#endif