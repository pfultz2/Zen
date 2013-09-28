/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    typeof.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TYPEOF_H
#define	ZEN_GUARD_TYPEOF_H

#include <zen/static_assert.h>
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>

#if !defined(ZEN_NO_DECLTYPE)
#define ZEN_TYPEOF(...) decltype(zen::typeof_detail::decayed(ZEN_AVOID(__VA_ARGS__)))
#define ZEN_TYPEOF_TPL(...) decltype(zen::typeof_detail::decayed(ZEN_AVOID(__VA_ARGS__)))
#elif defined(ZEN_HAS_TYPEOF)
#define ZEN_TYPEOF __typeof__
#define ZEN_TYPEOF_TPL __typeof__
#else
#include <boost/typeof/typeof.hpp>
#define ZEN_TYPEOF BOOST_TYPEOF
#define ZEN_TYPEOF_TPL BOOST_TYPEOF_TPL
#endif

#ifndef ZEN_NO_AUTO
#define ZEN_AUTO(var, ...) auto var = __VA_ARGS__
#define ZEN_AUTO_TPL(var, ...) auto var = __VA_ARGS__
#else
#define ZEN_AUTO(var, ...) ZEN_TYPEOF(__VA_ARGS__) var = __VA_ARGS__
#define ZEN_AUTO_TPL(var, ...) ZEN_TYPEOF_TPL(__VA_ARGS__) var = __VA_ARGS__
#endif

#ifndef ZEN_NO_TRAILING_RETURN
    #if !defined(ZEN_NO_NOEXCEPT) && !defined(ZEN_NO_RVALUE_REFS)
    #define ZEN_RETURNS(...) \
        noexcept(noexcept(decltype(__VA_ARGS__)(zen::typeof_detail::move(ZEN_AVOID(__VA_ARGS__))))) \
        -> decltype(__VA_ARGS__) \
        { return (__VA_ARGS__); } static_assert(true, "")
    #else
    #define ZEN_RETURNS(...) -> decltype(__VA_ARGS__) { return __VA_ARGS__; } static_assert(true, "")
    #endif
#else
#define ZEN_RETURNS(...) ZEN_ERROR_TRAILING_RETURNS_NOT_SUPPORTED
#endif


#ifndef ZEN_NO_DECLTYPE
#define ZEN_XTYPEOF(...) decltype((__VA_ARGS__))
#define ZEN_XTYPEOF_TPL(...) decltype((__VA_ARGS__))
#else
#define ZEN_XTYPEOF(...) zen::typeof_detail::xtypeof_<ZEN_TYPEOF(__VA_ARGS__), ZEN_TYPEOF_IS_LVALUE(__VA_ARGS__), ZEN_TYPEOF_IS_RVALUE(__VA_ARGS__)>::type
#define ZEN_XTYPEOF_TPL(...) typename zen::typeof_detail::xtypeof_<ZEN_TYPEOF_TPL(__VA_ARGS__), ZEN_TYPEOF_IS_LVALUE_TPL(__VA_ARGS__), ZEN_TYPEOF_IS_RVALUE_TPL(__VA_ARGS__)>::type
#endif


#ifndef ZEN_NO_AUTO
#define ZEN_XAUTO(var, ...) auto&& var = __VA_ARGS__
#define ZEN_XAUTO_TPL(var, ...) auto&& var = __VA_ARGS__        
#else
#define ZEN_XAUTO(var, ...) ZEN_XTYPEOF(__VA_ARGS__) var = __VA_ARGS__
#define ZEN_XAUTO_TPL(var, ...) ZEN_XTYPEOF_TPL(__VA_ARGS__) var = __VA_ARGS__
#endif

