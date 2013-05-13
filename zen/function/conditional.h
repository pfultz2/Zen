/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    conditional.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_CONDITIONAL_H
#define ZEN_GUARD_FUNCTION_CONDITIONAL_H

// @begin
// conditional
// ======
// 
// Description
// -----------
// 
// The `conditional` function adaptor combines several functions together. If the
// first function can not be called, then it will try to call the next function.
// 
// Note: This is different than the `overload` function adaptor, which can lead
// to ambiguities. Instead, `conditional` will call the first function that is
// callable, regardless if there is another function that could be called as
// well. So, for example:
// 
//     struct for_ints
//     {
//         void operator()(int) const
//         {
//             printf("Int\n");
//         }
//     };
// 
//     struct for_floats
//     {
//         void operator()(int) const
//         {
//             printf("Float\n");
//         }
//     };
// 
//     conditional(for_ints(), for_floats())(3.0);
// 
// This will print `Int` because the `for_floats` function object won't ever be
// called. Due to the conversion rules in C++, the `for_ints` function can be
// called on floats, so it is chosen by `conditional` first, even though
// `for_floats` is a better match.
// 
// So, the order of the functions in the `conditional_adaptor` are very important
// to how the function is chosen.
// 
// Synopsis
// --------
// 
//     template<class F1, class F2, ...>
//     conditional_adaptor<F1, F2, ...> conditional(F1 f1, F2 f2, ...);
// 
// @end

#include <zen/function/adaptor.h>
#include <zen/function/variadic.h>
#include <zen/function/fuse.h>
#include <zen/function/is_callable.h>
#include <zen/function/detail/nullary_tr1_result_of.h>

#ifndef ZEN_CONDITIONAL_LIMIT
#define ZEN_CONDITIONAL_LIMIT 16
#endif

namespace zen {

namespace detail {

template<class F1, class F2, class Enable = void>
struct conditional_kernel_base
{
    F1 f1;
    F2 f2;
    conditional_kernel_base() {}

    template<class A, class B>
    conditional_kernel_base(A f1, B f2) : f1(f1), f2(f2)
    {}

    F1 get_function1() const
    {
        return f1;
    }
    F2 get_function2() const
    {
        return f2;
    }
};

template<class F1, class F2>
struct conditional_kernel_base<F1, F2, ZEN_CLASS_REQUIRES(boost::is_empty<F1>, boost::is_empty<F2>)>
{
    conditional_kernel_base() {}

    template<class A, class B>
    conditional_kernel_base(A, B)
    {}

    F1 get_function1() const
    {
        return F1();
    }
    F2 get_function2() const
    {
        return F2();
    }
};

template<class F1, class F2>
struct conditional_kernel : conditional_kernel_base<F1, F2>
{
    // typedef void zen_is_callable_by_result_tag;
    conditional_kernel() {}

    template<class A, class B>
    conditional_kernel(A f1, B f2) : conditional_kernel_base<F1, F2>(f1, f2)
    {}

    template<class X>
    struct result;

    template<class X, class T>
    struct result<X(T)>
    : boost::mpl::eval_if
    <
        is_callable<F1(T)>, 
        zen::result_of<F1(T)>, 
        zen::result_of<F2(T)> 
    >
    {};

    template<class T>
    typename zen::result_of<F1(const T&)>::type 
    operator()(const T& t) const
    {
        return this->get_function1()(t);
    }

    template<class T>
    ZEN_FUNCTION_REQUIRES(exclude is_callable<F1(ZEN_FORWARD_REF(T))>)
    (typename zen::result_of<F2(const T&)>::type)
    operator()(const T& t) const
    {
        return this->get_function2()(t);
    }
};

#ifndef ZEN_NO_VARIADIC_TEMPLATES
template<class F, class... Fs>
struct conditional_base : conditional_kernel<F, conditional_base<Fs...> >
{
    conditional_base() {}

    template<class X, class... Xs>
    conditional_base(X f1, Xs... fs) : conditional_kernel<F, conditional_base<Fs...> >(f1, conditional_base<Fs...>(fs...))
    {}

};

#else
template<class T = void, ZEN_PP_PARAMS_Z(1, ZEN_CONDITIONAL_LIMIT, class T, = void BOOST_PP_INTERCEPT)>
struct conditional_base;
#define ZEN_CONDITIONAL_BASE(z, n, data) \
template<class F, ZEN_PP_PARAMS_Z(z, n, class Fs)> \
struct conditional_base<F, ZEN_PP_PARAMS_Z(z, n, Fs)> \
: conditional_kernel<F, conditional_base<ZEN_PP_PARAMS_Z(z, n, Fs)> > \
{ \
    typedef conditional_kernel<F, conditional_base<ZEN_PP_PARAMS_Z(z, n, Fs)> > base; \
    conditional_base() {} \
\
    conditional_base(const conditional_base& rhs) : base(static_cast<const base&>(rhs)) \
    {} \
    template<class X, ZEN_PP_PARAMS_Z(z, n, class Xs)> \
    conditional_base(X f1, ZEN_PP_PARAMS_Z(z, n, Xs, fs)) \
    : conditional_kernel<F, conditional_base<ZEN_PP_PARAMS_Z(z, n, Fs)> >(f1, conditional_base<ZEN_PP_PARAMS_Z(z, n, Fs)>(ZEN_PP_PARAMS_Z(z, n, fs))) \
    {} \
};
BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_CONDITIONAL_LIMIT, ZEN_CONDITIONAL_BASE, ~)
#endif

template<class F>
struct conditional_base<F> : function_adaptor_base<F>
{
    // typedef void zen_is_callable_by_result_tag;
    typedef function_adaptor_base<F> base;
    conditional_base() {}

