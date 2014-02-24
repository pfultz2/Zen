/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    regular.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_REGULAR_H
#define ZEN_GUARD_FUNCTION_REGULAR_H

// @begin
// regular
// =======
// 
// Description
// -----------
// 
// The `regular` function adaptor makes a function default-constructible on
// functions that are only copy-constructible. A lot of times, this is necessary
// when using a lambda function. When its used inside of an iterator, it can be
// problematic, since an iterator needs to be default-constructed.
// 
// Just as dereferencing a default-constructed iterator is invalid, calling a
// default-constructed regular function is invalid as well.
// 
// Synopsis
// --------
// 
//     template<class F>
//     regular_adaptor<F> regular(F f);
// 
// @end

#include <boost/optional.hpp>

namespace zen { namespace detail {


template<class F>
struct regular_base
{
    boost::optional<F> f;

    typedef F function_type;

    regular_base()
    {}
    template<class X>
    regular_base(X f): f(f)
    {}

    regular_base(const regular_base & rhs) : f(rhs.f)
    {}

    const F& get_function() const
    {
        return *(this->f);
    }

    // Assignment operator is just a copy construction, which does not provide
    // the strong exception guarentee.
    regular_base& operator=(const regular_base& rhs)
    {
        if (this != &rhs)
        {
            this->~regular_base();
            new (this) regular_base(rhs);
        }
        return *this;
    }

    template<class... Ts>
    auto operator()(Ts &&... xs) const ZEN_RETURNS
    (this->get_function()(std::forward<Ts>(xs)...));
};
}

template<class F>
struct regular_adaptor : detail::regular_base<F>
{
    typedef detail::regular_base<F> base;
    regular_adaptor()
    {}

    template<class X>
    regular_adaptor(X x) : base(x)
    {}
};

template<class F>
regular_adaptor<F> regular(F f)
{
    return regular_adaptor<F>(f);
}

}

#ifdef ZEN_TEST
#include <zen/test.h>
#include <algorithm>
#include <boost/iterator/filter_iterator.hpp>


ZEN_TEST_CASE(regular_test)
{
    int a1[6] = {1,2,3,4,5,6};
    int a2[3] = {2,4,6};

    auto pred = zen::regular([](auto x) { return (x % 2) == 0; });
    decltype(pred) def_pred;
    def_pred = pred;

    ZEN_TEST_CHECK(
        std::equal(a2, a2+3,
            boost::make_filter_iterator(def_pred, a1, a1+6) )
    );
}

#endif

#endif
