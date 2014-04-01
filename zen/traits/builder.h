/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    builder.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TRAITS_BUILDER_H
#define ZEN_GUARD_TRAITS_BUILDER_H

#include <type_traits>
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

struct void_ {};

template<class T> T&& operator,(T&& x, void_);

template<typename T>
int valid_expr(T &&);

template <class T>
struct is_placeholder_expression
: boost::mpl::not_<std::is_same<typename boost::mpl::lambda<T>::type, T>>
{};

// template<class F, class T, class Lambda = typename boost::mpl::lambda<F>::type>
// struct apply
// : Lambda::template apply<T>
// {};

template<class F, class T>
struct apply
{
    typedef typename boost::mpl::lambda<F>::type lambda;
    typedef typename lambda::template apply<T>::type type;
};

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

}

#define ZEN_VALID_EXPR(...) decltype(zen::traits_detail::valid_expr((__VA_ARGS__, zen::traits_detail::void_())))


template<typename T, typename U>
auto returns_(U &&) ->
    typename std::enable_if<traits_detail::matches<U,T>::value, int>::type;


template<
    class T, 
    class U = void, 
    class Enable = typename std::enable_if<traits_detail::matches<T,U>::value>::type>
class has_type {};

template<template<class...> class Template>
class has_template {};


template<class Trait, class X = void>
struct trait 
: std::false_type
{};

template<class Trait, class... Ts>
struct trait<Trait(Ts...), typename traits_detail::holder<
    decltype(Trait::requires(std::declval<Ts>()...))
>::type>
: std::true_type
{};

#define ZEN_TRAIT(name) \
struct zen_private_trait_ ## name; \
template<class... T> \
struct name \
: zen::trait<zen_private_trait_ ## name(T...)> \
{}; \
struct zen_private_trait_ ## name

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
    static auto requires(T&& x) -> ZEN_VALID_EXPR(
        zen::returns_<int>(x.foo())
    );
};

ZEN_TRAIT(has_integral_foo_member)
{
    template<class T>
    static auto requires(T&& x) -> ZEN_VALID_EXPR(
        zen::returns_<std::is_integral<boost::mpl::_>>(x.foo())
    );
};

ZEN_TRAIT(has_simple_foo_member)
{
    template<class T>
    static auto requires(T&& x) -> ZEN_VALID_EXPR(
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
    static auto requires(T) -> ZEN_VALID_EXPR(
        zen::has_type<typename T::type, int>()
    );
};

ZEN_TRAIT(has_integral_nested_type)
{
    template<class T>
    static auto requires(T) -> ZEN_VALID_EXPR(
        zen::has_type<typename T::type, std::is_integral<boost::mpl::_>>()
    );
};

ZEN_TRAIT(has_simple_nested_type)
{
    template<class T>
    static auto requires(T) -> ZEN_VALID_EXPR(
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
    static auto requires(T) -> ZEN_VALID_EXPR(
        zen::has_template<T::template template_>()
    );
};

static_assert(has_nested_template<nested_template>(), "No nested template");
static_assert(not has_nested_template<no_nested_template>(), "nested template found");
static_assert(not has_nested_template<invalid_nested_template>(), "Invalid nested template found");


}

#endif

#endif
