/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    pp.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_PP_H
#define ZEN_GUARD_PP_H

//#define BOOST_PP_VARIADICS 1
#include <boost/preprocessor.hpp>
//#include <boost/preprocessor/variadic.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/detail/is_nullary.hpp>
//#include <boost/preprocessor/facilities/overload.hpp>

//
// ZEN_PP_MSVC_INVOKE invokes a macro on msvc
//
#define ZEN_PP_MSVC_INVOKE BOOST_PP_CAT(ZEN_PP_MSVC_INVOKE_, BOOST_PP_AUTO_REC(ZEN_PP_DETAIL_MSVC_INVOKE_P, 16))

#define ZEN_PP_DETAIL_MSVC_INVOKE_P(n) BOOST_PP_IS_NULLARY( ZEN_PP_MSVC_INVOKE_ ## n((),) )

#define ZEN_PP_MSVC_INVOKE_1(macro, args)  ZEN_PP_MSVC_INVOKE_I_1(macro, args)
#define ZEN_PP_MSVC_INVOKE_2(macro, args)  ZEN_PP_MSVC_INVOKE_I_2(macro, args)
#define ZEN_PP_MSVC_INVOKE_3(macro, args)  ZEN_PP_MSVC_INVOKE_I_3(macro, args)
#define ZEN_PP_MSVC_INVOKE_4(macro, args)  ZEN_PP_MSVC_INVOKE_I_4(macro, args)
#define ZEN_PP_MSVC_INVOKE_5(macro, args)  ZEN_PP_MSVC_INVOKE_I_5(macro, args)
#define ZEN_PP_MSVC_INVOKE_6(macro, args)  ZEN_PP_MSVC_INVOKE_I_6(macro, args)
#define ZEN_PP_MSVC_INVOKE_7(macro, args)  ZEN_PP_MSVC_INVOKE_I_7(macro, args)
#define ZEN_PP_MSVC_INVOKE_8(macro, args)  ZEN_PP_MSVC_INVOKE_I_8(macro, args)
#define ZEN_PP_MSVC_INVOKE_9(macro, args)  ZEN_PP_MSVC_INVOKE_I_9(macro, args)
#define ZEN_PP_MSVC_INVOKE_10(macro, args) ZEN_PP_MSVC_INVOKE_I_10(macro, args)
#define ZEN_PP_MSVC_INVOKE_11(macro, args) ZEN_PP_MSVC_INVOKE_I_11(macro, args)
#define ZEN_PP_MSVC_INVOKE_12(macro, args) ZEN_PP_MSVC_INVOKE_I_12(macro, args)
#define ZEN_PP_MSVC_INVOKE_13(macro, args) ZEN_PP_MSVC_INVOKE_I_13(macro, args)
#define ZEN_PP_MSVC_INVOKE_14(macro, args) ZEN_PP_MSVC_INVOKE_I_14(macro, args)
#define ZEN_PP_MSVC_INVOKE_15(macro, args) ZEN_PP_MSVC_INVOKE_I_15(macro, args)
#define ZEN_PP_MSVC_INVOKE_16(macro, args) ZEN_PP_MSVC_INVOKE_I_16(macro, args)

#define ZEN_PP_MSVC_INVOKE_I_1(macro, args)  ZEN_PP_MSVC_INVOKE_X_1(macro args)
#define ZEN_PP_MSVC_INVOKE_I_2(macro, args)  ZEN_PP_MSVC_INVOKE_X_2(macro args)
#define ZEN_PP_MSVC_INVOKE_I_3(macro, args)  ZEN_PP_MSVC_INVOKE_X_3(macro args)
#define ZEN_PP_MSVC_INVOKE_I_4(macro, args)  ZEN_PP_MSVC_INVOKE_X_4(macro args)
#define ZEN_PP_MSVC_INVOKE_I_5(macro, args)  ZEN_PP_MSVC_INVOKE_X_5(macro args)
#define ZEN_PP_MSVC_INVOKE_I_6(macro, args)  ZEN_PP_MSVC_INVOKE_X_6(macro args)
#define ZEN_PP_MSVC_INVOKE_I_7(macro, args)  ZEN_PP_MSVC_INVOKE_X_7(macro args)
#define ZEN_PP_MSVC_INVOKE_I_8(macro, args)  ZEN_PP_MSVC_INVOKE_X_8(macro args)
#define ZEN_PP_MSVC_INVOKE_I_9(macro, args)  ZEN_PP_MSVC_INVOKE_X_9(macro args)
#define ZEN_PP_MSVC_INVOKE_I_10(macro, args) ZEN_PP_MSVC_INVOKE_X_10(macro args)
#define ZEN_PP_MSVC_INVOKE_I_11(macro, args) ZEN_PP_MSVC_INVOKE_X_11(macro args)
#define ZEN_PP_MSVC_INVOKE_I_12(macro, args) ZEN_PP_MSVC_INVOKE_X_12(macro args)
#define ZEN_PP_MSVC_INVOKE_I_13(macro, args) ZEN_PP_MSVC_INVOKE_X_13(macro args)
#define ZEN_PP_MSVC_INVOKE_I_14(macro, args) ZEN_PP_MSVC_INVOKE_X_14(macro args)
#define ZEN_PP_MSVC_INVOKE_I_15(macro, args) ZEN_PP_MSVC_INVOKE_X_15(macro args)
#define ZEN_PP_MSVC_INVOKE_I_16(macro, args) ZEN_PP_MSVC_INVOKE_X_16(macro args)

