#pragma once
#include <check.h>
#include "Src/Engine/Components/Components.h"

// TODO WRITE THESE UNIT TESTS

START_TEST(free_list_indexing_test)
{
// macros to making adding, removing, and checking things a little more
// terse
#define updateCurFreeIndex(assertindex) CPT_updateCurFreeIndex(&testcomponents)
#define deleteEntityAt(index) CPT_deleteEntityAt(&testcomponents, index)

#define isCurrFreeIndex(val)                                                   \
	ck_assert_int_eq(CPT_getCurFreeIndex(&testcomponents), val)

#define isFreeListIndex(index, val)                                            \
	ck_assert_int_eq(MarkedIndexVector_get(                                \
				 &testcomponents.free_elements.data, index)    \
				 .next_free_index,                             \
			 val)


#define isFreeListIndexUsed(index)                                             \
	ck_assert_int_eq(MarkedIndexVector_get(                                \
				 &testcomponents.free_elements.data, index)    \
				 .is_used,                                     \
			 true)

#define isFreeListIndexFree(index)                                             \
	ck_assert_int_eq(MarkedIndexVector_get(                                \
				 &testcomponents.free_elements.data, index)    \
				 .is_used,                                     \
			 false)
#define addEntity()                                                            \
	CPT_addPosition(&testcomponents, &(Position){.x = 1, .y = 1})

	struct CPT_Components testcomponents;
	CPT_initComponents(&testcomponents, 10);

	isCurrFreeIndex(0);
	for (size_t i = 0; i < 10; ++i) {
		isFreeListIndex(i, i + 1);
		isFreeListIndexFree(i);
	}
	// removing anywhere should keep it the same because no elements
	// are filled up
	for (size_t i = 0; i < 10000; ++i) {
		deleteEntityAt(i);
	}

	isCurrFreeIndex(0);
	for (size_t i = 0; i < 10; ++i) {
		isFreeListIndex(i, i + 1);
		isFreeListIndexFree(i);
	}

	// trying to update the current free index even though it is already
	// free
	updateCurFreeIndex();
	isCurrFreeIndex(0);

	updateCurFreeIndex();
	updateCurFreeIndex();
	isCurrFreeIndex(0);

	for (size_t i = 1; i < 10; ++i) {
		isFreeListIndex(i, i + 1);
	}

	// removig randomg stuff (should still be the same)
	for (size_t i = 1; i < 10000; ++i) {
		deleteEntityAt(i);
	}

	isCurrFreeIndex(0);
	addEntity();
	isFreeListIndexUsed(0);
	isCurrFreeIndex(0);

	updateCurFreeIndex();
	isFreeListIndexUsed(0);
	isCurrFreeIndex(1);

	// removing the index 0
	deleteEntityAt(0);
	isCurrFreeIndex(0);
	for (size_t i = 0; i < 10; ++i) {
		isFreeListIndex(i, i + 1);
		isFreeListIndexFree(i);
	}

	// -----------------------------------------
	//    Slightly more complicated scenario
	// -----------------------------------------
	/** 2 [M, M, 3, 4, 5 .. 10] add,add
	  0 [2, M, 3, 4, 5 .. 10] deleteEntityAt 0
	  1 [2, 0, 3, 4, 5 .. 10] deleteEntityAt 1
	  3 [M, M, M, 4, 5 .. 10] add, add, add
	  1 [M, 3, M, 4, 5 .. 10] deleteEntityAt 1
	*/
	updateCurFreeIndex();
	isCurrFreeIndex(0);
	isFreeListIndexFree(0);

	addEntity();
	isFreeListIndexUsed(0);
	isCurrFreeIndex(0);

	updateCurFreeIndex();
	isFreeListIndexUsed(0);
	isCurrFreeIndex(1);

	addEntity();
	isFreeListIndexUsed(1);
	isCurrFreeIndex(1);

	updateCurFreeIndex();

	isCurrFreeIndex(2);
	isFreeListIndexUsed(0);
	isFreeListIndexUsed(1);
	for (size_t i = 2; i < 10; ++i) {
		isFreeListIndex(i, i + 1);
		isFreeListIndexFree(i);
	}
}
END_TEST

