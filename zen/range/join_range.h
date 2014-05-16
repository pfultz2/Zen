/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    join_range.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_JOIN_RANGE_H
#define ZEN_GUARD_JOIN_RANGE_H

#include <zen/range/iterator_range.h>
#include <zen/range/iterator_range_adaptor.h>
#include <boost/iterator/iterator_adaptor.hpp>
#include <zen/make.h>
#include <zen/function/reveal.h>

namespace zen {

namespace detail {

template<class T, class U>
struct join_common_type
: boost::mpl::if_<std::is_convertible<U, T>, T, U>
{}; 

template<class Tail>
struct join_range_base
{
    detail::range_adaptor_base<Tail> tail;
    template<class X, ZEN_REQUIRES(not std::is_same<join_range_base, bare_t<X>>())>
    join_range_base(X&& x) : tail(std::forward<X>(x))
    {}

    template< class IteratorL, class IteratorR, class JoinRange>
    struct join_iterator;

    template< class IteratorL, class IteratorR, class JoinRange >
    struct join_iterator_base
    {
        typedef typename join_common_type
        <
            typename zen::iterator_reference<IteratorL>::type,
            typename zen::iterator_reference<IteratorR>::type
        >::type Reference;

        typedef typename boost::mpl::eval_if_c<(is_advanceable_iterator<IteratorL>() and is_advanceable_iterator<IteratorR>()),
                    boost::mpl::identity<boost::random_access_traversal_tag>,
                    boost::mpl::if_c<(is_reversible_iterator<IteratorL>() and is_reversible_iterator<IteratorR>()),
                        boost::bidirectional_traversal_tag,
                        boost::forward_traversal_tag
                    >
                >::type traversal_type;

        typedef
        boost::iterator_adaptor
        <
            join_iterator<IteratorL, IteratorR, JoinRange>,
            IteratorL,
            typename boost::remove_reference<Reference>,
            traversal_type,
            Reference
        >
        type;
    };


    template< class IteratorL, class IteratorR, class JoinRange>
    struct join_iterator 
    : join_iterator_base<IteratorL, IteratorR, JoinRange>::type
    {
        typedef typename join_iterator_base<IteratorL, IteratorR, JoinRange>::type iterator_base;
        typedef typename iterator_base::reference reference;
        typedef typename iterator_base::difference_type difference_type;

        IteratorR itR;
        JoinRange * self;

        join_iterator()
        { }

        join_iterator(IteratorL itL, IteratorR itR, JoinRange& jr) 
        : iterator_base(itL), itR(itR), self(&jr)
        {
            ZEN_ASSERT(this->invariant());
        }

        template<class IL, class IR>
        join_iterator(join_iterator<IL, IR, JoinRange> const& other,
            ZEN_REQUIRES_CONVERTIBLE(IL, IteratorL),
            ZEN_REQUIRES_CONVERTIBLE(IR, IteratorR)
        ) : iterator_base(other.base()), itR(other.itR), self(other.self)
        {
            ZEN_ASSERT(this->invariant());
        }

        bool is_in_left() const
        {
            return this->base() != this->self->base_end();
        }

        bool is_joint() const
        {
            return this->itR == this->self->tail.base_begin();
        }

        bool invariant() const
        {
            return is_in_left() ? (is_joint()) : true;
        }

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            return this->self == other.self;
        }

        reference dereference() const
        {
            ZEN_ASSERT(this->invariant());
            // Keep writability without 'read'.
            if (is_in_left()) return *this->base();
            else return *this->itR;
        }

        template< class IL, class IR, class JR >
        bool equal(join_iterator<IL, IR, JR> const& other) const
        {
            ZEN_ASSERT(is_compatible(other));

            return this->base() == other.base() && this->itR == other.itR;
        }

        void increment()
        {
            if (is_in_left()) ++this->base_reference();
            else ++this->itR;
            ZEN_ASSERT(this->invariant());
        }

        void decrement()
        {
            if (is_in_left() or is_joint()) --this->base_reference();
            else --this->itR;
            ZEN_ASSERT(this->invariant());
        }

        void advance(difference_type n)
        {
            if (n >= 0) 
            {
                // detail::join_advance(this->base_reference(), this->itR, n, this->lastL);
                if (is_in_left()) 
                {
                    difference_type dL = this->lastL - this->base_reference();
                    if (n > dL) 
                    {
                        this->base_reference() = this->lastL;
                        this->itR += n - dL;
                    }
                    else 
                    {
                        this->base_reference() += n;
                    }
                }
                else 
                {
                    this->itR += n;
                }
            }
            else 
            {
                if (is_in_left() or is_joint()) 
                {
                    this->base_reference() += n;
                }
                else 
                {
                    auto firstR = this->self->tail.base_begin();
                    difference_type dR = -(this->itR - firstR);
                    if (n < dR) 
                    {
                        this->itR = firstR;
                        this->base_reference() += n - dR;
                    }
                    else 
                    {
                        this->itR += n;
                    }
                }
            }
            ZEN_ASSERT(this->invariant());
        }

        template< class IL, class IR, class JR >
        difference_type distance_to(join_iterator<IL, IR, JR> const& other) const
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

    template<class IteratorL, class IteratorR, class JoinRange>
    static auto make_join_iterator(IteratorL il, IteratorR ir, JoinRange & jr)
    {
        return join_iterator<IteratorL, IteratorR, JoinRange>(il, ir, jr);
    }

    template<class Self>
    auto invoke_begin(Self&& self) const
    {
        return make_join_iterator(self.base_begin(), self.tail.base_begin(), self);
    }

    template<class Self>
    auto invoke_end(Self&& self) const
    {
        return make_join_iterator(self.base_end(), self.tail.base_end(), self);
    }
};

}

template<class Range1, class Range2>
using join_range = iterator_range_adaptor<Range1, detail::join_range_base<Range2>>;

}

#endif