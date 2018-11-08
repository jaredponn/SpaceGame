#pragma once

#include <check.h>
#include "mlib/mlib.h"
#include "mlib/mvector.h"
#include "mlib/mpackedvector.h"

// type for all the test cases
#define TEST_TYPE mint

// creating the vector of our test type
MPACKED_VECTOR_DECLARE(TEST_TYPE)

#define ASSERT_SPARSE_VECTOR_VAL(pkdvecptr, index, desiredVal)                   \
	{                                                                        \
		msize tmp = MVECTOR_GET_AT(msize)(&pkdvecptr->sparse_vector,     \
						  index);                        \
		ck_assert_msg(tmp == desiredVal,                               \
			      "sparse_vector has an incorrect value. See test at LINE: " GET_LINE_NUM()  \
			      ". in FILE: " GET_FILE_NAME()                            \
			      ".VAL at %i IS %i.\n VAL at %i should be %i\n",     \
			      index,tmp,index, desiredVal); \
	}

#define ASSERT_PACKED_INDICIES_VAL(pkdvecptr, index, desiredVal)                 \
	{                                                                        \
		msize tmp = MVECTOR_GET_AT(msize)(&pkdvecptr->packed_indices,    \
						  index);                        \
		ck_assert_msg(tmp == desiredVal,                               \
			      "packed_indicies has an incorrect value. See test at LINE: " GET_LINE_NUM()  \
			      ". in FILE: " GET_FILE_NAME()                            \
			      ".VAL at %i IS %i.\n VAL at %i should be %i\n",     \
			      index,tmp,index, desiredVal); \
	}

#define ASSERT_PACKED_DATA_VAL(pkdvecptr, index, desiredVal)                     \
	{                                                                        \
		const EVAL(DEFER1(MK_VEC)(TEST_TYPE)) *pkddatavec =              \
			&pkdvecptr->packed_data;                                 \
		TEST_TYPE tmp = MVECTOR_GET_AT(TEST_TYPE)(pkddatavec, index);    \
		ck_assert_msg(tmp == desiredVal,                               \
			      "packed_data has an incorrect value. See test at LINE: " GET_LINE_NUM()  \
			      ". in FILE: " GET_FILE_NAME()                            \
			      ".VAL at %i IS %i.\n VAL at %i should be %i\n",     \
			      index,tmp,index, desiredVal); \
	}

#define ASSERT_NEXT_PACKED_INDEX_VAL(pkdvecptr, desiredVal)                      \
	{                                                                        \
		msize tmp = pkdvecptr->next_packed_index;                        \
		ck_assert_msg(tmp == desiredVal,                               \
			      "next_packed_index has an incorrect value. See test at LINE: " GET_LINE_NUM()  \
			      ". in FILE: " GET_FILE_NAME()                            \
			      ".next_packed_index is %i but should be %i.\n",     \
			      tmp, desiredVal); \
	}


// -----------------------------------------
//    Unit tests:
// -----------------------------------------

START_TEST(init_test)
{
	MPackedVector_mint_t *pkdvec = malloc(sizeof(MPackedVector_mint_t));
	MPACKED_VECTOR_INIT(TEST_TYPE)(pkdvec, 10);

	for (msize i = 0; i < 10; ++i) {
		ASSERT_SPARSE_VECTOR_VAL(pkdvec, i, SIZE_MAX);
	}
	ASSERT_NEXT_PACKED_INDEX_VAL(pkdvec, 0);
}
END_TEST

