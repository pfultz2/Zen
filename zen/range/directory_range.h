/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    directory_range.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_DIRECTORY_RANGE_H
#define ZEN_GUARD_RANGE_DIRECTORY_RANGE_H

#include <boost/filesystem/operations.hpp>
#include <zen/range/iterator_range.h>

namespace zen { 

inline iterator_range<boost::filesystem::directory_iterator>
    directory_range(const boost::filesystem::path& p)
{
    return make_iterator_range(boost::filesystem::directory_iterator(p),
                               boost::filesystem::directory_iterator());
}

inline iterator_range<boost::filesystem::recursive_directory_iterator>
    recursive_directory_range(const boost::filesystem::path& p)
{
    return make_iterator_range(boost::filesystem::recursive_directory_iterator(p),
                               boost::filesystem::recursive_directory_iterator());
}

}

#endif