#define ZEN_PP_MSVC_INVOKE_X_1(x) x
#define ZEN_PP_MSVC_INVOKE_X_1(x) x
#define ZEN_PP_MSVC_INVOKE_X_2(x) x
#define ZEN_PP_MSVC_INVOKE_X_3(x) x
#define ZEN_PP_MSVC_INVOKE_X_4(x) x
#define ZEN_PP_MSVC_INVOKE_X_5(x) x
#define ZEN_PP_MSVC_INVOKE_X_6(x) x
#define ZEN_PP_MSVC_INVOKE_X_7(x) x
#define ZEN_PP_MSVC_INVOKE_X_8(x) x
#define ZEN_PP_MSVC_INVOKE_X_9(x) x
#define ZEN_PP_MSVC_INVOKE_X_10(x) x
#define ZEN_PP_MSVC_INVOKE_X_11(x) x
#define ZEN_PP_MSVC_INVOKE_X_12(x) x
#define ZEN_PP_MSVC_INVOKE_X_13(x) x
#define ZEN_PP_MSVC_INVOKE_X_14(x) x
#define ZEN_PP_MSVC_INVOKE_X_15(x) x
#define ZEN_PP_MSVC_INVOKE_X_16(x) x

//Utility

// Various utilities
#define ZEN_PP_EAT(...)
#define ZEN_PP_REM(...) __VA_ARGS__
#define ZEN_PP_EXPAND(...) __VA_ARGS__
#define ZEN_PP_EMPTY(...)
#define ZEN_PP_TRUE(...) 1
#define ZEN_PP_FALSE(...) 0
#define ZEN_PP_DEFER(...) __VA_ARGS__ ZEN_PP_EMPTY()
#define ZEN_PP_OBSTRUCT(...) __VA_ARGS__ ZEN_PP_DEFER(ZEN_PP_EMPTY)()
#define ZEN_PP_WHEN(cond) BOOST_PP_IF(cond, ZEN_PP_REM, ZEN_PP_EAT)
 
 /**
 * ZEN_PP_NARGS returns the number of args in __VA_ARGS__
 */

#define ZEN_PP_NARGS(...) \
         ZEN_PP_DETAIL_NARG((__VA_ARGS__,ZEN_PP_DETAIL_RSEQ_N()))
#ifndef _MSC_VER
#define ZEN_PP_DETAIL_NARG(args) \
        ZEN_PP_DETAIL_ARG_N args
#else
#define ZEN_PP_DETAIL_NARG(args) \
        ZEN_PP_MSVC_INVOKE(ZEN_PP_DETAIL_ARG_N, args)
#endif
#define ZEN_PP_DETAIL_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define ZEN_PP_DETAIL_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0 


//
// ZEN_PP_IS_PAREN is used to detect if the first token is a parenthesis.
// It expands to 1 if it is, otherwise it expands to 0.
//
#define ZEN_PP_IS_PAREN(x) ZEN_PP_IS_PAREN_CHECK(ZEN_PP_IS_PAREN_PROBE x)
#ifndef _MSC_VER
#define ZEN_PP_IS_PAREN_CHECK(...) ZEN_PP_IS_PAREN_CHECK_N(__VA_ARGS__,0)
#else
#define ZEN_PP_IS_PAREN_CHECK(...) ZEN_PP_MSVC_INVOKE(ZEN_PP_IS_PAREN_CHECK_N, (__VA_ARGS__,0))
#endif
#define ZEN_PP_IS_PAREN_PROBE(...) ~, 1,
#define ZEN_PP_IS_PAREN_CHECK_N(x, n, ...) n

//
// ZEN_PP_IS_1 is used to detect if the first token is a 1.
// It expands to 1 if it is, otherwise it expands to 0.
//
#define ZEN_PP_IS_1(x) ZEN_PP_IS_PAREN(BOOST_PP_CAT(ZEN_PP_IS_1_PROBE_, x))
#define ZEN_PP_IS_1_PROBE_1 ()


#define ZEN_PP_IS_SINGLE_ARGS(...) ZEN_PP_IS_1(ZEN_PP_NARGS(__VA_ARGS__))

//
// ZEN_PP_IS_EMPTY will expands to 1 if the parameter is empty, otherwise
// it expands to 0. This will work even if the parameter given is a set
// of parenthesis.
//
#define ZEN_PP_IS_EMPTY(x) BOOST_PP_CAT(ZEN_PP_DETAIL_IS_EMPTY_, ZEN_PP_IS_PAREN(x))(x)
#define ZEN_PP_DETAIL_IS_EMPTY_0(x) BOOST_PP_IS_EMPTY(x)
#define ZEN_PP_DETAIL_IS_EMPTY_1(x) 0 

//
// ZEN_PP_HEAD retrieves the first element of a sequence.
// Example:
//
//     ZEN_PP_HEAD((1)(2)(3)) // Expands to (1)
//
#define ZEN_PP_HEAD(x) ZEN_PP_PICK_HEAD(ZEN_PP_MARK x)
#define ZEN_PP_MARK(...) (__VA_ARGS__), 
#define ZEN_PP_PICK_HEAD(...) ZEN_PP_PICK_HEAD_I(__VA_ARGS__,)
#ifndef _MSC_VER
#define ZEN_PP_PICK_HEAD_I(x, ...) x
#else
// MSVC workarounds
#define ZEN_PP_PICK_HEAD_III(x, ...) x
#define ZEN_PP_PICK_HEAD_II(x) ZEN_PP_PICK_HEAD_III x
#define ZEN_PP_PICK_HEAD_I(...) ZEN_PP_PICK_HEAD_II((__VA_ARGS__))
#endif


//
// ZEN_PP_TAIL retrieves the tail of a sequence.
// Example:
//
//     ZEN_PP_TAIL((1)(2)(3)) // Expands to (2)(3)
//
#define ZEN_PP_TAIL(x) ZEN_PP_EAT x



//
// ZEN_PP_STRING_TOKEN
//
#define ZEN_PP_STRING_TOKEN(x) BOOST_PP_IIF(ZEN_PP_IS_PAREN(x), ZEN_PP_STRING_TOKEN_PAREN, ZEN_PP_STRING_TOKEN_KEYWORD)(x)
#define ZEN_PP_STRING_TOKEN_KEYWORD(x) ZEN_PP_STRING_TOKEN_KEYWORD_CHECK(BOOST_PP_CAT(ZEN_PP_STRING_, x), x)
#define ZEN_PP_STRING_TOKEN_KEYWORD_CHECK(tokened, raw) BOOST_PP_IIF(ZEN_PP_IS_PAREN(tokened), tokened, (raw))
#define ZEN_PP_STRING_TOKEN_PAREN(x) (ZEN_PP_HEAD(x)) ZEN_PP_TAIL(x) 

