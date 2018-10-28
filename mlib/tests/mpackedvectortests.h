#pragma once

#include <check.h>
#include "mlib/mlib.h"
#include "mlib/mpackedvector.h"

// type for all the test cases
#define TEST_TYPE mint

// creating the vector of our test type
MPACKED_VECTOR_DECLARE(TEST_TYPE)

// convienence fuctions for assertions
#define ASSERT_CAPACITY(vecptr, desiredVal)                                      \
	{                                                                        \
		msize tmp = VECTOR_CAPACITY(TEST_TYPE)(vecptr);                  \
		ck_assert_msg(tmp == desiredVal,                               \
			      "VECTOR_CAPACITY check FAILED at LINE: " GET_LINE_NUM()  \
			      ". in FILE: " GET_FILE_NAME()                            \
			      ".CAPACITY IS: %zu\n CAPACITY SHOULD BE: %zu",     \
			      tmp, desiredVal); \
	}
#define ASSERT_SIZE(vecptr, desiredVal)                                          \
	{                                                                        \
		msize tmp = VECTOR_SIZE(TEST_TYPE)(vecptr);                      \
		ck_assert_msg(tmp == desiredVal,                               \
			      "VECTOR_SIZE check FAILED at LINE: " GET_LINE_NUM()  \
			      ". in FILE: " GET_FILE_NAME()                            \
			      ".SIZE IS: %zu\n SIZE SHOULD BE: %zu",     \
			      tmp, desiredVal); \
	}
#define ASSERT_GET_AT(vecptr, index, desiredVal)                                 \
	{                                                                        \
		TEST_TYPE tmp = VECTOR_GET_AT(TEST_TYPE)(vecptr, index);         \
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
	/* tcase_add_test(tc_core, push_back_test); */

	suite_add_tcase(s, tc_core);

	return s;
}

#undef TEST_TYPE
#undef ASSERT_CAPACITY
#undef ASSERT_SIZE
#undef ASSERT_GET_AT