    // MSVC Workaround
    conditional_base(const conditional_base& rhs) : base(static_cast<const base&>(rhs))
    {}

    template<class X>
    conditional_base(X f) : function_adaptor_base<F>(f)
    {}

    template<class X>
    struct result;

    template<class X, class T>
    struct result<X(T)>
    : zen::result_of<F(T)>
    {};

    template<class T>
    typename zen::result_of<F(const T&)>::type 
    operator()(const T& t) const
    {
        return this->get_function()(t);
    }
};

}

#ifndef ZEN_NO_VARIADIC_TEMPLATES
template<class... Fs>
struct conditional_adaptor : variadic_adaptor<detail::conditional_base<fuse_adaptor<Fs>...> >
{
    conditional_adaptor() {}

    template<class... X>
    conditional_adaptor(X... fs) : variadic_adaptor<detail::conditional_base<fuse_adaptor<Fs>...> >(detail::conditional_base<fuse_adaptor<Fs>...>(fs...))
    {}

    //auto get_primary_function() const ZEN_RETURNS(this->get_function().get_function().get_function1().get_function());
};

template<class... Fs>
conditional_adaptor<Fs...> conditional(Fs... fs)
{
    return conditional_adaptor<Fs...>(fs...);
}
#else
namespace detail {

template<class F>
struct conditional_fuse
{
    typedef fuse_adaptor<F> type;
};

template<>
struct conditional_fuse<void>
{
    typedef void type;
};

}


template<ZEN_PP_PARAMS_Z(1, ZEN_CONDITIONAL_LIMIT, class Fs, = void BOOST_PP_INTERCEPT)>
struct conditional_adaptor 
: variadic_adaptor<detail::conditional_base<ZEN_PP_PARAMS_Z(1, ZEN_CONDITIONAL_LIMIT, typename detail::conditional_fuse<Fs,>::type BOOST_PP_INTERCEPT)> >
{
    typedef variadic_adaptor<detail::conditional_base<ZEN_PP_PARAMS_Z(1, ZEN_CONDITIONAL_LIMIT, typename detail::conditional_fuse<Fs,>::type BOOST_PP_INTERCEPT)> > base;
    conditional_adaptor() {}

    // MSVC Workaround
    conditional_adaptor(const conditional_adaptor& rhs) : base(static_cast<const base&>(rhs))
    {}

#define ZEN_CONDITIONAL_ADAPTOR_CONSTRUTOR(z, n, data) \
    template<ZEN_PP_PARAMS_Z(z, n, class X)> \
    conditional_adaptor(ZEN_PP_PARAMS_Z(z, n, X, fs)) \
    : variadic_adaptor<detail::conditional_base<ZEN_PP_PARAMS_Z(z, ZEN_CONDITIONAL_LIMIT, typename detail::conditional_fuse<Fs,>::type BOOST_PP_INTERCEPT)> > \
    (detail::conditional_base<ZEN_PP_PARAMS_Z(z, ZEN_CONDITIONAL_LIMIT, typename detail::conditional_fuse<Fs,>::type BOOST_PP_INTERCEPT)>(ZEN_PP_PARAMS_Z(z, n, fs))) \
    {}
    BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_CONDITIONAL_LIMIT, ZEN_CONDITIONAL_ADAPTOR_CONSTRUTOR, ~)
};

#define ZEN_CONDITIONAL_FUNCTION(z, n, data) \
template<ZEN_PP_PARAMS_Z(z, n, class Fs)> \
conditional_adaptor<ZEN_PP_PARAMS_Z(z, n, Fs)> conditional(ZEN_PP_PARAMS_Z(z, n, Fs, fs)) \
{ \
    return conditional_adaptor<ZEN_PP_PARAMS_Z(z, n, Fs)>(ZEN_PP_PARAMS_Z(z, n, fs)); \
}
BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_CONDITIONAL_LIMIT, ZEN_CONDITIONAL_FUNCTION, ~)

#endif

}

ZEN_NULLARY_TR1_RESULT_OF_N(ZEN_CONDITIONAL_LIMIT, zen::conditional_adaptor)

#endif
