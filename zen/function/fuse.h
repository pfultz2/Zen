/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    fuse.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_FUSE_H
#define ZEN_GUARD_FUNCTION_FUSE_H

// @begin
// fuse
// ====
// 
// Description
// -----------
// 
// The `fuse` function adaptor takes a fusion sequence and uses that for the
// arguments to the function.
// 
// Synopsis
// --------
// 
//     template<class F>
//     fuse_adaptor<F> fuse(F f);
// 
// Example
// -------
// 
//     struct sum
//     {
//         template<class T>
//         T sum(T x, T y)
//         {
//             return x+y;
//         }
//     };
// 
//     int r = fuse(sum())(boost::fusion::make_vector(3,2));
//     assert(r, 5);
// 
// @end

#include <zen/function/invoke.h>
#include <zen/function/variadic.h> 

namespace zen {

template<class F>
struct fuse_adaptor : F
{
    template<class... Ts>
    fuse_adaptor(Ts && ... x) : F(std::forward<Ts>(x)...)
    {}

    const F& base_function() const
    {
        return *this;
    }
#ifdef _MSC_VER
    // MSVC Workarounds
    fuse_adaptor(const fuse_adaptor& rhs) : F(static_cast<const F&>(rhs))
    {} 
#endif

    template<class T>
    auto operator()(T && x) const
    ZEN_RETURNS(zen::invoke(this->base_function(), std::forward<T>(x)));
};

// Optimizations
template<class F>
struct fuse_adaptor<variadic_adaptor<F> > : F
{
    template<class... Ts>
    fuse_adaptor(Ts && ... x) : F(std::forward<Ts>(x)...)
    {}

    const F& base_function() const
    {
        return *this;
    }
#ifdef _MSC_VER
    // MSVC Workarounds
    fuse_adaptor(const fuse_adaptor& rhs) : F(static_cast<const F&>(rhs))
    {} 
#endif
};

template<class F>
struct variadic_adaptor<fuse_adaptor<F> > : F
{
    template<class... Ts>
    variadic_adaptor(Ts && ... x) : F(std::forward<Ts>(x)...)
    {}

    const F& base_function() const
    {
        return *this;
    }
#ifdef _MSC_VER
    // MSVC Workarounds
    variadic_adaptor(const variadic_adaptor& rhs) : F(static_cast<const F&>(rhs))
    {} 
#endif
};

template<class F>
fuse_adaptor<F> fuse(F f)
{
    return fuse_adaptor<F>(f);
}

}


#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/detail/test.h>
#include <zen/function/static.h>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>

zen::static_<zen::fuse_adaptor<unary_class> > unary_fuse = {};

ZEN_TEST_CASE(fuse_test)
{
    int ifu = 3;
    ZEN_TEST_EQUAL(3, zen::fuse(unary_class())(boost::fusion::make_vector(3)));
    ZEN_TEST_EQUAL(3, unary_fuse(boost::fusion::make_vector(3)));
    ZEN_TEST_EQUAL(3, unary_fuse(boost::fusion::vector<int&>(ifu)));
}
#endif

#endif
