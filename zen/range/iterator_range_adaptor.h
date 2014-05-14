/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    iterator_range_adaptor.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_ITERATOR_RANGE_ADAPTOR_H
#define ZEN_GUARD_RANGE_ITERATOR_RANGE_ADAPTOR_H

#include <zen/range/detail/range_adaptor_base.h>

namespace zen {

template<class Begin, class End=void>
class iterator_range_invoke
: Begin, End 
{
public:
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

template<class Begin, class End>
auto make_iterator_range_invoke(Begin b, End e)
{
    return iterator_range_invoke<Begin, End>(b, e);
}

template<class F>
class iterator_range_invoke<F, void>
: F 
{
public:
    template<class X>
    iterator_range_invoke(X f)
    : F(f)
    {}

    template<class Self>
    decltype(auto) invoke_begin(Self&& self) const
    {
        return static_cast<const F&>(*this)(std::forward<Self>(self), [&]{ self.base_begin(); });
    }

    template<class Self>
    decltype(auto) invoke_end(Self&& self) const
    {
        return static_cast<const F&>(*this)(std::forward<Self>(self), [&]{ self.base_end(); });
    }
};

template<class F>
auto make_iterator_range_invoke(F f)
{
    return iterator_range_invoke<F>(f);
}



template<class Range, class Invoke>
struct iterator_range_adaptor
: detail::range_adaptor_base<Range>, Invoke
{
    typedef detail::range_adaptor_base<Range> range_adaptor_base;

    template<class R, class I>
    iterator_range_adaptor(R&& r, I i)
    : range_adaptor_base(std::forward<R>(r)), Invoke(i)
    {}

    decltype(auto) begin()
    {
        return this->invoke_begin(this->get_range_adaptor_base());
    }

    decltype(auto) end()
    {
        return this->invoke_end(this->get_range_adaptor_base());
    }

    decltype(auto) begin() const
    {
        return this->invoke_begin(this->get_range_adaptor_base());
    }

    decltype(auto) end() const
    {
        return this->invoke_end(this->get_range_adaptor_base());
    }

    typedef decltype(std::declval<Invoke>().invoke_begin(std::declval<range_adaptor_base>())) iterator;
    typedef decltype(std::declval<Invoke>().invoke_begin(std::declval<const range_adaptor_base>())) const_iterator;

private:
    range_adaptor_base& get_range_adaptor_base()
    {
        return *this;
    }

    const range_adaptor_base& get_range_adaptor_base() const
    {
        return *this;
    }
};

template<class Range, class Invoke>
auto make_iterator_range_adaptor(Range&& r, Invoke i)
{
    return iterator_range_adaptor<Range, Invoke>(std::forward<Range>(r), i);
}

}


#endif