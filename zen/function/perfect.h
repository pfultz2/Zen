/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    perfect.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_PERFECT_H
#define ZEN_GUARD_FUNCTION_PERFECT_H

// @begin
// perfect
// =======
// 
// Description
// -----------
// 
// The `perfect` function adaptor emulates perfect forwarding on older compilers.
// On C++11, it uses reference collapsing. Just define your parameter for `T` as
// `ZEN_FORWARD_REF(T)`. In C++11 because of reference collapsing, `T` can be a
// reference, however, in C++03, althought a variable is passed to a function by
// reference, `T` itself won't ever be a reference, but could be const or non-
// const. Also on C++03, rvalues are passed in as const references. So its just
// near-perfect forwarding on C++03.
// 
// Synopsis
// --------
// 
//     template<class F>
//     perfect_adaptor<F> perfect(F f);
// 
// @end

#include <zen/function/adaptor.h>
#include <zen/function/result_of.h>
#include <zen/function/detail/nullary_tr1_result_of.h>

#if !defined(ZEN_NO_VARIADIC_TEMPLATES) && !defined(ZEN_NO_RVALUE_REFS)
#include <zen/function/detail/c11/perfect_facade.h>
#elif !defined(ZEN_NO_RVALUE_REFS)
#include <zen/function/detail/msvc/perfect_facade.h>
#else
#include <zen/function/detail/c03/perfect_facade.h>
#endif

namespace zen {


// TODO: Add support for forwarding nullary functions as well
#ifndef ZEN_NO_VARIADIC_TEMPLATES
template<class F>
struct perfect_adaptor
: function_adaptor_base<F>
{
    typedef void zen_is_callable_by_result_tag;
    perfect_adaptor() {}

    template<class X>
    perfect_adaptor(X x) : function_adaptor_base<F>(x)
    {}

    template<class S>
    struct result
    : zen::result_of<S, F>
    {};

    ZEN_PERFECT_FACADE(F, this->get_function())
};

#else

template<class F, class Enable = void>
struct perfect_adaptor;

template<class F>
struct perfect_adaptor<F, ZEN_CLASS_REQUIRES(exclude is_callable<F()>)>
: function_adaptor_base<F>
{
    typedef function_adaptor_base<F> base;
    typedef void zen_is_callable_by_result_tag;
    perfect_adaptor() {}

    template<class X>
    perfect_adaptor(X x) : base(x)
    {}

    // MSVC Workarounds
    perfect_adaptor(const perfect_adaptor& rhs) : base(static_cast<const base&>(rhs))
    {}

    template<class S>
    struct result
    : zen::result_of<S, F>
    {};

    ZEN_PERFECT_FACADE(F, this->get_function())
};

template<class F>
struct perfect_adaptor<F, ZEN_CLASS_REQUIRES(is_callable<F()>)>
: function_adaptor_base<F>
{
    typedef function_adaptor_base<F> base;
    typedef void zen_is_callable_by_result_tag;
    perfect_adaptor() {}

    template<class X>
    perfect_adaptor(X x) : base(x)
    {}

    // MSVC Workarounds
    perfect_adaptor(const perfect_adaptor& rhs) : base(static_cast<const base&>(rhs))
    {}

    template<class S>
    struct result
    : zen::result_of<S, F>
    {};

    typename zen::result_of<F()>::type operator()() const
    {
        return this->get_function()();
    }

    ZEN_PERFECT_FACADE(F, this->get_function())
};
#endif

template<class F>
perfect_adaptor<F> perfect(F f)
{
    return perfect_adaptor<F>(f);
}

}

ZEN_NULLARY_TR1_RESULT_OF_N(1, zen::perfect_adaptor)


#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/detail/test.h>

typedef zen::perfect_adaptor<binary_class> binary_perfect;
typedef zen::perfect_adaptor<void_class> void_perfect;
typedef zen::perfect_adaptor<mono_class> mono_perfect;

ZEN_TEST_CASE(perfect_test)
{
    void_perfect()(1);
    ZEN_TEST_EQUAL(3, binary_perfect()(1, 2));
    ZEN_TEST_EQUAL(3, mono_perfect()(2));
}
#endif

#endif
