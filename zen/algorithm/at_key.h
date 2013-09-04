/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    at_key.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_AT_KEY_H
#define ZEN_GUARD_ALGORITHM_AT_KEY_H

#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <zen/function/builder.h>

namespace zen { 

namespace detail {

template<class Key>
struct at_key_base
{
    ZEN_FUNCTION_CLASS((apply_base)(auto seq) if (is_sequence<seq>)(boost::fusion::at_key<Key>(seq)));
    typedef pipable_adaptor<apply_base> apply;
};
    
}

template<class Key, class S>
typename zen::result_of<typename detail::at_key_base<Key>::apply(S)>::type
at_key(S& s)
{
    return typename detail::at_key_base<Key>::apply()(s);
}

template<class Key>
typename detail::at_key_base<Key>::apply
at_key()
{
    return typename detail::at_key_base<Key>::apply();
}

}



#ifdef ZEN_TEST
#include <zen/test.h>
#include <boost/assign.hpp>
#include <vector>
#include <boost/fusion/container/set.hpp>


ZEN_TEST_CASE(at_key_test)
{
    boost::fusion::set<int, char, bool> s(1, 'x', true);
    // assert(at_key<char>(s) == 'x');
    ZEN_TEST_EQUAL(zen::at_key<char>(s), 'x');
    ZEN_TEST_EQUAL(s| zen::at_key<char>(), 'x');

    // boost::fusion::vector<int, int, int> v(1, 2, 3);
    // ZEN_TEST_EQUAL(zen::at_key<1>(v), 2);
    // ZEN_TEST_EQUAL(v | zen::at_key<1>(), 2);
}

#endif

#endif
