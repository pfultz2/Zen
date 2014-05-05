/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    filter.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_FILTER_H
#define ZEN_GUARD_RANGE_FILTER_H

#include <zen/range/iterator_range.h>
#include <zen/range/detail/range_adaptor_base.h>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>

namespace zen {

template<class Range, class Predicate>
struct filter_range
: detail::range_adaptor_base<Range>
{
    typedef detail::range_adaptor_base<Range> base;

    Predicate predicate;
    filter_range()
    {
    }

    filter_range(Range r, Predicate t)
    : base(std::forward<Range>(r)), predicate(t)
    {}

    template<class Derived, class Iterator>
    using filter_iterator_base = boost::iterator_adaptor<
        Derived, 
        Iterator,
        boost::use_default,
        typename boost::mpl::if_<
            is_advanceable_iterator<Iterator>,
            boost::bidirectional_traversal_tag,
            boost::use_default
        >::type
    >;


    template<class Iterator, class FilterRange>
    struct filter_iterator
    : filter_iterator_base<filter_iterator<Iterator, FilterRange>, Iterator>
    {
        typedef filter_iterator_base<filter_iterator<Iterator, FilterRange>, Iterator> super;

        void satisfy_predicate()
        {
            while (this->base() != self->base_end() && !self->predicate(*this->base()))
                ++(this->base_reference());
        }

        FilterRange * self;
        filter_iterator()
        {}

        filter_iterator(Iterator it, FilterRange * self) : super(it), self(self)
        {
            this->satisfy_predicate();
        }

        template<class I, class R>
        filter_iterator(const filter_iterator<I, R>& other, 
            ZEN_REQUIRES_CONVERTIBLE(I, Iterator),
            ZEN_REQUIRES_CONVERTIBLE(R, Range))
        : super(other.base()), self(other.self)
        {}

        auto predicate() const { return self->predicate; }

        void increment()
        {
            ++(this->base_reference());
            this->satisfy_predicate();
        }

        void decrement()
        {
            while(!self->predicate(*--(this->base_reference()))){};
        }
    };

    typedef filter_iterator< _t<range_iterator<Range>>, filter_range> iterator;
    typedef filter_iterator< _t<range_const_iterator<Range>>, const filter_range> const_iterator; 

    iterator begin()
    {
        return iterator(this->base_begin(), this);
    }

    iterator end()
    {
        return iterator(this->base_end(), this);
    }

    const_iterator begin() const
    {
        return const_iterator(this->base_begin(), this);
    }

    const_iterator end() const
    {
        return const_iterator(this->base_end(), this);
    }

};

template<class Range, class F>
filter_range<Range, F> make_filter_range(Range&& r, F f)
{
    return filter_range<Range, F>(std::forward<Range>(r), f);
}

}

#endif