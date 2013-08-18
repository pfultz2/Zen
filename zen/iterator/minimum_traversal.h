/*=============================================================================
    Copyright (c) 2005-2007 Shunsuke Sogame
    minimum_traversal.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ITERATOR_MINIMUM_TRAVERSAL_H
#define ZEN_GUARD_ITERATOR_MINIMUM_TRAVERSAL_H

#include <boost/static_assert.hpp> // missing from 'minimum_category.hpp'
#include <boost/mpl/placeholders.hpp> // missing from 'minimum_category.hpp'
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_categories.hpp>

namespace zen {

template< class T1, class T2 >
struct minimum_traversal :
    boost::detail::minimum_category<
        typename boost::detail::pure_traversal_tag<T1>::type,
        typename boost::detail::pure_traversal_tag<T2>::type
    >
{ };

}

#endif