// add_at test
START_TEST(add_at_test)
{
	MPackedVector_mint_t *pkdvec = malloc(sizeof(MPackedVector_mint_t));
	MPACKED_VECTOR_INIT(TEST_TYPE)(pkdvec, 10);

	// adding 69 to index 0
	MPACKED_VECTOR_ADD_AT_SPARSE_VECTOR(TEST_TYPE)(pkdvec, 0, 69);
	// assertions
	ASSERT_PACKED_DATA_VAL(pkdvec, 0, 69);
	ASSERT_PACKED_INDICIES_VAL(pkdvec, 0, 0);
	ASSERT_NEXT_PACKED_INDEX_VAL(pkdvec, 1);

	// adding 99 to index 3
	MPACKED_VECTOR_ADD_AT_SPARSE_VECTOR(TEST_TYPE)(pkdvec, 3, 99);
	// assertions
	ASSERT_PACKED_DATA_VAL(pkdvec, 0, 69);
	ASSERT_PACKED_DATA_VAL(pkdvec, 1, 99);
	ASSERT_PACKED_INDICIES_VAL(pkdvec, 0, 0);
	ASSERT_PACKED_INDICIES_VAL(pkdvec, 1, 3);
	ASSERT_NEXT_PACKED_INDEX_VAL(pkdvec, 2);

	// adding 769 to index 12
	MPACKED_VECTOR_ADD_AT_SPARSE_VECTOR(TEST_TYPE)(pkdvec, 100, 769);
	// assertions
	ASSERT_PACKED_DATA_VAL(pkdvec, 0, 69);
	ASSERT_PACKED_DATA_VAL(pkdvec, 1, 99);
	ASSERT_PACKED_DATA_VAL(pkdvec, 2, 769);
	ASSERT_PACKED_INDICIES_VAL(pkdvec, 0, 0);
	ASSERT_PACKED_INDICIES_VAL(pkdvec, 1, 3);
	ASSERT_PACKED_INDICIES_VAL(pkdvec, 2, 100);
	ASSERT_NEXT_PACKED_INDEX_VAL(pkdvec, 3);

	// freing th etest
	MPACKED_VECTOR_FREE(TEST_TYPE)(pkdvec);
}
END_TEST

// add_at test
START_TEST(remove_at_sparse_vector_test)
{
	MPackedVector_mint_t *pkdvec = malloc(sizeof(MPackedVector_mint_t));
	MPACKED_VECTOR_INIT(TEST_TYPE)(pkdvec, 10);

	// creating the vector as the add_at_test case
	MPACKED_VECTOR_ADD_AT_SPARSE_VECTOR(TEST_TYPE)(pkdvec, 0, 69);
	MPACKED_VECTOR_ADD_AT_SPARSE_VECTOR(TEST_TYPE)(pkdvec, 3, 99);
	MPACKED_VECTOR_ADD_AT_SPARSE_VECTOR(TEST_TYPE)(pkdvec, 100, 769);

	// removing the third thingy
	MPACKED_VECTOR_REMOVE_AT_SPARSE_VECTOR(TEST_TYPE)(pkdvec, 3);
	// assertions
	ASSERT_SPARSE_VECTOR_VAL(pkdvec, 3, SIZE_MAX);
	ASSERT_PACKED_INDICIES_VAL(pkdvec, 0, 0);
	ASSERT_PACKED_INDICIES_VAL(pkdvec, 1, 100);
	ASSERT_PACKED_DATA_VAL(pkdvec, 0, 69);
	ASSERT_PACKED_DATA_VAL(pkdvec, 1, 769);
	ASSERT_NEXT_PACKED_INDEX_VAL(pkdvec, 2);

	// freing th etest
	MPACKED_VECTOR_FREE(TEST_TYPE)(pkdvec);
}
END_TEST


static Suite *packed_vector_test_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("mpacked_vector");

	// core test case
	tc_core = tcase_create("Core");

	// ADD MORE CASES TO TC_CORE HERE
	tcase_add_test(tc_core, init_test);
	tcase_add_test(tc_core, add_at_test);
	tcase_add_test(tc_core, remove_at_sparse_vector_test);
	/* tcase_add_test(tc_core, push_back_test); */

	suite_add_tcase(s, tc_core);

	return s;
}

#undef TEST_TYPE
#undef ASSERT_SPARSE_VECTOR_VAL
#undef ASSERT_PACKED_INDICIES_VAL
#undef ASSERT_PACKED_DATA_VAL
#undef ASSERT_NEXT_PACKED_INDEX_VAL