//
// ZEN_PP_STRING_TO_SEQ converts a string into a preprocessor sequence
// 
#define ZEN_PP_STRING_TO_SEQ(x) ZEN_PP_STRING_TO_SEQ_WHILE_M \
( \
    BOOST_PP_WHILE(ZEN_PP_STRING_TO_SEQ_WHILE_P, ZEN_PP_STRING_TO_SEQ_WHILE_O, (,x)) \
)

#define ZEN_PP_STRING_TO_SEQ_WHILE_P(r, state) ZEN_PP_STRING_TO_SEQ_P state
#define ZEN_PP_STRING_TO_SEQ_WHILE_O(r, state) ZEN_PP_STRING_TO_SEQ_O state
#define ZEN_PP_STRING_TO_SEQ_WHILE_M(state) ZEN_PP_STRING_TO_SEQ_M state

#define ZEN_PP_STRING_TO_SEQ_P(prev, tail) BOOST_PP_NOT(ZEN_PP_IS_EMPTY(tail))
#define ZEN_PP_STRING_TO_SEQ_O(prev, tail)  \
   ZEN_PP_STRING_TO_SEQ_REPLACE(prev, ZEN_PP_STRING_TOKEN(tail))

#define ZEN_PP_STRING_TO_SEQ_REPLACE(prev, tail) \
    (prev ZEN_PP_HEAD(tail), ZEN_PP_TAIL(tail))

#define ZEN_PP_STRING_TO_SEQ_M(prev, tail) prev

//
// ZEN_PP_SEQ_TO_STRING outputs the sequence
//
// TODO: Use sequence iteration
#define ZEN_PP_SEQ_TO_STRING(seq) BOOST_PP_SEQ_FOR_EACH(ZEN_PP_SEQ_TO_STRING_EACH, ~, seq) 
#define ZEN_PP_SEQ_TO_STRING_EACH(r, data, x) x 

//
// ZEN_PP_SEQ_SPLIT
//
#define ZEN_PP_SEQ_SPLIT(seq, pred, data) ZEN_DETAIL_PP_SEQ_SPLIT_FOLD_LEFT_M(BOOST_PP_SEQ_FOLD_LEFT(ZEN_DETAIL_PP_SEQ_SPLIT_FOLD_LEFT_O, (pred, data,,), seq))
#define ZEN_DETAIL_PP_SEQ_SPLIT_FOLD_LEFT_O(s, state, x) ZEN_DETAIL_PP_SEQ_SPLIT_FOLD_LEFT_INVOKE((s, x, ZEN_PP_REM state))
#define ZEN_DETAIL_PP_SEQ_SPLIT_FOLD_LEFT_INVOKE(x) ZEN_DETAIL_PP_SEQ_SPLIT_OP x
#define ZEN_DETAIL_PP_SEQ_SPLIT_OP(s, x, pred, data, seq, elem) \
    BOOST_PP_IF(pred(s, data, x), ZEN_DETAIL_PP_SEQ_SPLIT_OP_TRUE, ZEN_DETAIL_PP_SEQ_SPLIT_OP_FALSE)(x, pred, data, seq, elem)
#define ZEN_DETAIL_PP_SEQ_SPLIT_OP_TRUE(x, pred, data, seq, elem) BOOST_PP_IIF(ZEN_PP_IS_PAREN(elem), \
    (pred, data, seq(elem),),\
    (pred, data, seq,))
#define ZEN_DETAIL_PP_SEQ_SPLIT_OP_FALSE(x, pred, data, seq, elem) (pred, data, seq, elem (x))
#define ZEN_DETAIL_PP_SEQ_SPLIT_FOLD_LEFT_M(state) ZEN_DETAIL_PP_SEQ_SPLIT_M state
#define ZEN_DETAIL_PP_SEQ_SPLIT_M(pred, data, seq, elem) seq BOOST_PP_IIF(ZEN_PP_IS_PAREN(elem), (elem),)


//
// ZEN_PP_EQUAL
//
#define ZEN_PP_IS_COMPARABLE(x) BOOST_PP_IIF(ZEN_PP_IS_PAREN(x), ZEN_PP_FALSE, ZEN_PP_PRIMITIVE_IS_COMPARABLE)(x)

#define ZEN_PP_PRIMITIVE_IS_COMPARABLE(x) ZEN_PP_IS_PAREN( ZEN_PP_COMPARE_ ## x (()) )

#define ZEN_PP_PRIMITIVE_COMPARE(x, y) ZEN_PP_IS_PAREN \
( \
ZEN_PP_COMPARE_ ## x ( ZEN_PP_COMPARE_ ## y ZEN_PP_EMPTY()(()) ) \
)

#define ZEN_PP_NOT_EQUAL(x, y) \
BOOST_PP_IIF(BOOST_PP_BITAND( ZEN_PP_IS_COMPARABLE(x), ZEN_PP_IS_COMPARABLE(y) ), \
   ZEN_PP_PRIMITIVE_COMPARE, \
   ZEN_PP_TRUE \
)(x, y)

#define ZEN_PP_EQUAL(x, y) BOOST_PP_COMPL(ZEN_PP_NOT_EQUAL(x, y))


//
// SEQ
//
// ZEN_PP_SEQ_FOR_EACH_PRODUCT for each product with data
#define ZEN_PP_SEQ_FOR_EACH_PRODUCT(macro, data, seqs) \
BOOST_ZEN_PP_SEQ_FOR_EACH_PRODUCT(DETAIL_ZEN_PP_SEQ_FOR_EACH_PRODUCT_EACH, ((macro))((data))seqs)

