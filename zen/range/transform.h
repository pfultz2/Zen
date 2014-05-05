/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    transform.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_TRANSFORM_H
#define ZEN_GUARD_RANGE_TRANSFORM_H

#include <zen/range/iterator_range.h>
#include <zen/range/detail/range_adaptor_base.h>
#include <boost/iterator/iterator_adaptor.hpp>

namespace zen {

template<class Range, class Transformer>
struct transform_range
: detail::range_adaptor_base<Range>
{
    typedef detail::range_adaptor_base<Range> base;

    Transformer transformer;
    transform_range()
    {
    }

    transform_range(Range r, Transformer t)
    : base(std::forward<Range>(r)), transformer(t)
    {}

    template<class Derived, class Iterator>
    using transform_iterator_base = boost::iterator_adaptor<
        Derived, 
        Iterator,
        typename std::remove_reference<typename std::result_of<Transformer(_t<range_reference<Range>>)>::type>::type,
        boost::use_default,
        typename std::result_of<Transformer(_t<range_reference<Range>>)>::type
    >;


    template<class Iterator, class TransformRange>
    struct transform_iterator
    : transform_iterator_base<transform_iterator<Iterator, TransformRange>, Iterator>
    {
        typedef transform_iterator_base<transform_iterator<Iterator, TransformRange>, Iterator> super;

        TransformRange * self;
        transform_iterator()
        {}

        transform_iterator(Iterator it, TransformRange * self) : super(it), self(self)
        {}

        template<class I, class R>
        transform_iterator(const transform_iterator<I, R>& other, 
            ZEN_REQUIRES_CONVERTIBLE(I, Iterator),
            ZEN_REQUIRES_CONVERTIBLE(R, Range))
        : super(other.base()), self(other.self)
        {}

        typename super::reference dereference() const
        { 
            return self->transformer(*this->base());
        }
    };

    typedef transform_iterator< _t<range_iterator<Range>>, transform_range> iterator;
    typedef transform_iterator< _t<range_const_iterator<Range>>, const transform_range> const_iterator; 

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
transform_range<Range, F> make_transform_range(Range&& r, F f)
{
    return transform_range<Range, F>(std::forward<Range>(r), f);
}

}

#endif