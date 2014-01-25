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

#include <zen/function/is_callable.h>
#include <zen/returns.h>
#include <boost/mpl/if.hpp>

namespace zen {

namespace detail {

template<class F1, class F2>
struct conditional_kernel : F1, F2
{
    conditional_kernel() {}

    template<class A, class B>
    conditional_kernel(A f1, B f2) : F1(f1), F2(f2)
    {}

    template<class... T>
    struct select
    : boost::mpl::if_
    <
        is_callable<F1(T...)>, 
        F1,
        F2
    >
    {};

    template<class... T>
    const typename select<T...>::type& select_function() const
    {
        return *this;
    }

    template<class... T>
    auto operator()(T && ... x) const
    ZEN_RETURNS(this->select_function<T&&...>()(std::forward<T>(x)...));
};
}

template<class F, class... Fs>
struct conditional_adaptor : detail::conditional_kernel<F, conditional_adaptor<Fs...> >
{
    conditional_adaptor() {}

    template<class X, class... Xs>
    conditional_adaptor(X && f1, Xs && ... fs) 
    : detail::conditional_kernel<F, conditional_adaptor<Fs...> >(std::forward<X>(f1), std::forward<Xs>(fs)...)
    {}

};

template<class F>
struct conditional_adaptor<F> : F
{
    conditional_adaptor() {}

    template<class X>
    conditional_adaptor(X && f1) 
    : F(std::forward<X>(f1))
    {}

};

template<class... Fs>
conditional_adaptor<Fs...> conditional(Fs... fs)
{
    return conditional_adaptor<Fs...>(fs...);
}

}

#endif