#define DETAIL_ZEN_PP_SEQ_FOR_EACH_PRODUCT_EACH_I(r, macro, data, product) macro(r, data, product) 
#define DETAIL_ZEN_PP_SEQ_FOR_EACH_PRODUCT_EACH(r, product) \
DETAIL_ZEN_PP_SEQ_FOR_EACH_PRODUCT_EACH_I(r, BOOST_PP_SEQ_ELEM(0, product), BOOST_PP_SEQ_ELEM(1, product), BOOST_PP_SEQ_REST_N(2,product))

//
// ZEN_PP_ARGS_TO_SEQ converts args to a seq
//
#define ZEN_PP_ARGS_TO_SEQ(...) ZEN_PP_DETAIL_ARGS_TO_SEQ(ZEN_PP_NARGS(__VA_ARGS__), (__VA_ARGS__))
#define ZEN_PP_DETAIL_ARGS_TO_SEQ(size, tuple) BOOST_PP_TUPLE_TO_SEQ(size, tuple)



#define ZEN_PP_TYPEOF(x) ZEN_PP_DETAIL_TYPEOF(ZEN_PP_DETAIL_TYPEOF_PROBE x,)
#ifndef _MSC_VER
#define ZEN_PP_DETAIL_TYPEOF(...) ZEN_PP_DETAIL_TYPEOF_HEAD(__VA_ARGS__)
#else
// MSVC Workarounds
#define ZEN_PP_DETAIL_TYPEOF(...) ZEN_PP_MSVC_INVOKE(ZEN_PP_DETAIL_TYPEOF_HEAD, (__VA_ARGS__))
#endif
#define ZEN_PP_DETAIL_TYPEOF_HEAD(x, ...) ZEN_PP_REM x
#define ZEN_PP_DETAIL_TYPEOF_PROBE(...) (__VA_ARGS__),

#define ZEN_PP_STRIP(x) ZEN_PP_EAT x

#define ZEN_PP_PAIR(x) ZEN_PP_REM x

#define ZEN_PP_VARN_CAT(n, tuple) ZEN_DETAIL_PP_VARN_INVOKE((n, ZEN_PP_REM tuple, BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT, BOOST_PP_INTERCEPT))
#ifndef _MSC_VER
#define ZEN_DETAIL_PP_VARN_INVOKE(data)  ZEN_DETAIL_PP_VARN_CAT data
#else
// MSVC Workarounds
#define ZEN_DETAIL_PP_VARN_INVOKE(data) ZEN_PP_MSVC_INVOKE(ZEN_DETAIL_PP_VARN_CAT, data)
#endif
#define ZEN_DETAIL_PP_VARN_CAT(n, a, b, c, d, e, f, g, h, ...) ZEN_DETAIL_PP_VARN_CAT_EACH(a, n) ZEN_DETAIL_PP_VARN_CAT_EACH(b, n) ZEN_DETAIL_PP_VARN_CAT_EACH(c, n) ZEN_DETAIL_PP_VARN_CAT_EACH(d, n) ZEN_DETAIL_PP_VARN_CAT_EACH(e, n) ZEN_DETAIL_PP_VARN_CAT_EACH(f, n) ZEN_DETAIL_PP_VARN_CAT_EACH(g, n) ZEN_DETAIL_PP_VARN_CAT_EACH(h, n)
#define ZEN_DETAIL_PP_VARN_CAT_EACH(a, n) BOOST_PP_IF(ZEN_PP_IS_PAREN(a), ZEN_DETAIL_PP_VARN_CAT_EACH_PAREN, ZEN_DETAIL_PP_VARN_CAT_EACH_TOKEN)(a, n)
#define ZEN_DETAIL_PP_VARN_CAT_EACH_PAREN(a, n) (BOOST_PP_CAT(ZEN_PP_REM a, n))
#define ZEN_DETAIL_PP_VARN_CAT_EACH_TOKEN(a, n)  BOOST_PP_CAT(a, n)

// TODO: Remove when VARN_CAT can handle parenthesis
#define ZEN_PP_CONSTRUCT(n, ...) BOOST_PP_ENUM(n, ZEN_DETAIL_PP_CONSTRUCT_EACH, (__VA_ARGS__)) 
#define ZEN_DETAIL_PP_CONSTRUCT_EACH(z, i, data) ZEN_DETAIL_PP_CONSTRUCT_INVOKE((i, ZEN_PP_REM data))
#define ZEN_DETAIL_PP_CONSTRUCT_INVOKE(data) ZEN_DETAIL_PP_CONSTRUCT_OP data
#define ZEN_DETAIL_PP_CONSTRUCT_OP(n, ...) BOOST_PP_CAT(ZEN_DETAIL_PP_CONSTRUCT_CAT_, ZEN_PP_NARGS(__VA_ARGS__))(n, __VA_ARGS__)
#define ZEN_DETAIL_PP_CONSTRUCT_CAT_1(n, x) x ## n (x ## n)
#define ZEN_DETAIL_PP_CONSTRUCT_CAT_2(n, x, y) x ## n (y ## n)

#define ZEN_PP_FIXED_PARAMS(n, max, var, fixed) \
BOOST_PP_ENUM_PARAMS(n,var)                                 \
BOOST_PP_COMMA_IF(n)                                      \
BOOST_PP_ENUM_PARAMS(BOOST_PP_SUB(max,n), fixed BOOST_PP_INTERCEPT)

// TODO: Allow for a seq to be the first parmeter instead of just a number.
#define ZEN_PP_PARAMS(n, ...) BOOST_PP_ENUM(n, ZEN_DETAIL_PP_PARAMS_EACH, (__VA_ARGS__))
#define ZEN_PP_PARAMS_Z(z, n, ...) BOOST_PP_ENUM_ ## z(n, ZEN_DETAIL_PP_PARAMS_EACH, (__VA_ARGS__)) 
#define ZEN_DETAIL_PP_PARAMS_EACH(z, n, data) ZEN_PP_VARN_CAT(n, data)

