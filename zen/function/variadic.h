/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    variadic.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_VARIADIC_H
#define ZEN_GUARD_FUNCTION_VARIADIC_H

// @begin
// variadic
// ========
// 
// Description
// -----------
// 
// The `variadic` function adaptor converts the arguments to the function to a
// tuple or fusion sequence.
// 
// Synopsis
// --------
// 
//     template<class F>
//     variadic_adaptor<F> variadic(F f);
// 
// @end

#include <zen/function/adaptor.h>
#include <zen/function/perfect.h>
#include <zen/function/result_of.h>
#include <zen/function/detail/nullary_tr1_result_of.h>

#include <zen/function/detail/sequence.h>

namespace zen { 

// TODO: move to another file
template<class T>
struct remove_rvalue_reference
: boost::mpl::eval_if<boost::is_rvalue_reference<T>, boost::remove_reference<T>, boost::mpl::identity<T> >
{};

#ifdef ZEN_TEST
// static_assert(!boost::is_rvalue_reference<typename remove_rvalue_reference<int&&>::type>::type::value, "Error");
static_assert(!boost::is_rvalue_reference<remove_rvalue_reference<int&>::type>::type::value, "Error");
static_assert(boost::is_lvalue_reference<remove_rvalue_reference<int&>::type>::type::value, "Error");
static_assert(!boost::is_rvalue_reference<remove_rvalue_reference<const int&>::type>::type::value, "Error");
static_assert(boost::is_lvalue_reference<remove_rvalue_reference<const int&>::type>::type::value, "Error");
// static_assert(boost::is_rvalue_reference<int&&>::type::value, "Error");
#endif

namespace detail {

#ifndef ZEN_NO_VARIADIC_TEMPLATES
template<class F>
struct variadic_adaptor_base : function_adaptor_base<F>
{
    typedef void zen_is_callable_by_result_tag;
    variadic_adaptor_base() {}

    template<class X>
    variadic_adaptor_base(X x) : function_adaptor_base<F>(x)
    {}

    template<class X>
    struct result;

    template<class X, class... T>
    struct result<X(T...)>
    : zen::result_of<F(ZEN_FUNCTION_SEQUENCE<typename tuple_reference<T>::type...>)> 
    {};

    template<class... T>
    typename zen::result_of<F(ZEN_FUNCTION_SEQUENCE<typename tuple_reference<T&&>::type...>)>::type
    operator()(T && ... x) const
    {   
        return this->get_function()(ZEN_FUNCTION_SEQUENCE<typename tuple_reference<T&&>::type...>(std::forward<T>(x)...));
    }

};
#else

#define ZEN_FUNCTION_VARIADIC_ADAPTOR(z, n, data) \
    template<class X BOOST_PP_COMMA_IF(n) ZEN_PP_PARAMS_Z(z, n, class T)> \
    struct result<X(ZEN_PP_PARAMS_Z(z, n, T))> \
    : zen::result_of<F(ZEN_FUNCTION_SEQUENCE<ZEN_PP_PARAMS_Z(z, n, typename tuple_reference<T, >::type BOOST_PP_INTERCEPT)>)> \
    {}; \
    ZEN_PP_WHEN(n)(template<ZEN_PP_PARAMS_Z(z, n, class T)>) \
    typename result<F(ZEN_PP_PARAMS_Z(z, n, T, ZEN_FORWARD_REF() BOOST_PP_INTERCEPT))>::type \
    operator()(ZEN_PP_PARAMS_Z(z, n, T, ZEN_FORWARD_REF() BOOST_PP_INTERCEPT, x)) const \
    { \
        return this->get_function()(ZEN_FUNCTION_SEQUENCE<ZEN_PP_PARAMS_Z(z, n, typename tuple_reference<T, ZEN_FORWARD_REF()>::type BOOST_PP_INTERCEPT)> \
            ( \
                ZEN_PP_PARAMS_Z(z, n, zen::forward<T, > BOOST_PP_INTERCEPT, (x)) \
            )); \
    }

template<class F, class Enable = void>
struct variadic_adaptor_base;

template<class F>
struct variadic_adaptor_base<F, ZEN_CLASS_REQUIRES(exclude is_callable<F(ZEN_FUNCTION_SEQUENCE<>)>)> 
: function_adaptor_base<F>
{
    typedef function_adaptor_base<F> base; 
    typedef void zen_is_callable_by_result_tag;
    variadic_adaptor_base() {}

    template<class X>
    variadic_adaptor_base(X x) : function_adaptor_base<F>(x)
    {}

    // MSVC Workarounds
    variadic_adaptor_base(const variadic_adaptor_base& rhs) : base(static_cast<const base&>(rhs))
    {}

    template<class X>
    struct result;

BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_PARAMS_LIMIT, ZEN_FUNCTION_VARIADIC_ADAPTOR, ~)

};

template<class F>
struct variadic_adaptor_base<F, ZEN_CLASS_REQUIRES(is_callable<F(ZEN_FUNCTION_SEQUENCE<>)>)> 
: function_adaptor_base<F>
{
     typedef function_adaptor_base<F> base; 
    typedef void zen_is_callable_by_result_tag;
    variadic_adaptor_base() {}

    template<class X>
    variadic_adaptor_base(X x) : function_adaptor_base<F>(x)
    {}

    // MSVC Workarounds
    variadic_adaptor_base(const variadic_adaptor_base& rhs) : base(static_cast<const base&>(rhs))
    {}

    template<class X>
    struct result;

BOOST_PP_REPEAT_FROM_TO_1(0, ZEN_PARAMS_LIMIT, ZEN_FUNCTION_VARIADIC_ADAPTOR, ~)

};
#endif
}

template<class F>
struct variadic_adaptor : ZEN_FUNCTION_PERFECT_ADAPTOR(detail::variadic_adaptor_base<F>)
{
    typedef ZEN_FUNCTION_PERFECT_ADAPTOR(detail::variadic_adaptor_base<F>) base;
    variadic_adaptor() {}

    template<class X>
    variadic_adaptor(X x) : base(x)
    {}

    // MSVC Workarounds
    variadic_adaptor(const variadic_adaptor& rhs): base(static_cast<const base&>(rhs))
    {}

    typename function_adaptor_type<F>::type get_function() const
    {
#ifdef ZEN_NO_RVALUE_REFS
        return this->base::get_function().get_function();
#else
        return this->base::get_function();
#endif
    }
};

template<class F>
variadic_adaptor<F> variadic(F f)
{
    return variadic_adaptor<F>(f);
}

}

ZEN_NULLARY_TR1_RESULT_OF_N(1, zen::variadic_adaptor)

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/detail/test.h>

typedef zen::variadic_adaptor<tuple_class> vard_class;

ZEN_TEST_CASE(variadic_test)
{
    ZEN_TEST_EQUAL(3, vard_class()(2));
}
#endif

#endif
