/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    builder.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

// @begin
// Function Builder
// ================
// 
// Introduction
// ------------
// 
// The function builder provides a plugin for ZLang to make it easier to define
// polymorphic functions. Say, for instance, we want to define a simple generic
// sum function, we can define it like this:
// 
//     $(function(sum)(x, y)(x + y));
// 
// The return type is automatically deduced from the expression(ie `x + y`). The
// types for the `x` and `y` variables are deduced from whats passed into the
// function. However, with this function everything is passed in by value. The
// best way to avoid copying is to use perfect forwarding, which will accept an
// const reference, non-const reference, or an rvalue reference(in C++11). To do
// this we add the `auto` keyword to the parameters like this:
// 
//     $(function(sum)(auto x, auto y)(x + y));
// 
// Now perhaps, we would like to restrict the sum to just integers. We can add an
// `if` clause to the function as well:
// 
//     $(function(sum)(auto x, auto y) if (is_integral<x>, is_integral<y>)(x + y));
// 
// The `if` clause uses the same syntax as the requires clauses do. We can also
// use an `else` to add more overloads, if the first one fails. So perhaps we
// want to call `float_sum` function if they are floats, we can do this like
// this:
// 
//     $(function(sum)(auto x, auto y) 
//         if (is_integral<x>, is_integral<y>)(x + y)
//         else if (is_float<x>, is_float<y>)(float_sum(x, y))
//     );
// 
// Finally, we can also add `else` without using an `if` clause. Say for
// instance, we just want to print a message to the user if the sum is not an
// integer nor a float:
// 
//     $(function(sum)(auto x, auto y) 
//         if (is_integral<x>, is_integral<y>)(x + y)
//         else if (is_float<x>, is_float<y>)(float_sum(x, y))
//         else (printf("No sum for you\n"))
//     );
// 
// Types
// -----
// 
// By default, the function builder builds a function object, but if a class is
// all thats needed then the class keyword can be used like this:
// 
//      $(function class(sum_t)(x, y)(x + y));
// 
// And a class named `sum_t` will be created, that can be called like a function,
// like this:
// 
//     int i = sum_t()(1 + 2); // i = 3
// 
// Also, pipable functions can be built by using the `pipe` keyword:
// 
//      $(function pipe(sum)(x, y)(x + y));
// 
// Then the function can be called like this:
// 
//     int i = 1 | sum(2); // i = 3
// 
// Parameters
// ----------
// 
// The parameters to a function can accept parameters by value, by non-const
// reference, by const reference, and by perfect reference(which is either const,
// non-const, or an rvalue if supported). By default, without any keywords the
// parameters are taken by value:
// 
//     $(function(sum)(x, y)(x + y));
// 
// To use non-const references, use `mutable`:
// 
//     $(function(sum)(mutable x, mutable y)(x + y));
// 
// To use const references, use `const`:
// 
//     $(function(sum)(const x, const y)(x + y));
// 
// To do perfect forwarding, use `auto`:
// 
//     $(function(sum)(auto x, auto y)(x + y));
// 
// Traits
// ------
// 
// Traits can be given to a function to restrict valid overloads for that
// function by using the `if` clause:
// 
//     $(function(sum)(x, y) if (is_integral<x>, is_integral<y>)(x + y));
// 
// In the `if` clause, the `x` and `y` are types to the corresponding parameters.
// The types for The `if` clause uses the same syntax as the requires clauses do.
// So multiple traits given are inclusive, unless the `exclude` keyword is used.
// So, for example, if we want to further restrict the `sum` function to exlude
// booleans, we could write this:
// 
//     $(function(sum)(x, y) 
//         if (is_integral<x>, is_integral<y>, exclude is_same<x, bool>, exclude is_same<y, bool>)(x + y)
//     );
// 
// The `else` clause lets more overloads be added if the previous traits failed. 
// 
//     $(function(sum)(x, y) 
//         if (is_integral<x>, is_integral<y>, exclude is_same<x, bool>, exclude is_same<y, bool>)(x + y)
//         else (printf("No sum for you\n"))
//     );
// 
// The overloads for `else` clauses are process in order, so there aren't
// ambiguities like with C++ overload resolution. So this is perfectly valid:
// 
//     $(function(sum)(x, y) 
//         if (is_integral<x>, is_integral<y>)(x + y)
//         else if (is_float<x>, is_float<y>)(float_sum(x, y))
//     );
// 
// And won't cause an ambiguity, nor does it require using excludes.
// 
// Overloads
// ---------
// 
// If multiple overloads with a different number of parameters are needed, then
// the `def` keyword can be used:
// 
//     $(function(sum)(x, y)(x + y)
//                 def(x, y, z)(x + y + z)
//     );
// 
// Each additional overload uses C++ standard overload resolution to find the
// function. So ambiguities must be avoided.
// 
// @end