// this should recreate the scenario that crashes the system
START_TEST(free_list_indexing_test2)
{
	struct CPT_Components testcomponents;
	CPT_initComponents(&testcomponents, 10);
	isCurrFreeIndex(0);

	// updating and adding an enttiy
	updateCurFreeIndex();
	addEntity();
	isCurrFreeIndex(0);
	isFreeListIndex(0, 1);
	isFreeListIndexUsed(0);

	// updating / adding an entity
	updateCurFreeIndex();
	addEntity();
	isCurrFreeIndex(1);
	isFreeListIndexUsed(1);

	// deleint gan entity
	updateCurFreeIndex();
	deleteEntityAt(1);
	isCurrFreeIndex(1);
	isFreeListIndexFree(1);

	// adding an entity
	updateCurFreeIndex();
	isCurrFreeIndex(1);
	addEntity();
	isCurrFreeIndex(1);

	isFreeListIndexUsed(0);
	isFreeListIndexUsed(1);
	//
	// // okaylisten here buddy
	isFreeListIndex(0, 1);
	isFreeListIndex(1, 2);
	//
	// // okay fils
	updateCurFreeIndex();
	isCurrFreeIndex(2);
}
#undef deleteEntityAt
#undef isCurrFreeIndex
#undef isFreeListIndex
#undef updateCurFreeIndex
END_TEST

START_TEST(packed_array_swapping_test)
#define updateCurFreeIndex() CPT_updateCurFreeIndex(&testcomponents)

#define deleteEntityAt(index) CPT_deleteEntityAt(&testcomponents, index)

#define addPosition(_x, _y)                                                    \
	CPT_addPosition(&testcomponents, &(Position){.x = _x, .y = _y})

#define isPosSparseVectorIndex(index, desired)                                 \
	ck_assert_int_eq(                                                      \
		SizetVector_get(&CPT_managerGet(Position)(&testcomponents)     \
					 ->sparse_vector,                      \
				index),                                        \
		desired)

#define isPosPackedIndicesIndex(index, desired)                                \
	ck_assert_int_eq(                                                      \
		SizetVector_get(&CPT_managerGet(Position)(&testcomponents)     \
					 ->packed_indices,                     \
				index),                                        \
		desired)

#define isPosPackedVecIndex(index, _x, _y)                                     \
	ck_assert_int_eq(                                                      \
		PositionVector_get(&CPT_managerGet(Position)(&testcomponents)  \
					    ->packed_data,                     \
				   index)                                      \
			.x,                                                    \
		_x);                                                           \
	ck_assert_int_eq(                                                      \
		PositionVector_get(&CPT_managerGet(Position)(&testcomponents)  \
					    ->packed_data,                     \
				   index)                                      \
			.y,                                                    \
		_y)

#define isPosPackedSize(assertsize)                                            \
	ck_assert_int_eq(                                                      \
		SizetVector_size(&CPT_managerGet(Position)(&testcomponents)    \
					  ->packed_indices),                   \
		assertsize);                                                   \
	ck_assert_int_eq(                                                      \
		PositionVector_size(&CPT_managerGet(Position)(&testcomponents) \
					     ->packed_data),                   \
		assertsize)

{
	struct CPT_Components testcomponents;
	CPT_initComponents(&testcomponents, 10);
	// TODO - write this unit test. It seems to work right now but maybe add
	// this just to be safe
}


#undef deleteEntityAt
#undef updateCurFreeIndex
END_TEST
static Suite *cpt_engine_test_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Component engine test suite");

	// core test case
	tc_core = tcase_create("Core");

	// ADD MORE CASES TO TC_CORE HERE
	tcase_add_test(tc_core, free_list_indexing_test);
	tcase_add_test(tc_core, free_list_indexing_test2);
	tcase_add_test(tc_core, packed_array_swapping_test);

	suite_add_tcase(s, tc_core);

	return s;
}
