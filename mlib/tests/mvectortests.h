#pragma once

#include <check.h>
#include "mlib/mlib.h"
#include "mlib/mvector.h"

// type for all the test cases
#define TEST_TYPE mint

// creating the vector of our test type
MVECTOR_DECLARE(TEST_TYPE)

// convienence fuctions for assertions
#define ASSERT_CAPACITY(vecptr, desiredVal)                                      \
	{                                                                        \
		msize tmp = MVECTOR_CAPACITY(TEST_TYPE)(vecptr);                 \
		ck_assert_msg(tmp == desiredVal,                               \
			      "VECTOR_CAPACITY check FAILED at LINE: " GET_LINE_NUM()  \
			      ". in FILE: " GET_FILE_NAME()                            \
			      ".CAPACITY IS: %zu\n CAPACITY SHOULD BE: %zu",     \
			      tmp, desiredVal); \
	}
#define ASSERT_SIZE(vecptr, desiredVal)                                          \
	{                                                                        \
		msize tmp = MVECTOR_SIZE(TEST_TYPE)(vecptr);                     \
		ck_assert_msg(tmp == desiredVal,                               \
			      "VECTOR_SIZE check FAILED at LINE: " GET_LINE_NUM()  \
			      ". in FILE: " GET_FILE_NAME()                            \
			      ".SIZE IS: %zu\n SIZE SHOULD BE: %zu",     \
			      tmp, desiredVal); \
	}
#define ASSERT_GET_AT(vecptr, index, desiredVal)                                 \
	{                                                                        \
		TEST_TYPE tmp = MVECTOR_GET_AT(TEST_TYPE)(vecptr, index);        \
		ck_assert_msg(tmp == desiredVal,                               \
			      "VECTOR_GET_AT check FAILED at LINE: " GET_LINE_NUM()  \
			      ". in FILE: " GET_FILE_NAME()                            \
			      ".VAL IS: %zu\n VAL SHOULD BE: %zu",     \
			      tmp, desiredVal); \
	}
// -----------------------------------------
//    Unit tests:
// -----------------------------------------

// push_back_unit test
START_TEST(push_back_test)
{
	/* Initialization the vector */
	struct MVector_mint_t testvec;
	MVECTOR_INIT(mint)(&testvec, 5);

	// testing the intilization
	ASSERT_SIZE(&testvec, 0);
	ASSERT_CAPACITY(&testvec, 5);

	/* Pushing back 12 */
	MVECTOR_PUSH_BACK(mint)(&testvec, 12);

	// testing the vector vals
	ASSERT_GET_AT(&testvec, 0, 12);
	ASSERT_SIZE(&testvec, 1);
	ASSERT_CAPACITY(&testvec, 5);

	/* Pushing back 12 four more times, so we should have five 12s */
	MVECTOR_PUSH_BACK(mint)(&testvec, 12);
	MVECTOR_PUSH_BACK(mint)(&testvec, 12);
	MVECTOR_PUSH_BACK(mint)(&testvec, 12);
	MVECTOR_PUSH_BACK(mint)(&testvec, 12);

	// assertions
	ASSERT_SIZE(&testvec, 5);
	ASSERT_CAPACITY(&testvec, 5);

	/*pushing the vector back again should resize it*/
	MVECTOR_PUSH_BACK(mint)(&testvec, 13);

	// assertions
	ASSERT_SIZE(&testvec, 6);
	ASSERT_CAPACITY(&testvec, 10);
	for (msize i = 0; i < 4; ++i)
		ASSERT_GET_AT(&testvec, i, 12);
	ASSERT_GET_AT(&testvec, 5, 13);

	MVECTOR_FREE(mint)(&testvec);
}
END_TEST