#ifndef ZEN_GUARD_FUNCTION_BUILDER_H
#define ZEN_GUARD_FUNCTION_BUILDER_H

#include <zen/function/conditional.h>
#include <zen/function/pipable.h>
#include <zen/function/overload.h>
#include <zen/function/fix.h>
#include <zen/traits/ax.h>
#include <zen/pp.h>

#ifndef ZEN_PP_STRING_if
#define ZEN_PP_STRING_if (if)
#endif

#ifndef ZEN_PP_STRING_else
#define ZEN_PP_STRING_else (else)
#endif

#ifndef ZEN_PP_COMPARE_else
#define ZEN_PP_COMPARE_else(x) x
#endif

#ifndef ZEN_PP_STRING_def
#define ZEN_PP_STRING_def (def)
#endif

#ifndef ZEN_PP_COMPARE_def
#define ZEN_PP_COMPARE_def(x) x
#endif

#define ZEN_FUNCTION_PARAM(x) BOOST_PP_CAT(ZEN_FUNCTION_PARAM_, x)
#define ZEN_FUNCTION_PARAM_const (const)
#define ZEN_FUNCTION_PARAM_auto (())

#define ZEN_FUNCTION_PARAM_IF_PARAM(x, t, f, data) ZEN_DETAIL_FUNCTION_IF_PARAM(ZEN_FUNCTION_PARAM(x), x, t, f, data)
#define ZEN_DETAIL_FUNCTION_IF_PARAM(x, y, t, f, data) BOOST_PP_IIF(ZEN_PP_IS_PAREN(x), t, f)(x, y, data)

#define ZEN_FUNCTION_PARAM_REPLACE_ID() ZEN_FUNCTION_PARAM_REPLACE

#define ZEN_FUNCTION_PARAM_REPLACE(x, T) ZEN_FUNCTION_PARAM_IF_PARAM(x, ZEN_DETAIL_FUNCTION_PARAM_REPLACE_TRUE, ZEN_DETAIL_FUNCTION_PARAM_REPLACE_FALSE, T)
#define ZEN_DETAIL_FUNCTION_PARAM_REPLACE_TRUE(x, y, T) ZEN_DETAIL_FUNCTION_PARAM_REPLACE_TRUE_I(ZEN_PP_TYPEOF(x), ZEN_PP_STRIP(x), T)
#define ZEN_DETAIL_FUNCTION_PARAM_REPLACE_TRUE_I(head, tail, T) \
    BOOST_PP_IIF(ZEN_PP_IS_PAREN(head), ZEN_DETAIL_FUNCTION_PARAM_REPLACE_END, ZEN_DETAIL_FUNCTION_PARAM_REPLACE_CONT)(head, tail, T)
#define ZEN_DETAIL_FUNCTION_PARAM_REPLACE_END(head, tail, T) T tail
#define ZEN_DETAIL_FUNCTION_PARAM_REPLACE_CONT(head, tail, T) head ZEN_PP_DEFER(ZEN_FUNCTION_PARAM_REPLACE_ID)()(tail, T)
#define ZEN_DETAIL_FUNCTION_PARAM_REPLACE_FALSE(x, y, T) y

#define ZEN_FUNCTION_PARAM_TEMPLATE_ID() ZEN_FUNCTION_PARAM_TEMPLATE

