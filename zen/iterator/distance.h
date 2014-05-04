/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    distance.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ITERATOR_DISTANCE_H
#define ZEN_GUARD_ITERATOR_DISTANCE_H

#include <zen/function/builder.h>
#include <zen/iterator/iterator_traits.h>
#include <zen/returns.h>

namespace zen {

namespace detail {
ZEN_FUNCTION_OBJECT((distance)(auto start, auto last)
    if (_p<std::is_same>(start, last) and _p<is_advanceable_iterator>(start))(last - start)
    else if (_p<std::is_same>(start, last) and _p<is_input_iterator>(start))(std::distance(start, last))
)
}

template<class Iterator>
auto distance(Iterator start, Iterator last) ZEN_RETURNS(detail::distance(start, last));

}

#endif