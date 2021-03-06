/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    perfect_facade.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_C03_PERFECT_FACADE_H
#define ZEN_GUARD_C03_PERFECT_FACADE_H

#include <zen/pp.h>
#include <zen/config.h>
#include <zen/function/result_of.h>
#include <zen/forward.h>

#ifndef ZEN_PERFECT_FACADE_DONT_PREPROCESS

#if ZEN_PARAMS_LIMIT >= 12
#include <zen/function/detail/c03/perfect_facade_12.h>
#elif ZEN_PARAMS_LIMIT >= 10
#include <zen/function/detail/c03/perfect_facade_10.h>
#elif ZEN_PARAMS_LIMIT >= 8
#include <zen/function/detail/c03/perfect_facade_8.h>
#elif ZEN_PARAMS_LIMIT <= 6
#include <zen/function/detail/c03/perfect_facade_6.h>
#endif

#else
// (()())       ((const)())
// (()(const))  ((const)(const))

#define ZEN_PERFECT_ITERATE_END(...) ZEN_PERFECT_ITERATE_END_I(__VA_ARGS__)
#define ZEN_PERFECT_ITERATE_END_I(...) __VA_ARGS__ ## _EOF

#define ZEN_PERFECT_PRODUCT_SEQ(n) BOOST_PP_CAT(ZEN_PERFECT_PRODUCT_SEQ_, n)((())((const)))
#define ZEN_PERFECT_PRODUCT_SEQ_1(x) x
#define ZEN_PERFECT_PRODUCT_SEQ_2(x) ZEN_PERFECT_PRODUCT_SEQ_1(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_3(x) ZEN_PERFECT_PRODUCT_SEQ_2(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_4(x) ZEN_PERFECT_PRODUCT_SEQ_3(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_5(x) ZEN_PERFECT_PRODUCT_SEQ_4(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_6(x) ZEN_PERFECT_PRODUCT_SEQ_5(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_7(x) ZEN_PERFECT_PRODUCT_SEQ_6(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_8(x) ZEN_PERFECT_PRODUCT_SEQ_7(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_9(x) ZEN_PERFECT_PRODUCT_SEQ_8(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_10(x) ZEN_PERFECT_PRODUCT_SEQ_9(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_11(x) ZEN_PERFECT_PRODUCT_SEQ_10(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_12(x) ZEN_PERFECT_PRODUCT_SEQ_11(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_13(x) ZEN_PERFECT_PRODUCT_SEQ_12(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_14(x) ZEN_PERFECT_PRODUCT_SEQ_13(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_15(x) ZEN_PERFECT_PRODUCT_SEQ_14(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_16(x) ZEN_PERFECT_PRODUCT_SEQ_15(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_17(x) ZEN_PERFECT_PRODUCT_SEQ_16(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_18(x) ZEN_PERFECT_PRODUCT_SEQ_17(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_19(x) ZEN_PERFECT_PRODUCT_SEQ_18(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))
#define ZEN_PERFECT_PRODUCT_SEQ_20(x) ZEN_PERFECT_PRODUCT_SEQ_20(ZEN_PERFECT_PRODUCT_SEQ_STEP(x))

#define ZEN_PERFECT_PRODUCT_SEQ_STEP(seq) ZEN_PERFECT_ITERATE_END(ZEN_PERFECT_PRODUCT_SEQ_STEP_1 seq) 
#define ZEN_PERFECT_PRODUCT_SEQ_STEP_1(tail) (() tail) ((const) tail) ZEN_PERFECT_PRODUCT_SEQ_STEP_2
#define ZEN_PERFECT_PRODUCT_SEQ_STEP_2(tail) (() tail) ((const) tail) ZEN_PERFECT_PRODUCT_SEQ_STEP_1
#define ZEN_PERFECT_PRODUCT_SEQ_STEP_1_EOF
#define ZEN_PERFECT_PRODUCT_SEQ_STEP_2_EOF


#define ZEN_PERFECT_FACADE_SEQ(seq) ZEN_PP_EXPAND(ZEN_PERFECT_ITERATE_END(ZEN_PERFECT_FACADE_SEQ_1 seq))
#define ZEN_PERFECT_FACADE_SEQ_1(seq) ZEN_PP_OBSTRUCT(ZEN_PERFECT_FACADE_OP)(BOOST_PP_SEQ_SIZE(seq), seq) ZEN_PERFECT_FACADE_SEQ_2
#define ZEN_PERFECT_FACADE_SEQ_2(seq) ZEN_PP_OBSTRUCT(ZEN_PERFECT_FACADE_OP)(BOOST_PP_SEQ_SIZE(seq), seq) ZEN_PERFECT_FACADE_SEQ_1
#define ZEN_PERFECT_FACADE_SEQ_1_EOF
#define ZEN_PERFECT_FACADE_SEQ_2_EOF