#define ZEN_FUNCTION_PARAM_TEMPLATE(x, T) ZEN_FUNCTION_PARAM_IF_PARAM(x, ZEN_DETAIL_FUNCTION_PARAM_TEMPLATE_TRUE, ZEN_DETAIL_FUNCTION_PARAM_TEMPLATE_FALSE, T)
#define ZEN_DETAIL_FUNCTION_PARAM_TEMPLATE_TRUE(x, y, T) ZEN_DETAIL_FUNCTION_PARAM_TEMPLATE_TRUE_I(ZEN_PP_TYPEOF(x), ZEN_PP_STRIP(x), T)
#define ZEN_DETAIL_FUNCTION_PARAM_TEMPLATE_TRUE_I(head, tail, T) \
    BOOST_PP_IIF(ZEN_PP_IS_PAREN(head), ZEN_DETAIL_FUNCTION_PARAM_TEMPLATE_END, ZEN_DETAIL_FUNCTION_PARAM_TEMPLATE_CONT)(head, tail, T)
#define ZEN_DETAIL_FUNCTION_PARAM_TEMPLATE_END(head, tail, T) (class T)
#define ZEN_DETAIL_FUNCTION_PARAM_TEMPLATE_CONT(head, tail, T) ZEN_PP_DEFER(ZEN_FUNCTION_PARAM_TEMPLATE_ID)()(tail, T)
#define ZEN_DETAIL_FUNCTION_PARAM_TEMPLATE_FALSE(x, y, T)

#define ZEN_PP_SEQ_FOR_EACH_ID() BOOST_PP_SEQ_FOR_EACH_I
#define ZEN_PP_SEQ_FOR_EACH_I_R_ID() BOOST_PP_SEQ_FOR_EACH_I_R

#define ZEN_FUNCTION_PARAM_TEMPLATE_ARGS(r, seq, T) ZEN_PP_DEFER(ZEN_PP_SEQ_FOR_EACH_I_R_ID)()(r, ZEN_FUNCTION_PARAM_TEMPLATE_ARGS_EACH, T, seq) 
#define ZEN_FUNCTION_PARAM_TEMPLATE_ARGS_EACH(r, T, i, elem) ZEN_FUNCTION_PARAM_TEMPLATE(elem, T ## i)

#define ZEN_FUNCTION_PARAM_REPLACE_AUTO(r, seq, T) ZEN_PP_DEFER(ZEN_PP_SEQ_FOR_EACH_I_R_ID)()(r, ZEN_FUNCTION_PARAM_REPLACE_AUTO_EACH, T, seq) 
#define ZEN_FUNCTION_PARAM_REPLACE_AUTO_EACH(r, T, i, elem) (ZEN_FUNCTION_PARAM_REPLACE(elem, T ## i))


#define ZEN_DETAIL_FUNCTION_CLASS_K_REQ(reqs) , ZEN_PARAM_REQUIRES(reqs)
#define ZEN_DETAIL_FUNCTION_CLASS_K(name, n, t_params, f_params, reqs, body) \
struct name \
{ \
    template<BOOST_PP_SEQ_ENUM(t_params)> \
    decltype(auto) \
    operator()(BOOST_PP_SEQ_ENUM(f_params) \
        BOOST_PP_IIF(ZEN_PP_IS_PAREN(reqs), ZEN_DETAIL_FUNCTION_CLASS_K_REQ, ZEN_PP_EAT)(ZEN_PP_REM reqs) \
            ) const \
    { return body; } \
};

// TODO: Add support for bodies without double parenthesis, so you can write:
// ZEN_FUNCTIONS_CLASS((foo)(x, y) x + y)
#define ZEN_DETAIL_FUNCTION_CLASS_GEN(name, n, t_params, f_params, body) \
BOOST_PP_CAT(ZEN_DETAIL_FUNCTION_CLASS_GEN_, BOOST_PP_SEQ_SIZE(body))\
(name, n, t_params, f_params, body)
#define ZEN_DETAIL_FUNCTION_CLASS_GEN_1(name, n, t_params, f_params, body) \
ZEN_DETAIL_FUNCTION_CLASS_K(name, n, t_params, f_params,, BOOST_PP_SEQ_HEAD(body))
#define ZEN_DETAIL_FUNCTION_CLASS_GEN_3(name, n, t_params, f_params, body) \
ZEN_DETAIL_FUNCTION_CLASS_K(name, n, t_params, f_params, BOOST_PP_SEQ_ELEM(1, body), BOOST_PP_SEQ_ELEM(2, body))

