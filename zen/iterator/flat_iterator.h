/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    flat_iterator.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ITERATOR_FLAT_ITERATOR_H
#define ZEN_GUARD_ITERATOR_FLAT_ITERATOR_H

#include <zen/function/result_of.h>
#include <zen/typeof.h>
#include <boost/range.hpp>
#include <zen/requires.h>

namespace zen { 

template<
    class OuterIterator, 
    class InnerRangeReference = typename boost::iterator_reference<OuterIterator>::type,
    class InnerRange = typename boost::remove_reference<InnerRangeReference>::type>
struct flat_iterator
: boost::iterator_facade
<
    flat_iterator<OuterIterator, InnerRangeReference, InnerRange>,
    typename boost::range_value<InnerRange >::type,
    boost::forward_traversal_tag,
    typename boost::range_reference<InnerRange>::type
>
{
    // TODO: Static assert that the InnerRange is safe
    typedef typename boost::range_iterator<InnerRange>::type InnerIteraror;

    OuterIterator iterator;
    InnerIteraror inner_first;
    InnerIteraror inner_last;
    OuterIterator last;

    flat_iterator(OuterIterator iterator, OuterIterator last) : iterator(iterator), last(last)
    {
        this->select_first();
    }

    template<class Iterator, class Range>
    flat_iterator(const flat_iterator<Iterator, Range>& rhs, 
        ZEN_CLASS_REQUIRES(boost::is_convertible<Iterator, OuterIterator>, boost::is_convertible<Range, InnerRange>)* = 0) 
    : iterator(rhs.iterator), last(rhs.last), inner_first(rhs.inner_first), inner_last(rhs.inner_last)
    {}

    void select_first()
    {
        if (iterator!=last)
        {
            this->inner_select();
            if (inner_first==inner_last) this->select();
        }
    }

    void inner_select()
    {
        InnerRangeReference r = *iterator;
        inner_first = boost::begin(r);
        inner_last = boost::end(r);
    }
    
    void select()
    {
        for(;iterator!=last;iterator++)
        {
            if (inner_first==inner_last)
            {
                this->inner_select();
            }
            else inner_first++;
            for(;inner_first!=inner_last;inner_first++)
                return;
        }
    }

    void increment()
    {
        this->select();
    }

    bool equal(const flat_iterator& other) const
    {
        return this->iterator == other.iterator;
    }

    typename boost::range_reference<InnerRange>::type dereference() const
    {
        return *inner_first;
    }

};

template<class Iterator>
flat_iterator<Iterator> make_flat_iterator(Iterator first, Iterator last)
{
    return flat_iterator<Iterator>(first, last);
}

}

#endif
