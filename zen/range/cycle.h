/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    cycle.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_CYCLE_H
#define ZEN_GUARD_RANGE_CYCLE_H

#include <zen/iterator/cycle_iterator.h>
#include <zen/range/iterator_range.h>


namespace zen { 

template<class Range>
iterator_range<cycle_iterator<typename boost::range_iterator<Range>::type> >
cycle(Range& r, unsigned int n=std::numeric_limits<unsigned int>::max())
{
    typedef cycle_iterator<typename boost::range_iterator<Range>::type> iterator;
    return iterator_range<iterator>
    (
        iterator(boost::begin(r), boost::end(r)), 
        iterator(boost::end(r), n, boost::begin(r), boost::end(r))
    );
}

}

#endif
