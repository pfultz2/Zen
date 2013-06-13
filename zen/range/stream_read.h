/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    stream_read.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_STREAM_READ_H
#define ZEN_GUARD_RANGE_STREAM_READ_H

#include <iterator>
#include <zen/range/iterator_range.h>

namespace zen {

template< class Type, class Elem, class Traits >
iterator_range< std::istream_iterator<Type, Elem, Traits> >
istream_read(std::basic_istream<Elem, Traits>& in)
{
    return iterator_range< std::istream_iterator<Type, Elem, Traits> >
    (
        std::istream_iterator<Type, Elem, Traits>(in),
        std::istream_iterator<Type, Elem, Traits>()
    );
}

}

#endif