namespace zen {

#ifndef ZEN_NO_RVALUE_REFS
template<class T>
T&& declval();
#else
template<class T>
T declval();
#endif



namespace typeof_detail {
struct void_ {};
#ifndef ZEN_NO_RVALUE_REFS
template<class T> T&& operator,(T&& x, void_)
{
    return std::forward<T>(x);
}
#else
template<class T> const T& operator,(T const&, void_)
{
    return x;
}
template<class T> T& operator,(T&, void_)
{
    return x;
}
#endif
#define ZEN_AVOID(...) ((__VA_ARGS__), zen::typeof_detail::void_())

#if !defined(ZEN_NO_NOEXCEPT) && !defined(ZEN_NO_RVALUE_REFS)
template<typename T>
typename std::remove_reference<T>::type&&
move(T&& x) noexcept;
void move(void_);
#endif

#ifndef ZEN_NO_RVALUE_REFS
template<class T>
typename std::decay<T>::type decayed(T&& x);
#else
template<class T>
T decayed(T& x);

template<class T>
const T decayed(const T& x);
#endif

void decayed(void_);

//rvalue probe from Eric Niebler
template<typename T>
struct rvalue_probe
{
    struct private_type_ {};
    // can't ever return an array by value
    typedef BOOST_DEDUCED_TYPENAME boost::mpl::if_<
        boost::mpl::or_<boost::is_abstract<T>, boost::is_array<T> >, private_type_, T
    >::type value_type;
    operator value_type();
    operator const T&() const;
};

template<typename T>
rvalue_probe<T> const make_probe(T const &);
void make_probe(void_);

#define ZEN_TYPEOF_RVALUE_PROBE(x) true ? zen::typeof_detail::make_probe(ZEN_AVOID(x)) : (x)

#define ZEN_TYPEOF_IS_RVALUE(x) \
boost::mpl::and_<boost::mpl::not_<boost::is_array<ZEN_TYPEOF(x)> >,\
boost::mpl::not_<boost::is_const<ZEN_TYPEOF(ZEN_TYPEOF_RVALUE_PROBE(x))> > >

#define ZEN_TYPEOF_IS_RVALUE_TPL(x) \
boost::mpl::and_<boost::mpl::not_<boost::is_array<ZEN_TYPEOF_TPL(x)> >,\
boost::mpl::not_<boost::is_const<ZEN_TYPEOF_TPL(ZEN_TYPEOF_RVALUE_PROBE(x))> > >

template<class T> boost::mpl::false_ is_lvalue(const T &);
template<class T> boost::mpl::true_ is_lvalue(T&);
inline boost::mpl::false_ is_lvalue(void_);

#define ZEN_TYPEOF_IS_LVALUE(x) \
ZEN_TYPEOF(zen::typeof_detail::is_lvalue(ZEN_AVOID(x)))

#define ZEN_TYPEOF_IS_LVALUE_TPL(x) \
ZEN_TYPEOF_TPL(zen::typeof_detail::is_lvalue(ZEN_AVOID(x)))

template<class T, class IsLvalue, class IsRvalue>
struct xtypeof_
: boost::mpl::if_<boost::mpl::or_<IsLvalue, boost::mpl::not_<IsRvalue> >, 
typename boost::add_reference<T>::type, 
T> 
{};

template<class IsLvalue, class IsRvalue>
struct xtypeof_<void_, IsLvalue, IsRvalue>
{
    typedef void type;
};

//is_const2 that works with references
template<class T>
struct is_const2 : boost::is_const<typename boost::remove_reference<T>::type >
{
};

}
}

#ifdef ZEN_TEST
namespace zen {
namespace typeof_test {

int by_value();
int& by_ref();
const int& by_const_ref();
void by_void();

struct foo
{
    static int by_value();
    static int& by_ref();
    static const int& by_const_ref();
    static void by_void();
};

template<class T>
struct tester
{
    typedef ZEN_XTYPEOF_TPL(T::by_value()) test2;

    //On MSVC, static_assert is broken, so we use BOOST_MPL_ASSERT instead.
    BOOST_MPL_ASSERT_NOT((boost::is_reference<ZEN_XTYPEOF_TPL(T::by_value())>));
    BOOST_MPL_ASSERT_NOT((zen::typeof_detail::is_const2<ZEN_XTYPEOF_TPL(T::by_value())>));

    BOOST_MPL_ASSERT((boost::is_reference<ZEN_XTYPEOF_TPL(T::by_ref())>));
    BOOST_MPL_ASSERT_NOT((zen::typeof_detail::is_const2<ZEN_XTYPEOF_TPL(T::by_ref())>));

    BOOST_MPL_ASSERT((boost::is_reference<ZEN_XTYPEOF_TPL(T::by_const_ref())>));
    BOOST_MPL_ASSERT((zen::typeof_detail::is_const2<ZEN_XTYPEOF_TPL(T::by_const_ref())>));

    BOOST_MPL_ASSERT((boost::is_same<ZEN_XTYPEOF_TPL(T::by_void()), void>));
};

static tester<foo> tested;

}
}

static_assert(not boost::is_reference<ZEN_XTYPEOF(zen::typeof_test::by_value())>::value, "Failed");
static_assert(not zen::typeof_detail::is_const2<ZEN_XTYPEOF(zen::typeof_test::by_value())>::value, "Failed");

static_assert(boost::is_reference<ZEN_XTYPEOF(zen::typeof_test::by_ref())>::value, "Failed");
static_assert(not zen::typeof_detail::is_const2<ZEN_XTYPEOF(zen::typeof_test::by_ref())>::value, "Failed");

static_assert(boost::is_reference<ZEN_XTYPEOF(zen::typeof_test::by_const_ref())>::value, "Failed");
static_assert(zen::typeof_detail::is_const2<ZEN_XTYPEOF(zen::typeof_test::by_const_ref())>::value, "Failed");

static_assert(boost::is_same<ZEN_XTYPEOF(zen::typeof_test::by_void()), void>::value, "Failed");

#endif


#endif	/* TYPEOF_H */

