/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    cycle.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_CYCLE_H
#define ZEN_GUARD_RANGE_CYCLE_H

// #include <zen/iterator/cycle_iterator.h>
#include <zen/range/iterator_range.h>
#include <zen/range/detail/range_adaptor_base.h>
#include <zen/assert.h>

namespace zen {

namespace detail {

template< class Difference >
std::pair<Difference, Difference> positive_rem_div(Difference a, Difference b)
{
    ZEN_ASSERT(b >= 0);

    Difference const q = a / b;
    Difference const r = a % b;
    if (r < 0)
        return std::make_pair(q - 1, r + b);
    else
        return std::make_pair(q, r);
}

} 

template<class Range, class Incrementable=unsigned int>
struct cycle_range
: detail::range_adaptor_base<Range>
{
    typedef detail::range_adaptor_base<Range> base;
    Incrementable max;

    cycle_range()
    {}

    cycle_range(Range r, Incrementable n = std::numeric_limits<Incrementable>::max())
    : base(std::forward<Range>(r)), max(n)
    {}

    template< class ForwardIterator, class CycleRange>
    struct cycle_iterator 
    : boost::iterator_adaptor<cycle_iterator<ForwardIterator, CycleRange>, ForwardIterator>
    {
        typedef typename boost::iterator_adaptor<cycle_iterator<ForwardIterator, CycleRange>, ForwardIterator> super;
        typedef typename super::difference_type difference_type;
        typedef typename super::reference reference;

        Incrementable depth;
        CycleRange * self;

        cycle_iterator()
        { }

        cycle_iterator(CycleRange * range) 
        : super(range->base_begin()), depth(0), self(range)
        {
        }
        
        cycle_iterator(ForwardIterator it, CycleRange * range) 
        : super(it), depth(std::numeric_limits<Incrementable>::max()), self(range)
        {
        }

        cycle_iterator(ForwardIterator it, Incrementable depth, CycleRange * range) 
        : super(it), depth(depth), self(range)
        {
        }

        template< class I, class R>
        cycle_iterator(cycle_iterator<I, R> const& other,
            ZEN_REQUIRES_CONVERTIBLE(I, ForwardIterator),
            ZEN_REQUIRES_CONVERTIBLE(R, CycleRange)) 
        : super(other.base()), depth(other.depth), self(other.self)
        {}

        Incrementable count() const
        {
            return depth;
        }

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            ZEN_ASSERT(self != nullptr);
            return self->base_begin() == other.self->base_begin() && self->base_end() == other.self->base_end();
        }

        bool check_depth() const
        {
            return (depth <= self->max) and (this->depth >= 0);
        }

        reference dereference() const
        {
            ZEN_ASSERT(self != nullptr);
            ZEN_ASSERT(this->base() != self->base_end());
            return *this->base();
        }

        template< class F, class I >
        bool equal(cycle_iterator<F, I> const& other) const
        {
            ZEN_ASSERT(is_compatible(other));
            return depth == other.depth && this->base() == other.base();
        }

        void increment()
        {
            ZEN_ASSERT(self != nullptr);
            if (++this->base_reference() == self->base_end()) 
            {
                this->base_reference() = self->base_begin();
                ++depth;
                ZEN_ASSERT(check_depth());
            }
        }

        void decrement()
        {
            ZEN_ASSERT(self != nullptr);
            if (this->base() == self->base_begin()) 
            {
                this->base_reference() = self->base_end();
                --depth;
                ZEN_ASSERT(check_depth());
            }

            --this->base_reference();
        }

        void advance(difference_type n)
        {
            ZEN_ASSERT(self != nullptr);
            std::pair<difference_type, difference_type> const q_r =
                detail::positive_rem_div((this->base() - self->base_begin()) + n, self->base_end() - self->base_begin());
            ZEN_ASSERT(0 <= q_r.second);
            ZEN_ASSERT(q_r.second < self->base_end() - self->base_begin());

            this->base_reference() = self->base_begin() + q_r.second;
            depth += q_r.self->base_begin();
            ZEN_ASSERT(check_depth());
        }

        template< class I, class R >
        difference_type distance_to(cycle_iterator<I, R> const& other) const
        {
            ZEN_ASSERT(self != nullptr);
            ZEN_ASSERT(is_compatible(other));
            return ((self->base_end() - self->base_begin()) * (other.depth - depth)) + (other.base() - this->base());
        }
    };

    typedef cycle_iterator< _t<range_iterator<Range>>, cycle_range> iterator;
    typedef cycle_iterator< _t<range_const_iterator<Range>>, const cycle_range> const_iterator;

    iterator begin()
    {
        return iterator(this->base_begin(), 0, this);
    }

    iterator end()
    {
        return iterator(this->base_begin(), this->max, this);
    }

    const_iterator begin() const
    {
        return const_iterator(this->base_begin(), 0, this);
    }

    const_iterator end() const
    {
        return const_iterator(this->base_begin(), this->max, this);
    }
};

template<class Range>
cycle_range<Range&&> make_cycle_range(Range&& r, unsigned int n=std::numeric_limits<unsigned int>::max())
{
    return cycle_range<Range&&>(std::forward<Range>(r), n);
}

}

#endif