#define ZEN_PP_GEN(n, ...) BOOST_PP_REPEAT(n, ZEN_DETAIL_PP_GEN_EACH, (__VA_ARGS__)) 
#define ZEN_PP_GEN_Z(z, n, ...) BOOST_PP_REPEAT_ ## z(n, ZEN_DETAIL_PP_GEN_EACH, (__VA_ARGS__)) 
#define ZEN_DETAIL_PP_GEN_EACH(z, n, data) ZEN_PP_VARN_CAT(n, data)

#define ZEN_PP_SEQ_GEN(z, n, ...) BOOST_PP_REPEAT_ ## z(n, ZEN_DETAIL_PP_GEN_SEQ_EACH, (__VA_ARGS__)) 
#define ZEN_DETAIL_PP_GEN_SEQ_EACH(z, n, data) (ZEN_PP_VARN_CAT(n, data))


// TODO: De we really need these?
#define ZEN_PP_SEQ_PREFIX(prefix, seq) BOOST_PP_SEQ_TRANSFORM(ZEN_DETAIL_PP_SEQ_PREFIX_OP, prefix, seq)  
#define ZEN_DETAIL_PP_SEQ_PREFIX_OP(d, prefix, x) prefix x

#define ZEN_PP_SEQ_POSTFIX(postfix, seq) BOOST_PP_SEQ_TRANSFORM(ZEN_DETAIL_PP_SEQ_POSTFIX_OP, postfix, seq)  
#define ZEN_DETAIL_PP_SEQ_POSTFIX_OP(d, postfix, x) postfix x

#define ZEN_PP_SEQ_POST_ENUM(seq, ...) BOOST_PP_SEQ_FOR_EACH_I(ZEN_DETAIL_PP_SEQ_POST_ENUM_EACH, (__VA_ARGS__), seq) 
#define ZEN_DETAIL_PP_SEQ_POST_ENUM_EACH(r, data, i, elem) (ZEN_PP_VARN_CAT(i, data) elem)

#define ZEN_PP_SEQ_MERGE(seq1, seq2) BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq1), ZEN_DETAIL_PP_SEQ_MERGE_EACH, (seq1, seq2))
#define ZEN_DETAIL_PP_SEQ_MERGE_EACH(z, n, data) ZEN_DETAIL_PP_SEQ_MERGE_INVOKE((n, ZEN_PP_REM data))
#define ZEN_DETAIL_PP_SEQ_MERGE_INVOKE(data) ZEN_DETAIL_PP_SEQ_MERGE_OP data
#define ZEN_DETAIL_PP_SEQ_MERGE_OP(n, seq1, seq2) BOOST_PP_SEQ_ELEM(n, seq1) BOOST_PP_SEQ_ELEM(n, seq2)

#define ZEN_PP_SEQ_MERGE_CAT(seq1, seq2) BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq1), ZEN_DETAIL_PP_SEQ_MERGE_CAT_EACH, (seq1, seq2))
#define ZEN_DETAIL_PP_SEQ_MERGE_CAT_EACH(z, n, data) ZEN_DETAIL_PP_SEQ_MERGE_CAT_INVOKE((n, ZEN_PP_REM data))
#define ZEN_DETAIL_PP_SEQ_MERGE_CAT_INVOKE(data) ZEN_DETAIL_PP_SEQ_MERGE_CAT_OP data
#define ZEN_DETAIL_PP_SEQ_MERGE_CAT_OP(n, seq1, seq2) BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(n, seq1), BOOST_PP_SEQ_ELEM(n, seq2))



#define ZEN_PP_SEQ_HEAD(seq) ZEN_DETAIL_PP_SEQ_HEAD(ZEN_PP_REM ZEN_PP_HEAD(head))
#define ZEN_DETAIL_PP_SEQ_HEAD(...) __VA_ARGS__

#define ZEN_PP_SEQ_TAIL(seq) ZEN_PP_EAT seq

//
// ZEN_PP_SEQ_TRANSFORM_I
//
#define ZEN_PP_SEQ_TRANSFORM_I(op, data, seq) \
ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_M(BOOST_PP_WHILE(ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_P, ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_OP, (op, data, 0, , seq)))

