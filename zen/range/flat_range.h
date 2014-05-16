/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    flat_range.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_FLAT_RANGE_H
#define ZEN_GUARD_RANGE_FLAT_RANGE_H

#include <zen/iterator/flat_iterator.h>
#include <zen/range/iterator_range_adaptor.h>

namespace zen {

namespace detail {

struct flat_range_base
{
    template<class Self, class F>
    auto operator()(Self&& self, F f) const
    {
        return make_flat_iterator(f(), self.base_end());
    }
};
}

template<class Range>
using flat_range = iterator_range_adaptor<Range, iterator_range_invoke<detail::flat_range_base>>;

}


#endif