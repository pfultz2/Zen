/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    next.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ITERATOR_NEXT_H
#define ZEN_GUARD_ITERATOR_NEXT_H

#include <zen/function/builder.h>
#include <zen/traits.h>

namespace zen {

namespace detail {

template<class Iterator>
Iterator advance_ra(Iterator it, long n)
{
    it += n;
    return it;
}

template<class Iterator>
Iterator advance_bi(Iterator it, long n)
{
    if (n > 0)
    {
        while(n--) ++it;
    }
    else
    {
        while(n++) --it;
    }
    return it;
}

template<class Iterator>
Iterator advance_forward(Iterator it, long n)
{
    ZEN_ASSERT(n > 0);
    while(n--) ++it;
    return it;
}
    
}

ZEN_FUNCTION_OBJECT((next)(iterator, n)
                    if (has_iterator_traversal<iterator, boost::random_access_traversal_tag>)
                    (detail::advance_ra(iterator, n))
                    else if (has_iterator_traversal<iterator, boost::bidirectional_traversal_tag>)
                    (detail::advance_bi(iterator, n))
                    else
                    (detail::advance_forward(iterator, n))

)

}



#endif
