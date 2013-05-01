/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    forward.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FORWARD_H
#define	ZEN_GUARD_FORWARD_H


#include <zen/config.h>
#include <boost/type_traits.hpp>
#include <boost/mpl/identity.hpp>

namespace zen {


#ifdef ZEN_NO_RVALUE_REFS
#define ZEN_FORWARD_REF(...) __VA_ARGS__ &



// template< class T >
// const T& forward( const typename boost::remove_reference<T>::type& t )
// {
//     return static_cast<const T&>(t);
// }

// template< class T >
// T& forward( typename boost::remove_reference<T>::type& t )
// {
//     return static_cast<T&>(t);
// }

#else
#define ZEN_FORWARD_REF(x) x &&

// TODO: Add noexcept to forwarding functions
template< class T >
T&& forward( typename std::remove_reference<T>::type&& t )
{
    static_assert(not std::is_lvalue_reference<T>::value, "Attempting to forward an rvalue as an lvalue");
    return static_cast<T&&>(t);
}

#endif

template< class T >
ZEN_FORWARD_REF(T) forward( typename boost::remove_reference<T>::type& t )
{
    return static_cast<ZEN_FORWARD_REF(T)>(t);
}


#ifdef ZEN_NO_RVALUE_REFS
template<class T>
struct add_forward_reference
{
    typedef const T& type;
};

template<class T>
struct add_forward_reference<T&>
{
    typedef T& type;
};

template<class T>
struct add_forward_reference<const T&>
{
    typedef const T& type;
};

template<class T>
struct add_forward_reference<const T>
{
    typedef const T& type;
};

#else
template<class T>
struct add_forward_reference
{
    typedef T&& type;
};

#endif


}





#endif	/* ZEN_GUARD_FORWARD_H */

