/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    requires.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

// @begin
// 
// Requires
// ========
// 
// Introduction
// ------------
// 
// The requires macro provides a way for template specialization to include or
// exclude matching specialization based on traits given to it. There are three
// macros available:
// 
//     // Used inside template parameters
//     #define ZEN_REQUIRES(...)
//     // Used for functions
//     #define ZEN_FUNCTION_REQUIRES(...)
//     // Used for class specializations
//     #define ZEN_CLASS_REQUIRES(...)
// 
// Say for instance we had a template function like this:
// 
//     template<class T, class U>
//     T max(T x, U y)
//     {
//         return x > y : x ? y;
//     }
// 
// Perhaps we would like to restrict this function to just aritmetic types, We
// can use the `ZEN_FUNCTION_REQUIRES` macro to write this:
// 
//     template<class T, class U>
//     ZEN_FUNCTION_REQUIRES(is_arithmetic<T>, is_arithmetic<U>)
//     (T) max(T x, U y)
//     {
//         return x > y : x ? y;
//     }
// 
// It's important to note that parenthesis are required to be placed around the
// return type when using the `ZEN_FUNCTION_REQUIRES` macro. Also, multiple
// traits can be given to the requires clause, and if it's true for every trait
// given, then that function will be selected. So, it will by default be
// inclusive with traits, but perhaps we want to exclude the function if a trait
// is true. For example, maybe we would like to use this max function on
// arithmetic types, but exclude booleans. In this case we can use the `exclude`
// keyword(also `not` can be used on C++ compilers, but for portability to msvc
// it's better to use `exclude`):
// 
//     template<class T, class U>
//     ZEN_FUNCTION_REQUIRES
//     (
//         is_arithmetic<T>, 
//         is_arithmetic<U>, 
//         exclude is_same<T, bool>, 
//         exclude is_same<U, bool>
//     )
//     (T) max(T x, U y)
//     {
//         return x > y : x ? y;
//     }
// 
// Usage
// -----
// 
// The `ZEN_REQUIRES` macro is useful where default template parameters are
// used such as for classes(and function in C++11). It can be used something like
// this:
// 
//     template<class T, ZEN_REQUIRES(is_integral<T>)>
//     class A { ... };
// 
// If class specialization is needed, then the `ZEN_CLASS_REQUIRES` macro can
// be used, like this:
// 
//     template <class T, class Enable = void> 
//     class A { ... };
// 
//     template <class T>
//     class A<T, ZEN_CLASS_REQUIRES(is_integral<T>)> { ... };
// 
//     template <class T>
//     class A<T, ZEN_CLASS_REQUIRES(is_float<T>)> { ... };
// 
// For functions, the `ZEN_FUNCTION_REQUIRES` can be used like this, but
// parenthesis needs to be placed around the return type:
// 
//     template<class T, class U>
//     ZEN_FUNCTION_REQUIRES(is_arithmetic<T>, is_arithmetic<U>)
//     (T) max(T x, U y)
//     {
//         return x > y : x ? y;
//     }
// 
// Also, the `exclude` keyword can be used to exclude a trait from being
// selected. This is really helpful, when there are overlapping conditions:
// 
//     template<class T>
//     ZEN_FUNCTION_REQUIRES(is_integral<T>)
//     (T) foo(T x) { ... }
// 
//     template<class T>
//     ZEN_FUNCTION_REQUIRES(is_arithmetic<T>, exlcude is_integral<T>)
//     (T) foo(T x) { ... }
// 
// Also, the keyword `not` can be used instead of `exclude`: 
// 
//     template<class T>
//     ZEN_FUNCTION_REQUIRES(is_integral<T>)
//     (T) foo(T x) { ... }
// 
//     template<class T>
//     ZEN_FUNCTION_REQUIRES(is_arithmetic<T>, not is_integral<T>)
//     (T) foo(T x) { ... }
// 
// But this won't work in non-C++ compilers such as msvc.
// 
// @end


#ifndef ZEN_REQUIRES_H
#define	ZEN_REQUIRES_H

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <zen/pp.h>
#include <zen/static_assert.h>
#include <iso646.h>

namespace zen{namespace requires_detail{
struct not_tag {};

template<class X>
struct not_state : X {};


struct requires_op
{
    template<class X, class Y>
    struct apply
    : boost::mpl::bool_<X::type::value and Y::type::value> {};

    template<class X>
    struct apply<X, not_tag>
    : boost::mpl::identity<not_state<X> > {};

    template<class X, class Y>
    struct apply<not_state<X>, Y>
    : boost::mpl::bool_<X::type::value and not Y::type::value> {};
};

template<class Sequence>
struct requires_
{
    
    typedef typename boost::mpl::fold<Sequence, boost::mpl::bool_<true>, requires_op>::type type;

    static const bool value = type::value;

};

}
}
#define ZEN_DETAIL_REQUIRES_CLAUSE_KEYWORD_not ()
#define ZEN_DETAIL_REQUIRES_CLAUSE_KEYWORD_exclude ()


#define ZEN_DETAIL_REQUIRES_CLAUSE_DISPATCH(tokened, x) BOOST_PP_IIF(ZEN_PP_IS_PAREN(tokened), (zen::requires_detail::not_tag)(ZEN_PP_REM tokened), (x))
#define ZEN_DETAIL_REQUIRES_CLAUSE_EACH(r, data, x) ZEN_DETAIL_REQUIRES_CLAUSE_DISPATCH(BOOST_PP_CAT(ZEN_DETAIL_REQUIRES_CLAUSE_KEYWORD_, x), x)
#define ZEN_DETAIL_REQUIRES_CLAUSE(...) \
zen::requires_detail::requires_<boost::mpl::vector<BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(ZEN_DETAIL_REQUIRES_CLAUSE_EACH, ~, ZEN_PP_ARGS_TO_SEQ(__VA_ARGS__)))> >


#ifdef ZEN_TEST
static_assert(ZEN_DETAIL_REQUIRES_CLAUSE(boost::mpl::bool_<true>)::type::value, "Failed");
static_assert(ZEN_DETAIL_REQUIRES_CLAUSE(boost::mpl::bool_<true>, boost::mpl::bool_<true>)::type::value, "Failed");
static_assert(ZEN_DETAIL_REQUIRES_CLAUSE(boost::mpl::bool_<true>, exclude boost::mpl::bool_<false>)::type::value, "Failed");
static_assert(ZEN_DETAIL_REQUIRES_CLAUSE(exclude boost::mpl::bool_<false>, boost::mpl::bool_<true>)::type::value, "Failed");
static_assert(ZEN_DETAIL_REQUIRES_CLAUSE(exclude boost::mpl::bool_<false>)::type::value, "Failed");
#endif

 
#define ZEN_ERROR_PARENTHESIS_MUST_BE_PLACED_AROUND_THE_RETURN_TYPE(...) __VA_ARGS__>::type
#define ZEN_FUNCTION_REQUIRES(...) typename boost::enable_if<ZEN_DETAIL_REQUIRES_CLAUSE(__VA_ARGS__), ZEN_ERROR_PARENTHESIS_MUST_BE_PLACED_AROUND_THE_RETURN_TYPE

#define ZEN_CLASS_REQUIRES(...) typename boost::enable_if<ZEN_DETAIL_REQUIRES_CLAUSE(__VA_ARGS__)>::type

#define ZEN_REQUIRES(...) class Zen_Enable = typename boost::enable_if<ZEN_DETAIL_REQUIRES_CLAUSE(__VA_ARGS__)>::type


#endif	/* ZEN_REQUIRES_H */

