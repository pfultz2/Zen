/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    iterator_range_adaptor.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_ITERATOR_RANGE_ADAPTOR_H
#define ZEN_GUARD_RANGE_ITERATOR_RANGE_ADAPTOR_H

#include <zen/range/detail/range_adaptor_base.h>
#include <zen/make.h>

namespace zen {

template<class Begin, class End=void>
struct iterator_range_invoke : Begin, End 
{
    template<class B, class E>
    iterator_range_invoke(B b, E e)
    : Begin(b), End(e)
    {}

    template<class Self>
    decltype(auto) invoke_begin(Self&& self) const
    {
        return static_cast<const Begin&>(*this)(std::forward<Self>(self));
    }

    template<class Self>
    decltype(auto) invoke_end(Self&& self) const
    {
        return static_cast<const End&>(*this)(std::forward<Self>(self));
    }
};

template<class F>
struct iterator_range_invoke<F, void> : F 
{
    template<class... Ts>
    iterator_range_invoke(Ts&&... xs)
    : F(std::forward<Ts>(xs)...)
    {}

    template<class Self>
    decltype(auto) invoke_begin(Self&& self) const
    {
        return static_cast<const F&>(*this)(std::forward<Self>(self), [&]{ return self.base_begin(); });
    }

    template<class Self>
    decltype(auto) invoke_end(Self&& self) const
    {
        return static_cast<const F&>(*this)(std::forward<Self>(self), [&]{ return self.base_end(); });
    }
};

namespace detail {

template<class Range, class Invoke>
struct iterator_range_adaptor_base
: detail::range_adaptor_base<Range>, zen::bare<Invoke>::type
{
    typedef detail::range_adaptor_base<Range> range_adaptor_base;
    typedef typename zen::bare<Invoke>::type invoke_base;

    template<class R, class... Ts>
    iterator_range_adaptor_base(R&& r, Ts&&... xs)
    : range_adaptor_base(std::forward<R>(r)), invoke_base(std::forward<Ts>(xs)...)
    {}
};

}


template<class Range, class Invoke>
struct iterator_range_adaptor
: detail::iterator_range_adaptor_base<Range, Invoke>
{
    typedef detail::iterator_range_adaptor_base<Range, Invoke> super;
    ZEN_DISABLE_MAKE();

    template<class R, class... Ts>
    iterator_range_adaptor(R&& r, Ts&&... xs)
    : super(std::forward<R>(r), std::forward<Ts>(xs)...)
    {}

    decltype(auto) begin()
    {
        return this->invoke_begin(this->get_iterator_range_adaptor());
    }

    decltype(auto) end()
    {
        return this->invoke_end(this->get_iterator_range_adaptor());
    }

    decltype(auto) begin() const
    {
        return this->invoke_begin(this->get_iterator_range_adaptor());
    }

    decltype(auto) end() const
    {
        return this->invoke_end(this->get_iterator_range_adaptor());
    }

    typedef decltype(std::declval<super>().invoke_begin(std::declval<super>())) iterator;
    typedef decltype(std::declval<super>().invoke_begin(std::declval<const super>())) const_iterator;

private:
    super& get_iterator_range_adaptor()
    {
        return *this;
    }

    const super& get_iterator_range_adaptor() const
    {
        return *this;
    }
};


}


#endif