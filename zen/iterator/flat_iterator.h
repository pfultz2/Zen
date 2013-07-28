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

namespace zen { 

template<class OuterIterator, class InnerRange = typename boost::iterator_value<OuterIterator>::type>
struct flat_iterator
: boost::iterator_facade
<
    flat_iterator<OuterIterator, InnerRange>,
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
        this->select();
    }

    void select()
    {
        for(;iterator!=last;iterator++)
        {
            if (inner_first==inner_last)
            {
                ZEN_XAUTO_TPL(r, *iterator);
                inner_first = boost::begin(r);
                inner_last = boost::end(r);
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
