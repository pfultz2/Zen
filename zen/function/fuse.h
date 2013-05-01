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

#include <zen/function/adaptor.h>
#include <zen/function/perfect.h>
#include <zen/function/variadic.h>
#include <zen/function/invoke.h>
#include <zen/function/detail/nullary_tr1_result_of.h>

namespace zen {

template<class F>
struct fuse_adaptor : function_adaptor_base<F>
{
    typedef void zen_is_callable_by_result_tag;
    fuse_adaptor() {};

    template<class X>
    fuse_adaptor(X x) : function_adaptor_base<F>(x)
    {};

    template<class X, class Enable = void>
    struct result;

    template<class X, class T>
    struct result<X(T), ZEN_CLASS_REQUIRES(boost::fusion::traits::is_sequence<typename boost::decay<T>::type>)>
    : invoke_result<F, const typename boost::decay<T>::type&> 
    {}; 

    template<class T>
    typename result<F(const T&)>::type operator()(const T & x) const
    {
        return invoke(this->get_function(), x);
    }
};

// Optimizations
template<class F>
struct fuse_adaptor<variadic_adaptor<F> > : perfect_adaptor<F>
{
    fuse_adaptor() {};

    template<class X>
    fuse_adaptor(X x) : perfect_adaptor<F>(x)
    {};
};

template<class F>
struct variadic_adaptor<fuse_adaptor<F> > : perfect_adaptor<F>
{
    variadic_adaptor() {};

    template<class X>
    variadic_adaptor(X x) : perfect_adaptor<F>(x)
    {};
};

template<class F>
fuse_adaptor<F> fuse(F f)
{
    return fuse_adaptor<F>(f);
}

}

ZEN_NULLARY_TR1_RESULT_OF_N(1, zen::fuse_adaptor)


#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/detail/test.h>
#include <zen/function/static.h>

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
