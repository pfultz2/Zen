/*=============================================================================
    Copyright (c) 2013 Paul Fultz II
    stride_iterator.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ITERATOR_STRIDE_ITERATOR_H
#define ZEN_GUARD_ITERATOR_STRIDE_ITERATOR_H

#include <utility>
#include <limits>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/next_prior.hpp>
#include <boost/type_traits/is_same.hpp>
#include <zen/iterator/next.h>

namespace zen { 

namespace stride_detail {

template<class Iterator>
std::size_t advance_ra(Iterator& it, Iterator last, long n, long step, std::size_t i)
{
    it += n;
    return i + step;
}

template<class Iterator>
std::size_t advance_bi(Iterator& it, Iterator last, long n, long step, std::size_t i)
{
    if (n > 0)
    {
        while(n-- and it != last) ++it;
    }
    else
    {
        while(n++ and it != last) --it;
    }
    return i;
}

template<class Iterator>
std::size_t advance_forward(Iterator& it, Iterator last, long n, long step, std::size_t i)
{
    ZEN_ASSERT(n >= 0);
    while(n-- and it != last) ++it;
    return i;
}

ZEN_FUNCTION_OBJECT((stride_advance)(auto iterator, last, n, step, index)
                    if (has_iterator_traversal<iterator, boost::random_access_traversal_tag>)
                    (advance_ra(iterator, last, n, step, index))
                    else if (has_iterator_traversal<iterator, boost::bidirectional_traversal_tag>)
                    (advance_bi(iterator, last, n, step, index))
                    else
                    (advance_forward(iterator, last, n, step, index))
)

ZEN_FUNCTION_OBJECT((last_index)(auto iterator, auto last)
                    if (has_iterator_traversal<iterator, boost::random_access_traversal_tag>)
                    (last - iterator)
                    else
                    (std::numeric_limits<std::size_t>::max())
)

}

template< class ForwardIterator>
struct stride_iterator 
: boost::iterator_adaptor<stride_iterator<ForwardIterator>, ForwardIterator>
{
    typedef typename boost::iterator_adaptor<stride_iterator<ForwardIterator>, ForwardIterator> super;
    typedef typename super::difference_type difference_type;
    typedef typename super::reference reference;

    std::size_t index;
    const difference_type step;
    const ForwardIterator last;

    stride_iterator()
    { }

    stride_iterator(ForwardIterator it, ForwardIterator last, difference_type step) : super(it), step(step), index(0), last(last)
    {
    }

    stride_iterator(ForwardIterator it, ForwardIterator last, difference_type step, std::size_t index) : super(it), step(step), index(index), last(last)
    {
    }

    template< class F>
    stride_iterator(stride_iterator<F> const& other,
        typename boost::enable_if_convertible<F, ForwardIterator>::type * = 0
    ) :
        super(other.base()), step(other.step), index(other.index), last(last)
    {}

    difference_type step_size() const
    {
        return this->step;
    }

    void increment()
    {
        this->index = stride_detail::stride_advance(this->base_reference(), this->last, this->step, 1, this->index);
    }

    void decrement()
    {
        this->index = stride_detail::stride_advance(this->base_reference(), this->last, -this->step, -1, this->index);
    }

    void advance(difference_type n)
    {
        this->index = stride_detail::stride_advance(this->base_reference(), this->last, this->step * n, this->step, this->index);
    }

    template< class F>
    bool equal(stride_iterator<F> const& other) const
    {
        return this->last == other.last and
        (this->index == other.index or this->base() == other.base());
    }

    template< class F>
    difference_type distance_to(stride_iterator<F> const& other) const
    {
        return other.index - this->index;
    }
};

template<class Iterator, class Step>
stride_iterator<Iterator> make_begin_stride_iterator(Iterator it, Iterator last, Step step)
{
    return stride_iterator<Iterator>(it, last, step);
}

template<class Iterator, class Step>
stride_iterator<Iterator> make_end_stride_iterator(Iterator first, Iterator last, Step step)
{
    return stride_iterator<Iterator>(last, last, step, (stride_detail::last_index(first, last) / step)+1);
}

}

#endif
