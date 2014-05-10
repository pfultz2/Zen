/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    reverse_range.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_REVERSE_RANGE_H
#define ZEN_GUARD_RANGE_REVERSE_RANGE_H

#include <boost/iterator/reverse_iterator.hpp>
#include <zen/range/detail/range_adaptor_base.h>

namespace zen {

template<class Range>
struct reverse_range
: detail::range_adaptor_base<Range>
{
    typedef detail::range_adaptor_base<Range> base;

    reverse_range()
    {}

    reverse_range(Range&& r)
    : base(std::forward<Range>(r))
    {}

    typedef boost::reverse_iterator< _t<range_iterator<Range>> > iterator;
    typedef boost::reverse_iterator< _t<range_const_iterator<Range>> > const_iterator;

    iterator begin()
    {
        return iterator(this->base_end());
    }

    iterator end()
    {
        return iterator(this->base_begin());
    }

    const_iterator begin() const
    {
        return const_iterator(this->base_end());
    }

    const_iterator end() const
    {
        return const_iterator(this->base_begin());
    }
};

template<class Range>
reverse_range<Range> make_reverse_range(Range&& r)
{
    return reverse_range<Range>(std::forward<Range>(r));
}

}

#endif