//
// Conditional adaptor
//
#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_EACH(r, data, i, x) ZEN_DETAIL_FUNCTION_CLASS_INVOKE((i, ZEN_PP_REM data, x))
#ifndef _MSC_VER
#define ZEN_DETAIL_FUNCTION_CLASS_INVOKE(x) ZEN_DETAIL_FUNCTION_CLASS_OP x
#else
#define ZEN_DETAIL_FUNCTION_CLASS_INVOKE(x) ZEN_PP_MSVC_INVOKE(ZEN_DETAIL_FUNCTION_CLASS_OP, x)
#endif
#define ZEN_DETAIL_FUNCTION_CLASS_OP(i, name, n, t_params, f_params, body) \
ZEN_DETAIL_FUNCTION_CLASS_GEN(ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_NAME(i, name), n, t_params, f_params, body)

#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_NAME(i, name) BOOST_PP_CAT(zen_private_conditional_, BOOST_PP_CAT(i, name))
#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_NAMES(n, name) BOOST_PP_ENUM(n, ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_NAMES_EACH, name)
#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_NAMES_EACH(z, i, name) ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_NAME(i, name)

#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_ALL(r, name, n, params, bodies) \
ZEN_PP_DEFER(ZEN_PP_SEQ_FOR_EACH_I_R_ID)()(r, ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_EACH, \
    (name, n, ZEN_FUNCTION_PARAM_TEMPLATE_ARGS(r, params, Zen_T), ZEN_FUNCTION_PARAM_REPLACE_AUTO(r, params, Zen_T)), \
    bodies) \
    typedef zen::conditional_adaptor<ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_NAMES(BOOST_PP_SEQ_SIZE(bodies), name) > name; 

#ifndef _MSC_VER
#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_SINGLE_INVOKE(x) ZEN_DETAIL_FUNCTION_CLASS_GEN x
#else
#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_SINGLE_INVOKE(x) ZEN_PP_MSVC_INVOKE(ZEN_DETAIL_FUNCTION_CLASS_GEN, x)
#endif

#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_SINGLE(r, name, n, params, body) \
    ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_SINGLE_INVOKE((name, n, ZEN_FUNCTION_PARAM_TEMPLATE_ARGS(r, params, Zen_T), ZEN_FUNCTION_PARAM_REPLACE_AUTO(r, params, Zen_T), ZEN_PP_REM body))

#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL(r, name, params, bodies) BOOST_PP_IIF(ZEN_PP_SEQ_IS_SINGLE(bodies), \
                                                                    ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_SINGLE, \
                                                                    ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_ALL)\
                                                                    (r, name, ZEN_PP_NARGS params, ZEN_PP_ARGS_TO_SEQ params, bodies)

#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_P(s, data, x) ZEN_PP_EQUAL(x, else)
#define ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_SPLIT(seq) ZEN_PP_SEQ_SPLIT(seq, ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_P, data) 

//
// Overload adaptor
//
#define ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_P(s, data, x) ZEN_PP_EQUAL(x, def)
#define ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_SPLIT(seq) ZEN_PP_SEQ_SPLIT(seq, ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_P, data)

#define ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_NAME(i, name) BOOST_PP_CAT(zen_private_function_class_, BOOST_PP_CAT(i, name))
#define ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_NAMES(n, name) BOOST_PP_ENUM(n, ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_NAMES_EACH, name)
#define ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_NAMES_EACH(z, i, name) ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_NAME(i, name)

#define ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_EACH(r, name, i, seq) \
ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_SINGLE(r, ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_NAME(i, name), seq)

#define ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_SINGLE(r, name, bodies) \
ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL(r, name, BOOST_PP_SEQ_ELEM(0, bodies), ZEN_DETAIL_FUNCTION_CLASS_CONDITIONAL_SPLIT(BOOST_PP_SEQ_TAIL(bodies)))

#define ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_SINGLE_DISPATCH(name, body) ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_SINGLE(1, name, BOOST_PP_SEQ_HEAD(body))

#define ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_ALL(name, bodies) \
BOOST_PP_SEQ_FOR_EACH_I_R(1, ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_EACH, name, bodies) \
typedef zen::overload_adaptor<ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_NAMES(BOOST_PP_SEQ_SIZE(bodies), name) > name;

#define ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD(name, bodies) BOOST_PP_IIF(ZEN_PP_SEQ_IS_SINGLE(bodies), \
                                                                    ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_SINGLE_DISPATCH, \
                                                                    ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_ALL)\
                                                                    (name, bodies)


