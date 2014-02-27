/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    general.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_GENERAL_H
#define ZEN_GUARD_FUNCTION_GENERAL_H

// @begin
// general
// =======
// 
// Description
// -----------
// 
// The `general` function adaptor becomes a lazy function when a phoenix actor is
// passed to it, otherwise, the function works as it normally does.
// 
// Synopsis
// --------
// 
//     template<class F>
//     general_adaptor<F> general(F f);
// 
// @end

#include <zen/function/lazy.h>
#include <zen/function/conditional.h>

#include <type_traits>
#include <boost/mpl/or.hpp>

namespace zen { 

namespace detail {

template<class Derived, class F>
struct general_adaptor_base
{
    // typedef void zen_is_callable_by_result_tag;
    general_adaptor_base() {} 

    const F& get_function() const
    {
        return static_cast<const Derived&>(*this);
    }

    template<class T>
    struct is_lazy
    : boost::mpl::bool_<
        std::is_bind_expression<typename std::remove_reference<T>::type>() or 
        std::is_placeholder<typename std::remove_reference<T>::type>()>
    {};

    template<class... Ts, 
        ZEN_REQUIRES(not boost::mpl::or_<is_lazy<Ts>...>())>
    auto operator()(Ts&&... xs) const
    {
        return this->get_function()(std::forward<Ts>(xs)...);
    }
};


}

template<class F>
struct general_adaptor 
: conditional_adaptor<detail::general_adaptor_base<general_adaptor<F>, F>, lazy_adaptor<F> >
{
    typedef conditional_adaptor<detail::general_adaptor_base<general_adaptor<F>, F>, lazy_adaptor<F> > base;
    general_adaptor() {}

    template<class X>
    general_adaptor(X x) : base({}, x)
    {}

    const F& base_function() const
    {
        return *this;
    }
};

template<class F>
general_adaptor<F> general(F f)
{
    return general_adaptor<F>(f);
}

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/placeholders.h>

zen::static_<zen::general_adaptor<binary_class> > binary_general = {};

ZEN_TEST_CASE(general_test)
{
    using zen::ph::_1;
    using zen::ph::_2;
    ZEN_TEST_EQUAL(3, binary_general(1, 2));
    ZEN_TEST_EQUAL(3, binary_general(_1, _2)(1, 2));
    ZEN_TEST_EQUAL(3, binary_general(_1, 2)(1));
}
#endif

#endif
