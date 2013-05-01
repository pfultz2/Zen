/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    is_callable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_IS_CALLABLE_H
#define ZEN_GUARD_IS_CALLABLE_H

// @begin
// is_callable
// ===========
// 
// Description
// -----------
// 
// The `is_callable` metafunction checks if the function object is callable with
// the certain parameters. It uses the same signature as `result_of`.
// 
// Note: On older compilers, sometimes `is_callable` produces a compile error due
// to using incomplete types. To workaround this, callability can be detected by
// using the nested `result` if its made to be SFINAE-friendly. Just add a nested
// `zen_is_callable_by_result_tag` to the function object.
// 
// Synopsis
// --------
// 
//     template<class Sig>
//     struct is_callable;
// 
// Example
// -------
// 
//     struct is_callable_class
//     {
//         void operator()(int) const
//         {
//         }
//     };
//     static_assert(is_callable<is_callable_class(int)>::type::value, "Not callable");
// 
// @end

#include <zen/config.h>
#include <zen/pp.h>
#include <zen/typeof.h>
#include <zen/forward.h>
#include <zen/static_assert.h>
#include <zen/traits.h>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/function_types/is_function.hpp>
#include <boost/function_types/is_function_pointer.hpp>

#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/is_nullary.hpp>

#ifdef ZEN_TEST
#include <zen/function/placeholders.h>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/statement/if.hpp>
#endif

#ifndef ZEN_IS_CALLABLE_LIMIT
#define ZEN_IS_CALLABLE_LIMIT 16
#endif

namespace zen {

template<class F>
struct is_callable;


#if defined(ZEN_NO_VARIADIC_TEMPLATES) || defined(ZEN_NO_EXPRESSION_SFINAE)
// is_callable from Eric Niebler
namespace callable_detail {
struct dont_care
{
    dont_care(...);
};

struct private_type
{
    private_type const &operator,(int) const;
};

typedef char yes_type;      // sizeof(yes_type) == 1
typedef char (&no_type)[2]; // sizeof(no_type)  == 2

template<typename T>
no_type is_private_type(T const &);

yes_type is_private_type(private_type const &);

template<int N, class Fun>
struct funwrap;


#define ZEN_FUNWRAP_BUILDER(z, n, data) \
template<class Fun> \
struct funwrap<n, Fun> : Fun \
{ \
    funwrap(); \
    typedef private_type const &(*pointer_to_function)(ZEN_PP_PARAMS_Z(z, n, dont_care BOOST_PP_INTERCEPT)); \
    operator pointer_to_function() const; \
};
BOOST_PP_REPEAT_1(16, ZEN_FUNWRAP_BUILDER, ~)
#undef ZEN_FUNWRAP_BUILDER

BOOST_MPL_HAS_XXX_TRAIT_DEF(zen_is_callable_by_result_tag)

template<class F, class Enable = void>
struct is_callable_fo;

#define ZEN_IS_CALLABLE_FO_BY_RESULT(z, n, data) \
template<class Fun BOOST_PP_COMMA_IF(n) ZEN_PP_PARAMS_Z(z, n, class T)> \
struct is_callable_fo<Fun(ZEN_PP_PARAMS_Z(z, n, T)), ZEN_CLASS_REQUIRES(has_zen_is_callable_by_result_tag<Fun>)> \
: has_type<typename Fun::template result<Fun(ZEN_PP_PARAMS_Z(z, n, T))> > \
{};
BOOST_PP_REPEAT_1(ZEN_IS_CALLABLE_LIMIT, ZEN_IS_CALLABLE_FO_BY_RESULT, ~)

#define ZEN_IS_CALLABLE_FO(z, n, data) \
template<class Fun BOOST_PP_COMMA_IF(n) ZEN_PP_PARAMS_Z(z, n, class T)> \
struct is_callable_fo<Fun(ZEN_PP_PARAMS_Z(z, n, T)), ZEN_CLASS_REQUIRES(exclude has_zen_is_callable_by_result_tag<Fun>)> \
{ \
    static funwrap<n, Fun> & fun; \
    ZEN_PP_GEN_Z(z, n, static typename add_forward_reference<T, >::type BOOST_PP_INTERCEPT, x, ; BOOST_PP_INTERCEPT) \
    static bool const value = \
    (\
        sizeof(no_type) == sizeof(is_private_type( (fun(ZEN_PP_PARAMS_Z(z, n, x)), 0) )) \
    ); \
    typedef boost::mpl::bool_<value> type; \
};
BOOST_PP_REPEAT_1(ZEN_IS_CALLABLE_LIMIT, ZEN_IS_CALLABLE_FO, ~)

template<class F, class G>
struct is_callable_fp
: boost::mpl::bool_<false>
{};
#define ZEN_IS_CALLABLE_FP(z, n, data) \
template<class Fun BOOST_PP_COMMA_IF(n) ZEN_PP_PARAMS_Z(z, n, class T), \
         class Res BOOST_PP_COMMA_IF(n) ZEN_PP_PARAMS_Z(z, n, class U)> \
struct is_callable_fp<Fun(ZEN_PP_PARAMS_Z(z, n, T)), Res(*)(ZEN_PP_PARAMS_Z(z, n, U))> \
{ \
    static bool const value = \
        (true ZEN_PP_GEN_Z(z, n, && boost::is_convertible<T, ZEN_PP_INTERCEPT_COMMA, U, >::value BOOST_PP_INTERCEPT)); \
    typedef boost::mpl::bool_<value> type; \
};
BOOST_PP_REPEAT_1(ZEN_IS_CALLABLE_LIMIT, ZEN_IS_CALLABLE_FP, ~)

}

#define ZEN_IS_CALLABLE_BUILDER(z, n, data) \
template<class Fun BOOST_PP_COMMA_IF(n) ZEN_PP_PARAMS_Z(z, n, class T)> \
struct is_callable<Fun(ZEN_PP_PARAMS_Z(z, n, T))> \
: boost::mpl::eval_if<boost::function_types::is_function_pointer<Fun>, \
                    callable_detail::is_callable_fp<Fun(ZEN_PP_PARAMS_Z(z, n, T)), Fun>, \
                    callable_detail::is_callable_fo<Fun(ZEN_PP_PARAMS_Z(z, n, T))> >::type \
{};
BOOST_PP_REPEAT_1(ZEN_IS_CALLABLE_LIMIT, ZEN_IS_CALLABLE_BUILDER, ~)

#else

template<class F, class... Args>
struct is_callable<F(Args...)>
{
    typedef char yes;
    typedef char (&no)[2];
    template<class T> 
    struct selector {}; 

