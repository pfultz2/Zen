/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    find.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FIND_H
#define ZEN_GUARD_ALGORITHM_FIND_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <algorithm>
#include <string>


namespace zen {

template<class R, class Enable = void>
struct finder
{
    typedef typename boost::range_iterator<R>::type iterator;
    template<class Range, class T>
    static iterator call(Range & r, const T & x)
    {
        return std::find(boost::begin(r), boost::end(r), x);
    }
};

template<class R>
struct finder<R, typename boost::enable_if<is_keyed_range<R> >::type>
{
    typedef typename boost::range_iterator<R>::type iterator;
    template<class Range, class T>
    static iterator call(Range & r, const T & x)
    {
        return r.find(x);
    }
};

template<class Char, class Traits, class Allocator>
struct finder<std::basic_string<Char, Traits, Allocator> >
{
    typedef typename std::basic_string<Char, Traits, Allocator>::const_iterator const_iterator;
    typedef typename std::basic_string<Char, Traits, Allocator>::iterator iterator;
    static const typename std::basic_string<Char, Traits, Allocator>::size_type npos = std::basic_string<Char, Traits, Allocator>::npos;

    template<class T>
    static const_iterator call(const std::basic_string<Char, Traits, Allocator>& s, const T& x)
    {
        auto i = s.find(x);
        if (i == npos) return s.end();
        else return s.begin() + i;
    }

    template<class T>
    static iterator call(std::basic_string<Char, Traits, Allocator>& s, const T& x)
    {
        auto i = s.find(x);
        if (i == npos) return s.end();
        else return s.begin() + i;
    }
};

ZEN_FUNCTION_PIPE_OBJECT((find)(auto r, const x)
        if (is_sub_range<r, x>)(std::search(boost::begin(r), boost::end(r), boost::begin(x), boost::end(x)))
        else if (is_range<r>)(finder<typename boost::remove_cv<ZEN_TYPEOF_TPL(r)>::type>::call(r, x))
    )   

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <map>


ZEN_TEST_CASE(find_test)
{
    std::vector<int> v = boost::assign::list_of(0)(1)(2)(3)(4);
    std::map<int, int> m = boost::assign::map_list_of(0, 1)(1, 2)(2, 3)(3, 4)(4, 5)(5, 6);
    
    ZEN_TEST_EQUAL(2, *(v | zen::find(2)));
    ZEN_TEST_EQUAL(3, (m | zen::find(2))->second);
    ZEN_TEST_EQUAL('H', *(std::string("Hello World") | zen::find("Hello")));
    
    ZEN_TEST_EQUAL(boost::end(v), v | zen::find(5));
    ZEN_TEST_EQUAL(boost::end(m), m | zen::find(6));
    
}

#endif


#endif
