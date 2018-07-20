#pragma once
// clang-format off
// -----------------------------------------
//    Creating generic functions for the movement 
// -----------------------------------------

#define X_MVT(val) val,

// creating generic MVT_add (V2_add) function
#define F_MVT_add(type)const type* : type##_add,
#define MVT_add(a, b) _Generic((a),REMOVE_EXTRA_COMMA(DEFER1(MAP)(F_MVT_add, LIST_OF_MOVEMENTS))) (a,b)

// creating generic MVT_sub (V2_sub) function
#define F_MVT_sub(type)const type* : type##_sub,
#define MVT_sub(a, b) _Generic((a),REMOVE_EXTRA_COMMA(DEFER1(MAP)(F_MVT_sub, LIST_OF_MOVEMENTS))) (a,b)

// creating generic MVT_mul (V2_mul) function
#define F_MVT_mul(type)const type* : type##_mul,
#define MVT_mul(a, b) _Generic((a),REMOVE_EXTRA_COMMA(DEFER1(MAP)(F_MVT_mul, LIST_OF_MOVEMENTS))) (a,b)

// creating generic MVT_smul (V2_smul) function
#define F_MVT_smul(type)const type* : type##_smul,
#define MVT_smul(a, b) _Generic((a),REMOVE_EXTRA_COMMA(DEFER1(MAP)(F_MVT_smul, LIST_OF_MOVEMENTS))) (a,b)

// creating generic MVT_print (V2_print) function
#define F_MVT_print(type)const type* : type##_print,
#define MVT_print(a, b) _Generic((a),REMOVE_EXTRA_COMMA(DEFER1(MAP)(F_MVT_print, LIST_OF_MOVEMENTS))) (a,b)