#define ZEN_PP_SEQ_TRANSFORM_I_D(d, op, data, seq) \
ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_M(BOOST_PP_WHILE_ ## d(ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_P, ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_OP, (op, data, 0, , seq)))

#define ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_OP(d, state) ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_INVOKE(ZEN_DETAIL_PP_SEQ_TRANSFORM_I_OP, (d, ZEN_PP_REM state))
#define ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_P(d, state) ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_INVOKE(ZEN_DETAIL_PP_SEQ_TRANSFORM_I_P, (d, ZEN_PP_REM state))
#define ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_M(state) ZEN_DETAIL_PP_SEQ_TRANSFORM_I_M state
#define ZEN_DETAIL_PP_SEQ_TRANSFORM_I_WHILE_INVOKE(macro, args) macro args

#define ZEN_DETAIL_PP_SEQ_TRANSFORM_I_OP(d, op, data, i, result, seq) (op, data, BOOST_PP_INC(i), result(op(d, data, i, BOOST_PP_SEQ_HEAD(seq))), BOOST_PP_SEQ_TAIL(seq))
#define ZEN_DETAIL_PP_SEQ_TRANSFORM_I_P(d, op, data, i, result, seq) ZEN_PP_IS_PAREN(seq)
#define ZEN_DETAIL_PP_SEQ_TRANSFORM_I_M(op, data, i, result, seq) result

#define ZEN_PP_INTERCEPT_COMMA ZEN_PP_INTERCEPT_COMMA_

#define ZEN_PP_INTERCEPT_COMMA_0 ,
#define ZEN_PP_INTERCEPT_COMMA_1 ,
#define ZEN_PP_INTERCEPT_COMMA_2 ,
#define ZEN_PP_INTERCEPT_COMMA_3 ,
#define ZEN_PP_INTERCEPT_COMMA_4 ,
#define ZEN_PP_INTERCEPT_COMMA_5 ,
#define ZEN_PP_INTERCEPT_COMMA_6 ,
#define ZEN_PP_INTERCEPT_COMMA_7 ,
#define ZEN_PP_INTERCEPT_COMMA_8 ,
#define ZEN_PP_INTERCEPT_COMMA_9 ,
#define ZEN_PP_INTERCEPT_COMMA_10 ,
#define ZEN_PP_INTERCEPT_COMMA_11 ,
#define ZEN_PP_INTERCEPT_COMMA_12 ,
#define ZEN_PP_INTERCEPT_COMMA_13 ,
#define ZEN_PP_INTERCEPT_COMMA_14 ,
#define ZEN_PP_INTERCEPT_COMMA_15 ,
#define ZEN_PP_INTERCEPT_COMMA_16 ,
#define ZEN_PP_INTERCEPT_COMMA_17 ,
#define ZEN_PP_INTERCEPT_COMMA_18 ,
#define ZEN_PP_INTERCEPT_COMMA_19 ,
#define ZEN_PP_INTERCEPT_COMMA_20 ,
#define ZEN_PP_INTERCEPT_COMMA_21 ,
#define ZEN_PP_INTERCEPT_COMMA_22 ,
#define ZEN_PP_INTERCEPT_COMMA_23 ,
#define ZEN_PP_INTERCEPT_COMMA_24 ,
#define ZEN_PP_INTERCEPT_COMMA_25 ,
#define ZEN_PP_INTERCEPT_COMMA_26 ,
#define ZEN_PP_INTERCEPT_COMMA_27 ,
#define ZEN_PP_INTERCEPT_COMMA_28 ,
#define ZEN_PP_INTERCEPT_COMMA_29 ,
#define ZEN_PP_INTERCEPT_COMMA_30 ,
#define ZEN_PP_INTERCEPT_COMMA_31 ,
#define ZEN_PP_INTERCEPT_COMMA_32 ,
#define ZEN_PP_INTERCEPT_COMMA_33 ,
#define ZEN_PP_INTERCEPT_COMMA_34 ,
#define ZEN_PP_INTERCEPT_COMMA_35 ,
#define ZEN_PP_INTERCEPT_COMMA_36 ,
#define ZEN_PP_INTERCEPT_COMMA_37 ,
#define ZEN_PP_INTERCEPT_COMMA_38 ,
#define ZEN_PP_INTERCEPT_COMMA_39 ,
#define ZEN_PP_INTERCEPT_COMMA_40 ,
#define ZEN_PP_INTERCEPT_COMMA_41 ,
#define ZEN_PP_INTERCEPT_COMMA_42 ,
#define ZEN_PP_INTERCEPT_COMMA_43 ,
#define ZEN_PP_INTERCEPT_COMMA_44 ,
#define ZEN_PP_INTERCEPT_COMMA_45 ,
#define ZEN_PP_INTERCEPT_COMMA_46 ,
#define ZEN_PP_INTERCEPT_COMMA_47 ,
#define ZEN_PP_INTERCEPT_COMMA_48 ,
#define ZEN_PP_INTERCEPT_COMMA_49 ,
#define ZEN_PP_INTERCEPT_COMMA_50 ,
#define ZEN_PP_INTERCEPT_COMMA_51 ,
#define ZEN_PP_INTERCEPT_COMMA_52 ,
#define ZEN_PP_INTERCEPT_COMMA_53 ,
#define ZEN_PP_INTERCEPT_COMMA_54 ,
#define ZEN_PP_INTERCEPT_COMMA_55 ,
#define ZEN_PP_INTERCEPT_COMMA_56 ,
#define ZEN_PP_INTERCEPT_COMMA_57 ,
#define ZEN_PP_INTERCEPT_COMMA_58 ,
#define ZEN_PP_INTERCEPT_COMMA_59 ,
#define ZEN_PP_INTERCEPT_COMMA_60 ,
#define ZEN_PP_INTERCEPT_COMMA_61 ,
#define ZEN_PP_INTERCEPT_COMMA_62 ,
#define ZEN_PP_INTERCEPT_COMMA_63 ,
#define ZEN_PP_INTERCEPT_COMMA_64 ,
#define ZEN_PP_INTERCEPT_COMMA_65 ,
#define ZEN_PP_INTERCEPT_COMMA_66 ,
#define ZEN_PP_INTERCEPT_COMMA_67 ,
#define ZEN_PP_INTERCEPT_COMMA_68 ,
#define ZEN_PP_INTERCEPT_COMMA_69 ,
#define ZEN_PP_INTERCEPT_COMMA_70 ,
#define ZEN_PP_INTERCEPT_COMMA_71 ,
#define ZEN_PP_INTERCEPT_COMMA_72 ,
#define ZEN_PP_INTERCEPT_COMMA_73 ,
#define ZEN_PP_INTERCEPT_COMMA_74 ,
#define ZEN_PP_INTERCEPT_COMMA_75 ,
#define ZEN_PP_INTERCEPT_COMMA_76 ,
#define ZEN_PP_INTERCEPT_COMMA_77 ,
#define ZEN_PP_INTERCEPT_COMMA_78 ,
#define ZEN_PP_INTERCEPT_COMMA_79 ,
#define ZEN_PP_INTERCEPT_COMMA_80 ,
#define ZEN_PP_INTERCEPT_COMMA_81 ,
#define ZEN_PP_INTERCEPT_COMMA_82 ,
#define ZEN_PP_INTERCEPT_COMMA_83 ,
#define ZEN_PP_INTERCEPT_COMMA_84 ,
#define ZEN_PP_INTERCEPT_COMMA_85 ,
#define ZEN_PP_INTERCEPT_COMMA_86 ,
#define ZEN_PP_INTERCEPT_COMMA_87 ,
#define ZEN_PP_INTERCEPT_COMMA_88 ,
#define ZEN_PP_INTERCEPT_COMMA_89 ,
#define ZEN_PP_INTERCEPT_COMMA_90 ,
#define ZEN_PP_INTERCEPT_COMMA_91 ,
#define ZEN_PP_INTERCEPT_COMMA_92 ,
#define ZEN_PP_INTERCEPT_COMMA_93 ,
#define ZEN_PP_INTERCEPT_COMMA_94 ,
#define ZEN_PP_INTERCEPT_COMMA_95 ,
#define ZEN_PP_INTERCEPT_COMMA_96 ,
#define ZEN_PP_INTERCEPT_COMMA_97 ,
#define ZEN_PP_INTERCEPT_COMMA_98 ,
#define ZEN_PP_INTERCEPT_COMMA_99 ,
#define ZEN_PP_INTERCEPT_COMMA_100 ,
#define ZEN_PP_INTERCEPT_COMMA_101 ,
#define ZEN_PP_INTERCEPT_COMMA_102 ,
#define ZEN_PP_INTERCEPT_COMMA_103 ,
#define ZEN_PP_INTERCEPT_COMMA_104 ,
#define ZEN_PP_INTERCEPT_COMMA_105 ,
#define ZEN_PP_INTERCEPT_COMMA_106 ,
#define ZEN_PP_INTERCEPT_COMMA_107 ,
#define ZEN_PP_INTERCEPT_COMMA_108 ,
#define ZEN_PP_INTERCEPT_COMMA_109 ,
#define ZEN_PP_INTERCEPT_COMMA_110 ,
#define ZEN_PP_INTERCEPT_COMMA_111 ,
#define ZEN_PP_INTERCEPT_COMMA_112 ,
#define ZEN_PP_INTERCEPT_COMMA_113 ,
#define ZEN_PP_INTERCEPT_COMMA_114 ,
#define ZEN_PP_INTERCEPT_COMMA_115 ,
#define ZEN_PP_INTERCEPT_COMMA_116 ,
#define ZEN_PP_INTERCEPT_COMMA_117 ,
#define ZEN_PP_INTERCEPT_COMMA_118 ,
#define ZEN_PP_INTERCEPT_COMMA_119 ,
#define ZEN_PP_INTERCEPT_COMMA_120 ,
#define ZEN_PP_INTERCEPT_COMMA_121 ,
#define ZEN_PP_INTERCEPT_COMMA_122 ,
#define ZEN_PP_INTERCEPT_COMMA_123 ,
#define ZEN_PP_INTERCEPT_COMMA_124 ,
#define ZEN_PP_INTERCEPT_COMMA_125 ,
#define ZEN_PP_INTERCEPT_COMMA_126 ,
#define ZEN_PP_INTERCEPT_COMMA_127 ,
#define ZEN_PP_INTERCEPT_COMMA_128 ,
#define ZEN_PP_INTERCEPT_COMMA_129 ,
#define ZEN_PP_INTERCEPT_COMMA_130 ,
#define ZEN_PP_INTERCEPT_COMMA_131 ,
#define ZEN_PP_INTERCEPT_COMMA_132 ,
#define ZEN_PP_INTERCEPT_COMMA_133 ,
#define ZEN_PP_INTERCEPT_COMMA_134 ,
#define ZEN_PP_INTERCEPT_COMMA_135 ,
#define ZEN_PP_INTERCEPT_COMMA_136 ,
#define ZEN_PP_INTERCEPT_COMMA_137 ,
#define ZEN_PP_INTERCEPT_COMMA_138 ,
#define ZEN_PP_INTERCEPT_COMMA_139 ,
#define ZEN_PP_INTERCEPT_COMMA_140 ,
#define ZEN_PP_INTERCEPT_COMMA_141 ,
#define ZEN_PP_INTERCEPT_COMMA_142 ,
#define ZEN_PP_INTERCEPT_COMMA_143 ,
#define ZEN_PP_INTERCEPT_COMMA_144 ,
#define ZEN_PP_INTERCEPT_COMMA_145 ,
#define ZEN_PP_INTERCEPT_COMMA_146 ,
#define ZEN_PP_INTERCEPT_COMMA_147 ,
#define ZEN_PP_INTERCEPT_COMMA_148 ,
#define ZEN_PP_INTERCEPT_COMMA_149 ,
#define ZEN_PP_INTERCEPT_COMMA_150 ,
#define ZEN_PP_INTERCEPT_COMMA_151 ,
#define ZEN_PP_INTERCEPT_COMMA_152 ,
#define ZEN_PP_INTERCEPT_COMMA_153 ,
#define ZEN_PP_INTERCEPT_COMMA_154 ,
#define ZEN_PP_INTERCEPT_COMMA_155 ,
#define ZEN_PP_INTERCEPT_COMMA_156 ,
#define ZEN_PP_INTERCEPT_COMMA_157 ,
#define ZEN_PP_INTERCEPT_COMMA_158 ,
#define ZEN_PP_INTERCEPT_COMMA_159 ,
#define ZEN_PP_INTERCEPT_COMMA_160 ,
#define ZEN_PP_INTERCEPT_COMMA_161 ,
#define ZEN_PP_INTERCEPT_COMMA_162 ,
#define ZEN_PP_INTERCEPT_COMMA_163 ,
#define ZEN_PP_INTERCEPT_COMMA_164 ,
#define ZEN_PP_INTERCEPT_COMMA_165 ,
#define ZEN_PP_INTERCEPT_COMMA_166 ,
#define ZEN_PP_INTERCEPT_COMMA_167 ,
#define ZEN_PP_INTERCEPT_COMMA_168 ,
#define ZEN_PP_INTERCEPT_COMMA_169 ,
#define ZEN_PP_INTERCEPT_COMMA_170 ,
#define ZEN_PP_INTERCEPT_COMMA_171 ,
#define ZEN_PP_INTERCEPT_COMMA_172 ,
#define ZEN_PP_INTERCEPT_COMMA_173 ,
#define ZEN_PP_INTERCEPT_COMMA_174 ,
#define ZEN_PP_INTERCEPT_COMMA_175 ,
#define ZEN_PP_INTERCEPT_COMMA_176 ,
#define ZEN_PP_INTERCEPT_COMMA_177 ,
#define ZEN_PP_INTERCEPT_COMMA_178 ,
#define ZEN_PP_INTERCEPT_COMMA_179 ,
#define ZEN_PP_INTERCEPT_COMMA_180 ,
#define ZEN_PP_INTERCEPT_COMMA_181 ,
#define ZEN_PP_INTERCEPT_COMMA_182 ,
#define ZEN_PP_INTERCEPT_COMMA_183 ,
#define ZEN_PP_INTERCEPT_COMMA_184 ,
#define ZEN_PP_INTERCEPT_COMMA_185 ,
#define ZEN_PP_INTERCEPT_COMMA_186 ,
#define ZEN_PP_INTERCEPT_COMMA_187 ,
#define ZEN_PP_INTERCEPT_COMMA_188 ,
#define ZEN_PP_INTERCEPT_COMMA_189 ,
#define ZEN_PP_INTERCEPT_COMMA_190 ,
#define ZEN_PP_INTERCEPT_COMMA_191 ,
#define ZEN_PP_INTERCEPT_COMMA_192 ,
#define ZEN_PP_INTERCEPT_COMMA_193 ,
#define ZEN_PP_INTERCEPT_COMMA_194 ,
#define ZEN_PP_INTERCEPT_COMMA_195 ,
#define ZEN_PP_INTERCEPT_COMMA_196 ,
#define ZEN_PP_INTERCEPT_COMMA_197 ,
#define ZEN_PP_INTERCEPT_COMMA_198 ,
#define ZEN_PP_INTERCEPT_COMMA_199 ,
#define ZEN_PP_INTERCEPT_COMMA_200 ,
#define ZEN_PP_INTERCEPT_COMMA_201 ,
#define ZEN_PP_INTERCEPT_COMMA_202 ,
#define ZEN_PP_INTERCEPT_COMMA_203 ,
#define ZEN_PP_INTERCEPT_COMMA_204 ,
#define ZEN_PP_INTERCEPT_COMMA_205 ,
#define ZEN_PP_INTERCEPT_COMMA_206 ,
#define ZEN_PP_INTERCEPT_COMMA_207 ,
#define ZEN_PP_INTERCEPT_COMMA_208 ,
#define ZEN_PP_INTERCEPT_COMMA_209 ,
#define ZEN_PP_INTERCEPT_COMMA_210 ,
#define ZEN_PP_INTERCEPT_COMMA_211 ,
#define ZEN_PP_INTERCEPT_COMMA_212 ,
#define ZEN_PP_INTERCEPT_COMMA_213 ,
#define ZEN_PP_INTERCEPT_COMMA_214 ,
#define ZEN_PP_INTERCEPT_COMMA_215 ,
#define ZEN_PP_INTERCEPT_COMMA_216 ,
#define ZEN_PP_INTERCEPT_COMMA_217 ,
#define ZEN_PP_INTERCEPT_COMMA_218 ,
#define ZEN_PP_INTERCEPT_COMMA_219 ,
#define ZEN_PP_INTERCEPT_COMMA_220 ,
#define ZEN_PP_INTERCEPT_COMMA_221 ,
#define ZEN_PP_INTERCEPT_COMMA_222 ,
#define ZEN_PP_INTERCEPT_COMMA_223 ,
#define ZEN_PP_INTERCEPT_COMMA_224 ,
#define ZEN_PP_INTERCEPT_COMMA_225 ,
#define ZEN_PP_INTERCEPT_COMMA_226 ,
#define ZEN_PP_INTERCEPT_COMMA_227 ,
#define ZEN_PP_INTERCEPT_COMMA_228 ,
#define ZEN_PP_INTERCEPT_COMMA_229 ,
#define ZEN_PP_INTERCEPT_COMMA_230 ,
#define ZEN_PP_INTERCEPT_COMMA_231 ,
#define ZEN_PP_INTERCEPT_COMMA_232 ,
#define ZEN_PP_INTERCEPT_COMMA_233 ,
#define ZEN_PP_INTERCEPT_COMMA_234 ,
#define ZEN_PP_INTERCEPT_COMMA_235 ,
#define ZEN_PP_INTERCEPT_COMMA_236 ,
#define ZEN_PP_INTERCEPT_COMMA_237 ,
#define ZEN_PP_INTERCEPT_COMMA_238 ,
#define ZEN_PP_INTERCEPT_COMMA_239 ,
#define ZEN_PP_INTERCEPT_COMMA_240 ,
#define ZEN_PP_INTERCEPT_COMMA_241 ,
#define ZEN_PP_INTERCEPT_COMMA_242 ,
#define ZEN_PP_INTERCEPT_COMMA_243 ,
#define ZEN_PP_INTERCEPT_COMMA_244 ,
#define ZEN_PP_INTERCEPT_COMMA_245 ,
#define ZEN_PP_INTERCEPT_COMMA_246 ,
#define ZEN_PP_INTERCEPT_COMMA_247 ,
#define ZEN_PP_INTERCEPT_COMMA_248 ,
#define ZEN_PP_INTERCEPT_COMMA_249 ,
#define ZEN_PP_INTERCEPT_COMMA_250 ,
#define ZEN_PP_INTERCEPT_COMMA_251 ,
#define ZEN_PP_INTERCEPT_COMMA_252 ,
#define ZEN_PP_INTERCEPT_COMMA_253 ,
#define ZEN_PP_INTERCEPT_COMMA_254 ,
#define ZEN_PP_INTERCEPT_COMMA_255 ,
#define ZEN_PP_INTERCEPT_COMMA_256 ,



#endif	/* ZEN_GUARD_PP_H */