    template<class U> 
    static yes check( selector<decltype( zen::declval<U>()(zen::declval<Args>()...) )> * ); 

    template<class U> 
    static no check(...); 
    
    static const bool value = sizeof(check<F>(0)) == sizeof(yes); 

    typedef boost::mpl::bool_<value> type; 
};

#endif

// Workaround for Boost.Phoenix
template<class Expr>
struct is_callable<boost::phoenix::actor<Expr>()>
: boost::phoenix::result_of::is_nullary<Expr>
{};

#ifdef ZEN_TEST
struct is_callable_class
{
    void operator()(int) const
    {
    }
};
struct callable_test_param {};

void is_callable_function(int)
{
}
// using zen::ph::_1;
template<class F>
void phoenix_not_nullary_check(F)
{
    static_assert(!is_callable<F()>::type::value, "Callable failed");
}

inline void callable_test()
{
    phoenix_not_nullary_check(zen::ph::_1 + 1);
}
// typedef is_callable<is_callable_class(int)>::type is_callable_test;
static_assert(is_callable<is_callable_class(int)>::type::value, "Not callable");
static_assert(is_callable<is_callable_class(const int&)>::type::value, "Not callable");
static_assert(not is_callable<is_callable_class(callable_test_param)>::type::value, "callable failed");
static_assert(not is_callable<is_callable_class()>::type::value, "callable failed");
static_assert(not is_callable<is_callable_class(int, int)>::type::value, "callable failed");

typedef void (*is_callable_function_pointer)(int);
static_assert(boost::function_types::is_function_pointer<is_callable_function_pointer>::value, "Not callable");
// typedef boost::mpl::identity<is_callable_function_pointer>::type is_callable_function_type;
// typedef is_callable<is_callable_function_pointer(int)>::type is_callable_test;
static_assert(is_callable<is_callable_function_pointer(int)>::type::value, "Not callable");
static_assert(is_callable<is_callable_function_pointer(const int&)>::type::value, "Not callable");
static_assert(not is_callable<is_callable_function_pointer(callable_test_param)>::type::value, "callable failed");
static_assert(not is_callable<is_callable_function_pointer()>::type::value, "callable failed");
static_assert(not is_callable<is_callable_function_pointer(int, int)>::type::value, "callable failed");

#endif


}

#endif
