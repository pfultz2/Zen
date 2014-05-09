/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    flat_iterator.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ITERATOR_FLAT_ITERATOR_H
#define ZEN_GUARD_ITERATOR_FLAT_ITERATOR_H


#include <zen/range/range_traits.h>
#include <zen/range/detail/range_adaptor_base.h>
#include <zen/requires.h>

namespace zen { 

template<
    class OuterIterator, 
    class InnerRangeReference = typename zen::iterator_reference<OuterIterator>::type>
struct flat_iterator
: boost::iterator_facade
<
    flat_iterator<OuterIterator, InnerRangeReference>,
    typename zen::range_value<InnerRangeReference >::type,
    boost::forward_traversal_tag,
    typename zen::range_reference<InnerRangeReference>::type
>
{
    typedef typename zen::range_iterator<InnerRangeReference>::type InnerIteraror;

    OuterIterator iterator;
    OuterIterator last;
    InnerIteraror inner_it;

    flat_iterator(OuterIterator iterator, OuterIterator last) : iterator(iterator), last(last)
    {
        if (this->iterator!=this->last) 
        {
            this->inner_it = zen::begin(*this->iterator);
            if (this->inner_it == zen::end(*this->iterator)) this->increment();
        }
    }

    template<class I, class R>
    flat_iterator(const flat_iterator<I, R>& rhs, 
        ZEN_REQUIRES_CONVERTIBLE(I, OuterIterator)) 
    : iterator(rhs.iterator), last(rhs.last), inner_it(rhs.inner_it)
    {}

    bool is_outer_end() const
    {
        return this->iterator == this->last;
    }

    void increment()
    {
        goto resume;
        for(;this->iterator!=this->last;++this->iterator)
        {
            for(this->inner_it=zen::begin(*this->iterator);this->inner_it!=zen::end(*this->iterator);++this->inner_it)
            {
                return;
                resume:;
            }
        }
    }

    void decrement()
    {
        goto resume;
        for(;;--this->iterator)
        {
            for(this->inner_it=zen::end(*this->iterator);this->inner_it!=zen::begin(*this->iterator);)
            {
                --this->inner_it;
                return;
                resume:;
            }
        }
    }

    // TODO: Advance

    bool equal(const flat_iterator& other) const
    {
        return this->iterator == other.iterator and (this->is_outer_end() or this->inner_it == other.inner_it);
    }

    decltype(auto) dereference() const
    {
        ZEN_ASSERT(!this->is_outer_end());
        ZEN_ASSERT(this->inner_it != zen::end(*this->iterator));
        return *this->inner_it;
    }

};

template<class Iterator>
flat_iterator<Iterator> make_flat_iterator(Iterator first, Iterator last)
{
    return flat_iterator<Iterator>(first, last);
}

}

#endif
