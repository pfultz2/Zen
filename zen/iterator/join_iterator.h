/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    join_iterator.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ITERATOR_JOIN_ITERATOR_H
#define ZEN_GUARD_ITERATOR_JOIN_ITERATOR_H

#include <zen/iterator/minimum_traversal.h>
#include <zen/function/result_of.h>
#include <zen/typeof.h>
#include <boost/range.hpp>
#include <boost/mpl/if.hpp>

namespace zen {

template< class IteratorL, class IteratorR>
struct join_iterator;

namespace detail {

template<class T, class U>
struct common_type
: boost::mpl::if_<boost::is_convertible<U, T>, T, U>
{};


template< class IteratorL, class IteratorR >
void join_increment(IteratorL& itL, IteratorR& itR, IteratorL lastL)
{
    if (itL != lastL)
        ++itL;
    else
        ++itR;
}


template< class Difference, class IteratorL, class IteratorR >
void join_advance(IteratorL& itL, IteratorR& itR, Difference n, IteratorL lastL)
{
    ZEN_ASSERT(n >= 0);

    if (itL != lastL) {
        Difference dL = lastL - itL;
        if (n > dL) {
            itL = lastL;
            itR += n - dL;
        }
        else {
            itL += n;
        }
    }
    else {
        itR += n;
    }
}



template< class IteratorL, class IteratorR >
struct join_iterator_base
{
    typedef typename common_type
    <
        typename boost::iterator_reference<IteratorL>::type,
        typename boost::iterator_reference<IteratorR>::type
    >::type Reference;
    typedef
    boost::iterator_adaptor
    <
        join_iterator<IteratorL, IteratorR>,
        IteratorL,
        typename boost::remove_reference<Reference>,
        typename minimum_traversal
        <
            typename boost::iterator_traversal<IteratorL>::type,
            typename boost::iterator_traversal<IteratorR>::type
        >::type,
        Reference
    >
    type;
};

}

template< class IteratorL, class IteratorR>
struct join_iterator 
: detail::join_iterator_base<IteratorL, IteratorR>::type
{
    typedef typename detail::join_iterator_base<IteratorL, IteratorR>::type iterator_base;
    typedef typename iterator_base::reference reference;
    typedef typename iterator_base::difference_type difference_type;

    join_iterator()
    { }

    join_iterator(
        IteratorL itL, IteratorL lastL,
        IteratorR firstR, IteratorR itR
    ) :
        iterator_base(itL), lastL(lastL),
        firstR(firstR), itR(itR)
    {
        ZEN_ASSERT(this->invariant());
    }

    template<class IL, class IR>
    join_iterator(join_iterator<IL, IR> const& other,
        ZEN_CLASS_REQUIRES(boost::is_convertible<IL, IteratorL>)* * = 0,
        ZEN_CLASS_REQUIRES(boost::is_convertible<IR, IteratorR>)* * = 0
    ) :
        iterator_base(other.base()), lastL(other.lastL), 
        firstR(other.firstR), itR(other.itR)
    {
        ZEN_ASSERT(this->invariant());
    }

    IteratorL lastL; IteratorR firstR; // the join point
    IteratorR itR;

    IteratorR right_base() const
    {
        return this->itR;
    }

    bool is_in_left() const
    {
        return this->base() != this->lastL;
    }

    bool invariant() const
    {
        return is_in_left() ? (this->itR == this->firstR) : true;
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return this->lastL == other.lastL && this->firstR == other.firstR;
    }

    reference dereference() const
    {
        ZEN_ASSERT(this->invariant());
        // Keep writability without 'read'.
        if (is_in_left())
            return *this->base();
        else
            return *this->itR;
    }

    template< class IL, class IR >
    bool equal(join_iterator<IL, IR> const& other) const
    {
        ZEN_ASSERT(is_compatible(other));

        return this->base() == other.base() && this->itR == other.itR;
    }

    void increment()
    {
        detail::join_increment(this->base_reference(), this->itR, this->lastL);
    }

    void decrement()
    {
        boost::reverse_iterator<IteratorR> itL(this->itR), lastL(this->firstR);
        boost::reverse_iterator<IteratorL> itR(this->base());
        detail::join_increment(itL, itR, lastL);
        this->base_reference() = itR.base();
        this->itR = itL.base();
    }

    void advance(difference_type n)
    {
        if (n >= 0) 
        {
            detail::join_advance(this->base_reference(), this->itR, n, this->lastL);
        }
        else 
        {
            boost::reverse_iterator<IteratorR> ritL(this->itR), rlastL(this->firstR);
            boost::reverse_iterator<IteratorL> ritR(this->base());
            detail::join_advance(ritL, ritR, -n, rlastL);
            this->base_reference() = ritR.base();
            this->itR = ritL.base();
        }
    }

    template< class IL, class IR >
    difference_type distance_to(join_iterator<IL, IR> const& other) const
    {
        ZEN_ASSERT(is_compatible(other));

        if (is_in_left() && other.is_in_left())
            return other.base() - this->base();
        else if (!is_in_left() && !other.is_in_left())
            return other.itR - this->itR;
        else if (is_in_left())
            return (this->lastL - this->base()) + (other.itR - other.firstR);
        else 
        {
            ZEN_ASSERT(!is_in_left());
            return (this->firstR - this->itR) + (other.base() - other.m_lastL);
        }
    }
};

template<class IteratorL, class IteratorR>
join_iterator<IteratorL, IteratorR> make_join_iterator(IteratorL itL, IteratorL lastL, IteratorR firstR, IteratorR itR)
{
    return join_iterator<IteratorL, IteratorR>(itL, lastL, firstR, itR);
}


}

#endif
