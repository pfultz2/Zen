/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    builder.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TRAITS_BUILDER_H
#define ZEN_GUARD_TRAITS_BUILDER_H

#include <type_traits>
#include <zen/pp.h>
#include <zen/traits/local_ops.h>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/not.hpp>

// Trait introspection based on Eric Niebler's concepts

namespace zen {

namespace traits_detail {
template<class T1 = void, class T2 = void, class T3 = void, class T4 = void, class T5 = void>
struct holder
{
    typedef void type;
};

template<template<class...> class... Templates>
struct template_holder
{
    typedef void type;
};

struct void_ {};

template<class T> T&& operator,(T&& x, void_);

template<typename T>
int valid_expr(T &&);

template <class T>
struct is_placeholder_expression
: boost::mpl::not_<std::is_same<typename boost::mpl::lambda<T>::type, T>>
{};

// TODO: Use these traits for is_placoholder_expression
template<class F, class... Ts>
struct apply_trait
{
    typedef typename F::template apply<Ts...>::type type;
};

template<class F, class... Ts>
struct lambda_trait
{
    typedef typename boost::mpl::lambda<F>::type lambda;
    typedef apply_trait<lambda, Ts...> type;
};

// Specializations for the most common use cases
template<template<class...> class F, class T>
struct lambda_trait<F<boost::mpl::arg<-1>>, T>
{
    typedef F<T> type;
};
template<template<class...> class F, class T>
struct lambda_trait<F<boost::mpl::arg<1>>, T>
{
    typedef F<T> type;
};

template<class F, class... Ts>
using apply = typename lambda_trait<F, Ts...>::type;

template<class T, class U>
struct matches
: boost::mpl::eval_if<is_placeholder_expression<U>, 
    apply<U, T>,
    std::is_convertible<T, U>
>::type
{};

template<class T>
struct matches<T, void>
: std::true_type
{};

struct base_requires
{
    template<class... Ts>
    int requires(Ts&&...);
};

}

#define ZEN_VALID_EXPR(...) decltype(zen::traits_detail::valid_expr((__VA_ARGS__, zen::traits_detail::void_())))


template<typename T, typename U>
auto returns(U &&) ->
    typename std::enable_if<traits_detail::matches<U,T>::value, int>::type;


template<
    class T, 
    class U = void, 
    class Enable = typename std::enable_if<traits_detail::matches<T,U>::value>::type>
class has_type {};

template<template<class...> class Template>
class has_template {};

template<
    class T, 
    class Enable = typename std::enable_if<T::value>::type>
class is_true {};

template<
    class T, 
    class Enable = typename std::enable_if<not T::value>::type>
class is_false {};


template<class... Traits>
struct base_traits;

template<class Trait, class... Traits>
struct base_traits<Trait, Traits...>
: std::integral_constant<bool, Trait::value and base_traits<Traits...>::value>
{
    typedef base_traits<Trait, Traits...> base_traits_type;
};
template<>
struct base_traits<>
: std::true_type
{
    typedef base_traits<> base_traits_type;
};
template<class... Lambdas>
struct refines
{
    template<class... Ts>
    struct zen_trait_base_apply
    : base_traits<traits_detail::apply<Lambdas, Ts...>...>
    {
    };
};

template<class T, class Enable=void>
struct refine_traits
{
    template<class... Ts>
    struct apply
    : base_traits<>
    {
    };
};

template<class T>
struct refine_traits<T, typename traits_detail::template_holder<T::template zen_trait_base_apply>::type>
{
    template<class... Ts>
    struct apply
    : T::template zen_trait_base_apply<Ts...>
    {

    };
};

template<class T, class Enable = void>
struct base_traits_type
{
    typedef base_traits<> type;
};

template<class T>
struct base_traits_type<T, typename traits_detail::holder<
    typename T::base_traits_type
>::type>
{
    typedef typename T::base_traits_type type;
};

template<class Trait, class X = void>
struct trait 
: std::false_type
{};
// TODO: Add axioms
template<class Trait, class... Ts>
struct trait<Trait(Ts...), typename traits_detail::holder<
    decltype(std::declval<Trait>().requires(std::declval<Ts>()...))
>::type>
: refine_traits<Trait>::template apply<Ts...>
{};

#define ZEN_TRAIT_REFINES(name, ...) \
struct zen_private_trait_ ## name; \
template<class... T> \
struct name \
: zen::trait<zen_private_trait_ ## name(T...)> \
{}; \
struct zen_private_trait_ ## name : zen::traits_detail::base_requires, zen::local_ops, zen::refines<__VA_ARGS__>

#define ZEN_TRAIT(...) \
    ZEN_PP_EXPAND( \
        ZEN_TRAIT_REFINES BOOST_PP_IF(ZEN_PP_ARGS_IS_SINGLE(__VA_ARGS__), (__VA_ARGS__,), (__VA_ARGS__)))

// template<class Trait>
// struct test_trait;
// template<class Trait, class... Ts>
// struct test_trait<Trait(Ts...)>
// {
//     typedef decltype(Trait::requires(std::declval<Ts>()...)) type;
// };

}

#ifdef ZEN_TEST

