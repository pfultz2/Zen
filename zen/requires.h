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

#include <zen/config.h>
#include <iso646.h>
#include <type_traits>
#include <boost/mpl/bool.hpp>

namespace zen {

namespace detail {

struct requires_private {};

}

namespace predicate_clause {

#define ZEN_PREDICATE_FOREACH_BINARY_OPS(m) \
    m(+, plus) \
    m(-, minus) \
    m(*, multiply) \
    m(/, divide) \
    m(%, remainder) \
    m(&, bitand_) \
    m(|, bitor_) \
    m(&&, and_) \
    m(||, or_) \
    m(==, equal) \
    m(!=, not_equal) \
    m(<=, less_than_equal) \
    m(>=, greater_than_equal) \
    m(<, less_than) \
    m(>, greater_than)

#define ZEN_PREDICATE_BINARY_OP(op, name) \
    template<class T, class U> \
    struct name \
    : std::integral_constant< \
        typename std::common_type< \
            typename T::value_type, \
            typename U::value_type \
        >::type, (T::value op U::value)> \
    {};

ZEN_PREDICATE_FOREACH_BINARY_OPS(ZEN_PREDICATE_BINARY_OP)

template<class T>
struct not_
: std::integral_constant<bool, !T::value>
{};

#define ZEN_PREDICATE_CAPTURE_BINARY_OP(op, name) \
    template<class U> \
    typename std::enable_if<!std::is_integral<U>::value, expression<name<T, U>>>::type \
    operator op(const U&) const; \


template<class T>
struct expression
: std::integral_constant<typename T::value_type, T::value>
{

    ZEN_PREDICATE_FOREACH_BINARY_OPS(ZEN_PREDICATE_CAPTURE_BINARY_OP)

    expression<not_<T>> operator !() const;
};
struct capture
{
    template<typename T>
    constexpr expression<T> operator->* (const T&) const
    {
        static_assert(!std::is_integral<T>::value, 
            "Predicate clauses cannot have literals. Please wrap them in a type.");
        return expression<T>();
    }
};

template<class T, class X = void>
struct enable_if
: std::enable_if<T::value, X>
{};

}

#define ZEN_PREDICATE_CLAUSE(...) decltype(zen::predicate_clause::capture() ->* __VA_ARGS__)

template<bool B>
using requires_ = typename std::enable_if<B, int>::type;

}
 
#define ZEN_ERROR_PARENTHESIS_MUST_BE_PLACED_AROUND_THE_RETURN_TYPE(...) __VA_ARGS__>::type
#define ZEN_FUNCTION_REQUIRES(...) typename std::enable_if<(__VA_ARGS__), ZEN_ERROR_PARENTHESIS_MUST_BE_PLACED_AROUND_THE_RETURN_TYPE

#define ZEN_CLASS_REQUIRES(...) typename std::enable_if<(__VA_ARGS__)>::type
#define ZEN_PARAM_REQUIRES(...) typename zen::predicate_clause::enable_if<ZEN_PREDICATE_CLAUSE(__VA_ARGS__), zen::detail::requires_private>::type=zen::detail::requires_private()
#define ZEN_REQUIRES_CONVERTIBLE(...) typename std::enable_if<std::is_convertible<__VA_ARGS__>::value, int>::type=0

#define ZEN_REQUIRES(...) typename std::enable_if<(__VA_ARGS__), int>::type = 0


#endif	/* ZEN_REQUIRES_H */

