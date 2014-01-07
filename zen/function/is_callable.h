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
// #include <zen/pp.h>
#include <utility>
#include <boost/mpl/bool.hpp>
// #include <zen/typeof.h>
// #include <zen/forward.h>
// #include <zen/static_assert.h>
// #include <zen/traits.h>
// #include <boost/mpl/eval_if.hpp>
// #include <boost/type_traits.hpp>
// #include <boost/function_types/is_function.hpp>
// #include <boost/function_types/is_function_pointer.hpp>

// #include <boost/phoenix/core/actor.hpp>
// #include <boost/phoenix/core/is_nullary.hpp>

// #ifdef ZEN_TEST
// #include <zen/function/placeholders.h>
// #include <boost/phoenix/operator.hpp>
// #include <boost/phoenix/core.hpp>
// #include <boost/phoenix/statement/if.hpp>
// #endif


namespace zen {

template<class F>
struct is_callable;

// TODO: Use integral constants instead
template<class F, class... Args>
struct is_callable<F(Args...)>
{
    typedef char yes;
    typedef char (&no)[2];
    template<class T> 
    struct selector {}; 

    template<class U> 
    static yes check( selector<decltype( std::declval<U>()(std::declval<Args>()...) )> * ); 

    template<class U> 
    static no check(...); 
    
    static const bool value = sizeof(check<F>(0)) == sizeof(yes); 

    typedef boost::mpl::bool_<value> type; 
};

#ifdef ZEN_TEST
namespace detail_test {
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
// template<class F>
// void phoenix_not_nullary_check(F)
// {
//     static_assert(!is_callable<F()>::type::value, "Callable failed");
// }

// inline void callable_test()
// {
//     phoenix_not_nullary_check(zen::ph::_1 + 1);
// }
// typedef is_callable<is_callable_class(int)>::type is_callable_test;
static_assert(is_callable<is_callable_class(int)>::type::value, "Not callable");
static_assert(is_callable<is_callable_class(const int&)>::type::value, "Not callable");
static_assert(not is_callable<is_callable_class(callable_test_param)>::type::value, "callable failed");
static_assert(not is_callable<is_callable_class()>::type::value, "callable failed");
static_assert(not is_callable<is_callable_class(int, int)>::type::value, "callable failed");

typedef void (*is_callable_function_pointer)(int);
// static_assert(boost::function_types::is_function_pointer<is_callable_function_pointer>::value, "Not callable");
// typedef boost::mpl::identity<is_callable_function_pointer>::type is_callable_function_type;
// typedef is_callable<is_callable_function_pointer(int)>::type is_callable_test;
static_assert(is_callable<is_callable_function_pointer(int)>::type::value, "Not callable");
static_assert(is_callable<is_callable_function_pointer(const int&)>::type::value, "Not callable");
static_assert(not is_callable<is_callable_function_pointer(callable_test_param)>::type::value, "callable failed");
static_assert(not is_callable<is_callable_function_pointer()>::type::value, "callable failed");
static_assert(not is_callable<is_callable_function_pointer(int, int)>::type::value, "callable failed");
}
#endif


}

#endif
