/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    range_adaptor_base.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_DETAIL_RANGE_ADAPTOR_BASE_H
#define ZEN_GUARD_RANGE_DETAIL_RANGE_ADAPTOR_BASE_H

#include <zen/range/range_traits.h>

namespace zen { namespace detail {

template<class Range>
class range_adaptor_base
{
    Range rng_;
public:
    range_adaptor_base() = default;
    range_adaptor_base(Range &&rng) : rng_(std::forward<Range&&>(rng))
    {}
    Range &base()
    {
        return rng_;
    }
    Range const &base() const
    {
        return rng_;
    }

    decltype(auto) base_begin()
    {
        return zen::begin(this->base());
    }

    decltype(auto) base_end()
    {
        return zen::end(this->base());
    }

    decltype(auto) base_begin() const
    {
        return zen::begin(this->base());
    }

    decltype(auto) base_end() const
    {
        return zen::end(this->base());
    }
};

template<class Range>
class range_adaptor_base<Range &>
{
    Range *rng_;
public:
    range_adaptor_base() = default;
    range_adaptor_base(Range &rng) : rng_(&rng)
    {}
    Range &base()
    {
        return *rng_;
    }

    const Range &base() const
    {
        return *rng_;
    }

    decltype(auto) base_begin()
    {
        return zen::begin(this->base());
    }

    decltype(auto) base_end()
    {
        return zen::end(this->base());
    }

    decltype(auto) base_begin() const
    {
        return zen::begin(this->base());
    }

    decltype(auto) base_end() const
    {
        return zen::end(this->base());
    }
};

}}

#endif