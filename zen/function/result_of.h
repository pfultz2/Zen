/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    result_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RESULT_OF_H
#define ZEN_GUARD_RESULT_OF_H

// @begin
// result_of
// =========
// 
// Description
// -----------
// 
// The `result_of` metafunction returns the the return of a polymorphic function
// object. This works like `boost::result_of` except its SFINAE-friendly(meaning
// there is no nested type when the function object is not callable) even on
// C++03 compilers as well.
// 
// Synopsis
// --------
// 
//     template<class Sig>
//     struct result_of;
// 
// @end

#include <zen/function/is_callable.h>
#include <zen/requires.h>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/has_xxx.hpp>

#include <boost/type_traits/is_same.hpp>

namespace zen {

namespace detail {

template<class F>
struct result_check : boost::mpl::bool_<true>
{
};

template<class T1, class T2>
struct result_assert
{
    typedef typename boost::is_convertible<T1, T2>::type type;
    static_assert(type::value, "result_of protocol has incorrect return type");
};

#ifndef ZEN_NO_VARIADIC_TEMPLATES
template<class F, class... T>
struct result_check<F(T...)>
: result_assert
< 
    ZEN_XTYPEOF_TPL(zen::declval<F>()(zen::declval<T>()...)),
    typename boost::result_of<F(T...)>::type
>
{
};

#else

#define ZEN_RESULT_OF_CHECK(z, n, data) \
template<class F BOOST_PP_COMMA_IF(n) ZEN_PP_PARAMS_Z(z, n, class T)> \
struct result_check<F(ZEN_PP_PARAMS_Z(z, n, T))> \
: result_assert \
<  \
    ZEN_XTYPEOF_TPL( zen::declval<F>()(ZEN_PP_PARAMS_Z(z, n, zen::declval<T, >() BOOST_PP_INTERCEPT)) ), \
    typename boost::result_of<F(ZEN_PP_PARAMS_Z(z, n, T))>::type \
> \
{};
BOOST_PP_REPEAT_1(ZEN_PARAMS_LIMIT, ZEN_RESULT_OF_CHECK, ~)

#endif

// Retrieve function type
template<class Sig>
struct get_result_function;

#ifndef ZEN_NO_VARIADIC_TEMPLATES

template<class F, class... T>
struct get_result_function<F(T...)>
{
    typedef F type;
};

#else

#define ZEN_RESULT_OF_GET_RESULT_FUNCTION_GENERATE(z, n, data) \
template<class F BOOST_PP_COMMA_IF(n) ZEN_PP_PARAMS_Z(z, n, class T)> \
struct get_result_function<F(ZEN_PP_PARAMS_Z(z, n, T))> \
{ \
   typedef F type; \
};
BOOST_PP_REPEAT_1(ZEN_PARAMS_LIMIT, ZEN_RESULT_OF_GET_RESULT_FUNCTION_GENERATE, ~)
#undef ZEN_RESULT_OF_GENERATE

#endif


BOOST_MPL_HAS_XXX_TEMPLATE_DEF(result);
BOOST_MPL_HAS_XXX_TRAIT_DEF(type);

template<class T>
struct has_valid_type
{
    typedef typename has_type<T>::type type;
};

template<class Sig, class F=typename get_result_function<Sig>::type, class Enable = void>
struct has_valid_result;

template<class Sig, class F>
struct has_valid_result<Sig, F, ZEN_CLASS_REQUIRES(has_result<F>)>
// : boost::mpl::bool_<true>
: has_type<typename F::template result<Sig> >
{};

template<class Sig, class F>
struct has_valid_result<Sig, F, ZEN_CLASS_REQUIRES(exclude has_result<F>)>
: boost::mpl::bool_<false>
{};


template<class Sig, class F>
struct inner_result
: F::template result<Sig>
{};

template<class Sig, class Enable = void>
struct result_of_impl;

template<class Sig>
struct result_of_impl<Sig, ZEN_CLASS_REQUIRES(is_callable<Sig>, has_valid_result<Sig>)>
: inner_result<Sig, typename get_result_function<Sig>::type> 
{};

template<class Sig>
struct result_of_impl<Sig, ZEN_CLASS_REQUIRES(is_callable<Sig>, exclude has_valid_result<Sig>)>
: boost::result_of<Sig> 
{};

template<class Sig>
struct result_of_impl<Sig, ZEN_CLASS_REQUIRES(exclude is_callable<Sig>)>
{};

}

template<class Sig, class F=void, class Enable=void>
struct result_of;

template<class Sig>
struct result_of<Sig, void, void>
: detail::result_of_impl<Sig>
{};

#ifndef ZEN_NO_VARIADIC_TEMPLATES

template<class F, class X, class... T>
struct result_of<F(T...), X, ZEN_CLASS_REQUIRES(exclude boost::is_void<X>)>
: detail::result_of_impl<X(T...)>
{};

#else

#define ZEN_RESULT_OF_GENERATE(z, n, data) \
template<class F, class X BOOST_PP_COMMA_IF(n) ZEN_PP_PARAMS_Z(z, n, class T)> \
struct result_of<F(ZEN_PP_PARAMS_Z(z, n, T)), X, ZEN_CLASS_REQUIRES(exclude boost::is_void<X>)> \
: detail::result_of_impl<X(ZEN_PP_PARAMS_Z(z, n, T))> \
{ \
};
BOOST_PP_REPEAT_1(ZEN_PARAMS_LIMIT, ZEN_RESULT_OF_GENERATE, ~)
#undef ZEN_RESULT_OF_GENERATE

#endif

#ifdef ZEN_TEST
namespace result_of_test {
    
struct no_result
{};

struct has_result
{
    template<class>
    struct result;

    template<class X, class T>
    struct result<X(T)>
    {
        typedef typename boost::decay<T>::type type;
    };

    template<class T>
    T operator()(T) const;
};


static_assert(!zen::detail::has_valid_result<no_result(int)>::value, "No result detection");
static_assert(!zen::detail::has_valid_result<has_result(int, int)>::value, "No result detection");
static_assert(zen::detail::has_valid_result<has_result(int)>::value, "No result detection");
ZEN_STATIC_ASSERT_SAME(zen::detail::get_result_function<has_result(int)>::type, has_result);
ZEN_STATIC_ASSERT_SAME(zen::detail::inner_result<has_result(int), has_result>::type, int);
ZEN_STATIC_ASSERT_SAME(zen::result_of<has_result(int)>::type, int);
}
#endif

}





#endif