#define ZEN_PERFECT_FACADE_PARAMS_R(r, seq, ...) BOOST_PP_SEQ_FOR_EACH_I_R(r, ZEN_PERFECT_FACADE_PARAMS_EACH, (__VA_ARGS__), seq) 
#define ZEN_PERFECT_FACADE_PARAMS_EACH(r, data, i, const_) BOOST_PP_COMMA_IF(i) const_ ZEN_PP_VARN_CAT(i, data)

#define ZEN_PERFECT_FACADE_FORWARD_R(r, seq, T, x) BOOST_PP_SEQ_FOR_EACH_I_R(r, ZEN_PERFECT_FACADE_FORWARD_EACH, (T, x), seq)
#define ZEN_PERFECT_FACADE_FORWARD_EACH(r, data, i, const_) BOOST_PP_COMMA_IF(i) \
zen::forward<const_ BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 0, data), i)>\
( BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 1, data), i) )

#define ZEN_PERFECT_FACADE_OP(n, seq) \
template<ZEN_PP_PARAMS_Z(2, n, class T)> \
typename zen::result_of<zen_private_perfect_facade_function_type(ZEN_PERFECT_FACADE_PARAMS_R(1, seq, T, & BOOST_PP_INTERCEPT))>::type \
operator()(ZEN_PERFECT_FACADE_PARAMS_R(1, seq, T, & x)) const \
{ return this->zen_private_perfect_facade_function()( ZEN_PERFECT_FACADE_FORWARD_R(1, seq, T, x) ); }

#define ZEN_DETAIL_PERFECT_FACADE(z, n, data) \
ZEN_PERFECT_FACADE_SEQ(ZEN_PERFECT_PRODUCT_SEQ(n))

#define ZEN_PERFECT_FACADE(type, f) \
typedef type zen_private_perfect_facade_function_type; \
type zen_private_perfect_facade_function() const \
{ \
    return f; \
} \
BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_PARAMS_LIMIT, ZEN_DETAIL_PERFECT_FACADE, ~)

// Template parameters
#define ZEN_PERFECT_FACADE_SEQ_TPL(tpl, seq) ZEN_PERFECT_ITERATE_END(ZEN_PERFECT_FACADE_SEQ_1_ ## tpl seq)
#define ZEN_PERFECT_FACADE_SEQ_1_class(seq) ZEN_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZEN_PERFECT_FACADE_SEQ_2_class
#define ZEN_PERFECT_FACADE_SEQ_2_class(seq) ZEN_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZEN_PERFECT_FACADE_SEQ_1_class
#define ZEN_PERFECT_FACADE_SEQ_1_class_EOF
#define ZEN_PERFECT_FACADE_SEQ_2_class_EOF

#define ZEN_PERFECT_FACADE_SEQ_1_int(seq) ZEN_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZEN_PERFECT_FACADE_SEQ_2_int
#define ZEN_PERFECT_FACADE_SEQ_2_int(seq) ZEN_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZEN_PERFECT_FACADE_SEQ_1_int
#define ZEN_PERFECT_FACADE_SEQ_1_int_EOF
#define ZEN_PERFECT_FACADE_SEQ_2_int_EOF

#define ZEN_PERFECT_FACADE_SEQ_1_long(seq) ZEN_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZEN_PERFECT_FACADE_SEQ_2_long
#define ZEN_PERFECT_FACADE_SEQ_2_long(seq) ZEN_PERFECT_FACADE_OP(BOOST_PP_SEQ_SIZE(seq), seq) ZEN_PERFECT_FACADE_SEQ_1_long
#define ZEN_PERFECT_FACADE_SEQ_1_long_EOF
#define ZEN_PERFECT_FACADE_SEQ_2_long_EOF

#define ZEN_PERFECT_FACADE_OP_TPL(tpl, n, seq) \
template<tpl T_ ## tpl, ZEN_PP_PARAMS_Z(2, n, class T)> \
typename zen::result_of<typename zen_private_perfect_facade_function_type<T_ ## tpl>::type(ZEN_PERFECT_FACADE_PARAMS_R(1, seq, T, & BOOST_PP_INTERCEPT))>::type \
operator()(ZEN_PERFECT_FACADE_PARAMS_R(1, seq, T, & x)) const \
{ return this->zen_private_perfect_facade_function<T_ ## tpl>()( ZEN_PERFECT_FACADE_FORWARD_R(1, seq, T, x) ); }

#define ZEN_DETAIL_PERFECT_FACADE_TPL(z, n, tpl) \
ZEN_PERFECT_FACADE_SEQ_TPL(tpl, ZEN_PERFECT_PRODUCT_SEQ(n))

#define ZEN_PERFECT_FACADE_TPL(type_, f, tpl) \
template<tpl T_ ## tpl> \
struct zen_private_perfect_facade_function_type { typedef type_ type; }; \
typedef type zen_private_perfect_facade_function_type; \
template<tpl T_ ## tpl> \
type_ zen_private_perfect_facade_function() const \
{ \
    return f; \
} \
BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_PARAMS_LIMIT, ZEN_DETAIL_PERFECT_FACADE_TPL, tpl)

#endif

#endif
