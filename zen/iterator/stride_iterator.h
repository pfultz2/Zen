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
#include <zen/function/partial.h>

namespace zen { 

namespace stride_detail {

template<class Iterator1, class Iterator2>
std::size_t advance_ra(Iterator1& it, const Iterator2& last, long n, long m, std::size_t i)
{
    it += n;
    return i + m;
}

template<class Iterator1, class Iterator2>
std::size_t advance_bi(Iterator1& it, const Iterator2& last, long n, long m, std::size_t i)
{
    if (n > 0)
    {
        while(n-- and it != last) 
        {
            ++it;
        }
    }
    else
    {
        while(n++ and it != last)
        {
            --it;
        }
    }
    return i;
}

template<class Iterator1, class Iterator2>
std::size_t advance_forward(Iterator1& it, const Iterator2& last, long n, long m, std::size_t i)
{
    ZEN_ASSERT(n >= 0);
    while(n-- and it != last)
    {
        ++it;
    }
    return i;
}

ZEN_FUNCTION_OBJECT((stride_advance)(auto iterator, const last, n, m, index)
                    if (has_iterator_traversal<iterator, boost::random_access_traversal_tag>)
                    (advance_ra(iterator, last, n, m, index))
                    else if (has_iterator_traversal<iterator, boost::bidirectional_traversal_tag>)
                    (advance_bi(iterator, last, n, m, index))
                    else
                    (advance_forward(iterator, last, n, m, index))
)

// This is a workaround for GCC when in C++03 mode. GCC incorrectly binds
// `std::numeric_limits<std::size_t>::max()` to a non-const lvalue reference,
// which causes type deduction to fail.
template<class T>
const T stride_max()
{
    return std::numeric_limits<T>::max();
}

ZEN_FUNCTION_OBJECT((last_index)(const iterator, const last)
                    if (has_iterator_traversal<iterator, boost::random_access_traversal_tag>)
                    (last - iterator)
                    else
                    (stride_max<std::size_t>())
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
    const  ForwardIterator last;

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
        super(other.base()), step(other.step), index(other.index), last(other.last)
    {}

    difference_type step_size() const
    {
        return this->step;
    }

    void increment()
    {
        this->index = zen::partial(stride_detail::stride_advance)(boost::ref(this->base_reference()), boost::cref(this->last))(this->step, 1, this->index);
    }

    void decrement()
    {
        this->index = zen::partial(stride_detail::stride_advance)(boost::ref(this->base_reference()), boost::cref(this->last))(-this->step, -1, this->index);
    }

    void advance(difference_type n)
    {
        this->index = zen::partial(stride_detail::stride_advance)(boost::ref(this->base_reference()), boost::cref(this->last))(this->step * n, n, this->index);
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
