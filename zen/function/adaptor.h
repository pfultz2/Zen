/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    adaptor.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_ADAPTOR_H
#define ZEN_GUARD_FUNCTION_ADAPTOR_H

#include <zen/pp.h>
#include <zen/requires.h>
#include <boost/type_traits.hpp>

namespace zen {

//Optimization for stateless functions
template<class F, class Enable = void>
struct function_adaptor_base
{
    F f;
    function_adaptor_base() {};
    template<class X>
    function_adaptor_base(X x) : f(x) {};

    const F& get_function() const
    {
        return f;
    }
};

template<class F>
struct function_adaptor_base<F, ZEN_CLASS_REQUIRES(boost::is_empty<F>)>
{
    function_adaptor_base() {};
    template<class X>
    function_adaptor_base(X) {};

    F get_function() const
    {
        return F();
    }
};

template<class F, class Enable = void>
struct function_adaptor_type
{
    typedef const F& type;
};

template<class F>
struct function_adaptor_type<F, ZEN_CLASS_REQUIRES(boost::is_empty<F>)>
{
    typedef F type;
};

}

#endif
