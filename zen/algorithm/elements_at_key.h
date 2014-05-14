/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    element_at_key.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_ELEMENT_AT_KEY_H
#define ZEN_GUARD_ALGORITHM_ELEMENT_AT_KEY_H

#include <zen/function/builder.h>
#include <zen/algorithm/at_key.h>
#include <zen/algorithm/transform.h>

namespace zen { 

namespace detail {

template<class Key>
struct elements_at_key_base
{
    ZEN_FUNCTION_CLASS((apply_base)(auto&& r) 
    if (_p<is_range>(r) or _p<boost::fusion::traits::is_sequence>(r))
    (
        r | zen::transform([](auto&& x) -> decltype(auto)
        { 
            return zen::at_key<Key>(x);
        })
    ));
    typedef pipable_adaptor<apply_base> apply;
};
    
}

template<class Key, class... Ts>
decltype(auto) elements_at_key(Ts&&... xs)
{
    return typename detail::elements_at_key_base<Key>::apply()(std::forward<Ts>(xs)...);
}

}



#ifdef ZEN_TEST
#include <zen/test.h>
#include <vector>
#include <boost/fusion/container/vector.hpp>


ZEN_TEST_CASE(elments_at_key_test)
{
    boost::fusion::set<int, char, bool> s(1, 'x', true);

    std::vector<boost::fusion::set<int, char, bool> > v1;
    v1.push_back(s);
    v1.push_back(s);
    v1.push_back(s);

    std::vector<char> v2 = {'x','x','x'};

    ZEN_TEST_EQUAL(zen::elements_at_key<char>(v1), v2);
    ZEN_TEST_EQUAL(v1 | zen::elements_at_key<char>(), v2);
}

#endif

#endif