// push_back_unit test
START_TEST(pop_back_test)
{
	/* Initialization the vector */
	struct MVector_mint_t testvec;
	MVECTOR_INIT(mint)(&testvec, 5);

	// testing the intilization
	ASSERT_SIZE(&testvec, 0);
	ASSERT_CAPACITY(&testvec, 5);

	/* Pushing back 0,1,2,3,4 */
	for (mint i = 0; i < 5; ++i)
		MVECTOR_PUSH_BACK(mint)(&testvec, i);

	// testing the vector vals
	ASSERT_SIZE(&testvec, 5);
	ASSERT_CAPACITY(&testvec, 5);
	for (mint i = 0; i < 5; ++i)
		ASSERT_GET_AT(&testvec, i, i);

	/* Popping back so we should have 0,1,2,3 */
	ck_assert_msg(MVECTOR_POP_BACK(mint)(&testvec) == 4,
		      "POP BACK ERROR AT LINE " GET_LINE_NUM());

	// assertions
	ASSERT_SIZE(&testvec, 4);
	ASSERT_CAPACITY(&testvec, 5);
	for (mint i = 0; i < 4; ++i)
		ASSERT_GET_AT(&testvec, i, i);


	/*Popping the entire vector away*/
	ck_assert_msg(MVECTOR_POP_BACK(mint)(&testvec) == 3,
		      "POP BACK ERROR AT LINE " GET_LINE_NUM());
	ASSERT_SIZE(&testvec, 3);
	ASSERT_CAPACITY(&testvec, 5);

	ck_assert_msg(MVECTOR_POP_BACK(mint)(&testvec) == 2,
		      "POP BACK ERROR AT LINE " GET_LINE_NUM());
	ASSERT_SIZE(&testvec, 2);
	ASSERT_CAPACITY(&testvec, 5);

	ck_assert_msg(MVECTOR_POP_BACK(mint)(&testvec) == 1,
		      "POP BACK ERROR AT LINE " GET_LINE_NUM());
	ASSERT_SIZE(&testvec, 1);
	ASSERT_CAPACITY(&testvec, 5);

	ck_assert_msg(MVECTOR_POP_BACK(mint)(&testvec) == 0,
		      "POP BACK ERROR AT LINE " GET_LINE_NUM());
	ASSERT_SIZE(&testvec, 0);
	ASSERT_CAPACITY(&testvec, 5);

	MVECTOR_FREE(mint)(&testvec);
}
END_TEST

// push_back_unit test
START_TEST(swap_test)
{
	/* Initialization the vector */
	struct MVector_mint_t testvec;
	MVECTOR_INIT(mint)(&testvec, 5);

	// testing the intilization
	ASSERT_SIZE(&testvec, 0);
	ASSERT_CAPACITY(&testvec, 5);

	/* Pushing back 0,1,2,3,4 */
	for (mint i = 0; i < 5; ++i)
		MVECTOR_PUSH_BACK(mint)(&testvec, i);

	/* swapping */
	MVECTOR_SWAP(mint)(&testvec, 0, 2);

	// assetions
	ASSERT_GET_AT(&testvec, 0, 2);
	ASSERT_GET_AT(&testvec, 2, 0);


	MVECTOR_FREE(mint)(&testvec);
}
END_TEST

// push_back_unit test
START_TEST(swap_back_test)
{
	/* Initialization the vector */
	struct MVector_mint_t testvec;
	MVECTOR_INIT(mint)(&testvec, 5);

	// testing the intilization
	ASSERT_SIZE(&testvec, 0);
	ASSERT_CAPACITY(&testvec, 5);

	/* Pushing back 0,1,2,3,4 */
	for (mint i = 0; i < 5; ++i)
		MVECTOR_PUSH_BACK(mint)(&testvec, i);

	/* swapping */
	MVECTOR_SWAP_BACK(mint)(&testvec, 0);

	// assetions
	ASSERT_GET_AT(&testvec, 0, 4);
	ASSERT_GET_AT(&testvec, 4, 0);


	MVECTOR_FREE(mint)(&testvec);
}
END_TEST

static Suite *vector_test_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("mvector");

	// core test case
	tc_core = tcase_create("Core");

	// ADD MORE CASES TO TC_CORE HERE
	tcase_add_test(tc_core, push_back_test);
	tcase_add_test(tc_core, pop_back_test);
	tcase_add_test(tc_core, swap_test);
	tcase_add_test(tc_core, swap_back_test);

	suite_add_tcase(s, tc_core);

	return s;
}

#undef TEST_TYPE
#undef ASSERT_CAPACITY
#undef ASSERT_SIZE
#undef ASSERT_GET_AT
