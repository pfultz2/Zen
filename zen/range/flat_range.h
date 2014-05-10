/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    flat_range.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_FLAT_RANGE_H
#define ZEN_GUARD_RANGE_FLAT_RANGE_H

#include <zen/iterator/flat_iterator.h>

namespace zen {

template<class Range>
struct flat_range
: detail::range_adaptor_base<Range>
{
    typedef detail::range_adaptor_base<Range> base;

    flat_range()
    {}

    flat_range(Range&& r)
    : base(std::forward<Range>(r))
    {}

    typedef flat_iterator< _t<range_iterator<Range>> > iterator;
    typedef flat_iterator< _t<range_const_iterator<Range>> > const_iterator;

    iterator begin()
    {
        return iterator(this->base_begin(), this->base_end());
    }

    iterator end()
    {
        return iterator(this->base_end(), this->base_end());
    }

    const_iterator begin() const
    {
        return const_iterator(this->base_begin(), this->base_end());
    }

    const_iterator end() const
    {
        return const_iterator(this->base_end(), this->base_end());
    }
};

template<class Range>
flat_range<Range> make_flat_range(Range&& r)
{
    return flat_range<Range>(std::forward<Range>(r));
}

}


#endif