namespace test_zen_traits {


static_assert(zen::traits_detail::matches<int, int>::value, "int -> int doesn't match");
static_assert(zen::traits_detail::matches<int, float>::value, "int -> float doesn't match");
static_assert(zen::traits_detail::matches<int, void>::value, "int -> void doesn't match");

ZEN_TRAIT(has_foo_member)
{
    template<class T>
    auto requires(T&& x) -> ZEN_VALID_EXPR(
        zen::returns<int>(x.foo())
    );
};

ZEN_TRAIT(has_more_foo_member)
{
    template<class T>
    auto requires(T&& x) -> ZEN_VALID_EXPR(
        zen::is_true<has_foo_member<T>>()
    );
};

ZEN_TRAIT(has_integral_foo_member)
{
    template<class T>
    auto requires(T&& x) -> ZEN_VALID_EXPR(
        zen::returns<std::is_integral<boost::mpl::_>>(x.foo())
    );
};

ZEN_TRAIT(has_simple_foo_member)
{
    template<class T>
    auto requires(T&& x) -> ZEN_VALID_EXPR(
        x.foo()
    );
};

struct foo_member
{
    int foo();
};

struct long_foo_member
{
    long foo();
};

struct no_foo_member
{};

struct invalid_foo_member
{
    struct invalid
    {};

    invalid foo();
};

struct void_foo_member
{
    void foo();
};

static_assert(has_foo_member<foo_member>(), "No foo member");
static_assert(has_foo_member<long_foo_member>(), "No foo member");
static_assert(not has_foo_member<no_foo_member>(), "Foo member found");
static_assert(not has_foo_member<invalid_foo_member>(), "Invalid foo member found");
static_assert(not has_foo_member<void_foo_member>(), "Invalid void foo member found");

static_assert(has_more_foo_member<foo_member>(), "No foo member");
static_assert(has_more_foo_member<long_foo_member>(), "No foo member");
static_assert(not has_more_foo_member<no_foo_member>(), "Foo member found");
static_assert(not has_more_foo_member<invalid_foo_member>(), "Invalid foo member found");
static_assert(not has_more_foo_member<void_foo_member>(), "Invalid void foo member found");

static_assert(has_integral_foo_member<foo_member>(), "No foo member");
static_assert(has_integral_foo_member<long_foo_member>(), "No foo member");
static_assert(not has_integral_foo_member<no_foo_member>(), "Foo member found");
static_assert(not has_integral_foo_member<invalid_foo_member>(), "Invalid foo member found");
static_assert(not has_integral_foo_member<void_foo_member>(), "Invalid void foo member found");

static_assert(has_simple_foo_member<foo_member>(), "No foo member");
static_assert(not has_simple_foo_member<no_foo_member>(), "Foo member found");
static_assert(has_simple_foo_member<invalid_foo_member>(), "Invalid foo member found");
static_assert(has_simple_foo_member<void_foo_member>(), "No void foo member found");

ZEN_TRAIT(has_nested_type)
{
    template<class T>
    auto requires(T) -> ZEN_VALID_EXPR(
        zen::has_type<typename T::type, int>()
    );
};

ZEN_TRAIT(has_integral_nested_type)
{
    template<class T>
    auto requires(T) -> ZEN_VALID_EXPR(
        zen::has_type<typename T::type, std::is_integral<boost::mpl::_>>()
    );
};

ZEN_TRAIT(has_simple_nested_type)
{
    template<class T>
    auto requires(T) -> ZEN_VALID_EXPR(
        zen::has_type<typename T::type>()
    );
};

struct nested_type
{
    typedef int type;
};

struct no_nested_type
{
    typedef int type_;
};

struct invalid_nested_type
{
    struct invalid {};
    typedef invalid type;
};

struct void_nested_type
{
    typedef void type;
};

struct template_nested_type
{
    template<class T>
    struct type {};
};

static_assert(has_nested_type<nested_type>(), "No nested type");
static_assert(not has_nested_type<no_nested_type>(), "nested type found");
static_assert(not has_nested_type<invalid_nested_type>(), "Invalid nested type found");
static_assert(not has_nested_type<invalid_nested_type>(), "Templated nested type found");
static_assert(not has_nested_type<void_nested_type>(), "Invalid void nested type found");
static_assert(not has_nested_type<template_nested_type>(), "Templated nested type found");

static_assert(has_integral_nested_type<nested_type>(), "No nested type");
static_assert(not has_integral_nested_type<no_nested_type>(), "nested type found");
static_assert(not has_integral_nested_type<invalid_nested_type>(), "Invalid nested type found");
static_assert(not has_integral_nested_type<invalid_nested_type>(), "Templated nested type found");
static_assert(not has_integral_nested_type<void_nested_type>(), "Invalid void nested type found");
static_assert(not has_integral_nested_type<template_nested_type>(), "Templated nested type found");

static_assert(has_simple_nested_type<nested_type>(), "No nested type");
static_assert(not has_simple_nested_type<no_nested_type>(), "nested type found");
static_assert(has_simple_nested_type<invalid_nested_type>(), "Invalid nested type found");
static_assert(has_simple_nested_type<void_nested_type>(), "No void nested type found");
static_assert(not has_simple_nested_type<template_nested_type>(), "Templated nested type found");


struct nested_template
{
    template<class T>
    struct template_
    {};
};

struct no_nested_template
{
};

struct invalid_nested_template
{
    struct template_ {};
};

ZEN_TRAIT(has_nested_template)
{
    template<class T>
    auto requires(T) -> ZEN_VALID_EXPR(
        zen::has_template<T::template template_>()
    );
};

static_assert(has_nested_template<nested_template>(), "No nested template");
static_assert(not has_nested_template<no_nested_template>(), "nested template found");
static_assert(not has_nested_template<invalid_nested_template>(), "Invalid nested template found");


}

#endif

#endif
