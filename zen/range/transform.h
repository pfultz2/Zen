/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    transform.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_TRANSFORM_H
#define ZEN_GUARD_RANGE_TRANSFORM_H

#include <zen/range/iterator_range.h>
#include <zen/range/iterator_range_adaptor.h>
#include <boost/iterator/iterator_adaptor.hpp>
#include <zen/make.h>

namespace zen {

namespace detail {

template<class Transformer>
struct transform_range_base
{
    Transformer transformer;
    template<class X>
    transform_range_base(X x) : transformer(x)
    {}

    template<class Derived, class Iterator>
    using transform_iterator_base = boost::iterator_adaptor<
        Derived, 
        Iterator,
        typename std::remove_reference<typename std::result_of<Transformer(_t<iterator_reference<Iterator>>)>::type>::type,
        boost::use_default,
        typename std::result_of<Transformer(_t<iterator_reference<Iterator>>)>::type
    >;


    template<class Iterator, class TransformRange>
    struct transform_iterator
    : transform_iterator_base<transform_iterator<Iterator, TransformRange>, Iterator>
    {
        typedef transform_iterator_base<transform_iterator<Iterator, TransformRange>, Iterator> super;

        TransformRange * self;
        transform_iterator()
        {}

        transform_iterator(Iterator it, TransformRange & tr) : super(it), self(&tr)
        {}

        template<class I, class R>
        transform_iterator(const transform_iterator<I, R>& other, 
            ZEN_REQUIRES_CONVERTIBLE(I, Iterator),
            ZEN_REQUIRES_CONVERTIBLE(R, TransformRange))
        : super(other.base()), self(other.self)
        {}

        typename super::reference dereference() const
        { 
            return self->transformer(*this->base());
        }
    };

    template<class Self, class F>
    auto operator()(Self&& self, F f) const
    {
        return make<transform_iterator>(f(), *this);
    }
};

}

template<class Range, class Transformer>
using transform_range = iterator_range_adaptor<Range, iterator_range_invoke<detail::transform_range_base<Transformer>>>;

template<class Range, class F>
transform_range<Range, F> make_transform_range(Range&& r, F f)
{
    return transform_range<Range, F>(std::forward<Range>(r), f);
}

}

#endif