#define ZEN_DETAIL_FUNCTION_CLASS_NAME(seq) ZEN_DETAIL_FUNCTION_CLASS_NAME_I(BOOST_PP_SEQ_ELEM(0, seq))
#define ZEN_DETAIL_FUNCTION_CLASS_NAME_I(x) ZEN_PP_REM x

#define ZEN_DETAIL_FUNCTION_CLASS_TRANSFORM(seq) \
ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD(ZEN_DETAIL_FUNCTION_CLASS_NAME(seq), ZEN_DETAIL_FUNCTION_CLASS_OVERLOAD_SPLIT(BOOST_PP_SEQ_TAIL(seq)))

// Apply additional scans
#define ZEN_DETAIL_FUNCTION_CLASS_X(...) __VA_ARGS__

// class
#define ZEN_FUNCTION_CLASS(x) ZEN_DETAIL_FUNCTION_CLASS_X(ZEN_DETAIL_FUNCTION_CLASS_TRANSFORM(ZEN_PP_STRING_TO_SEQ(x)))

// function object
#define ZEN_DETAIL_FUNCTION_OBJECT(name, x) ZEN_FUNCTION_CLASS((BOOST_PP_CAT(zen_class_, name))x) zen::static_<BOOST_PP_CAT(zen_class_, name)> name = {};
#define ZEN_FUNCTION_OBJECT(x) ZEN_DETAIL_FUNCTION_OBJECT(BOOST_PP_SEQ_HEAD(x), BOOST_PP_SEQ_TAIL(x))

// pipe
#define ZEN_DETAIL_FUNCTION_PIPE_OBJECT(name, x) ZEN_FUNCTION_CLASS((BOOST_PP_CAT(zen_class_, name))x) zen::static_<zen::pipable_adaptor<BOOST_PP_CAT(zen_class_, name) > > name = {};
#define ZEN_FUNCTION_PIPE_OBJECT(x) ZEN_DETAIL_FUNCTION_PIPE_OBJECT(BOOST_PP_SEQ_HEAD(x), BOOST_PP_SEQ_TAIL(x))

#define ZEN_FUNCTION_KEYWORD_class (ZEN_FUNCTION_CLASS)

#define ZEN_FUNCTION_KEYWORD_pipe (ZEN_FUNCTION_PIPE_OBJECT)

// Register with ZLANG
#define ZLANG_zen_function (ZEN_FUNCTION)

#define ZEN_FUNCTION_INVOKE(m, args) m args
#define ZEN_FUNCTION_II(x) ZEN_FUNCTION_INVOKE(BOOST_PP_SEQ_HEAD(x), (BOOST_PP_SEQ_TAIL(x)))
#define ZEN_FUNCTION_I(x) ZEN_FUNCTION_II(BOOST_PP_CAT(ZEN_FUNCTION_KEYWORD_, x))
#define ZEN_FUNCTION(x) BOOST_PP_IIF(ZEN_PP_IS_PAREN(x), ZEN_FUNCTION_OBJECT, ZEN_FUNCTION_I)(x)



#ifdef ZEN_TEST
namespace zen {

namespace zen_function_test {

// class
ZEN_FUNCTION_CLASS((sum_class)(const auto x, const auto y) if(ax<std::is_integral>(x) and ax<std::is_integral>(y))(x + y) else (1))
// object
ZEN_FUNCTION_OBJECT((sum)(const auto x, const auto y) if(ax<std::is_integral>(x) and ax<std::is_integral>(y))(x + y) else (1))
// pipe
ZEN_FUNCTION_PIPE_OBJECT((sum_pipe)(const auto x, const auto y) if(ax<std::is_integral>(x) and ax<std::is_integral>(y))(x + y) else (1))

#include <zen/test.h>

struct foo
{};

ZEN_TEST_CASE(function_builder_test)
{
    ZEN_TEST_EQUAL( sum(1, 2), 3 );
    ZEN_TEST_EQUAL( sum_class()(1, 2), 3 );
    ZEN_TEST_EQUAL( 1 | sum_pipe(2), 3 );
    ZEN_TEST_EQUAL( sum(foo(), 2), 1 );
}


}

}
#endif

#endif
