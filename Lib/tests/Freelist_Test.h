#include <check.h>
#include <stdint.h>
#include "Data_Structures.h"
#include "Lib/E_FreeList.h"

START_TEST(freelist_test)
{
	struct FLIntFreeList testfreelist;
	FLIntFreeList_init(&testfreelist);
	FLIntFreeList_reserve(&testfreelist, 4);

	// adding 0,1,2,3 to the freelist
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(
			FLIntFreeList_add(
				&testfreelist,
				(struct FLInt){.myData = i,
					       .next_free_index = SIZE_MAX}),
			i);
	}

	// testing if 0,1,2,3 are really in the free list
	for (int i = 0; i < 4; ++i) {
		ck_assert_int_eq(FLIntFreeList_get(&testfreelist, i).myData, i);
	}

	// adding too much stuff to the free list. (elements 4)
	ck_assert_int_eq(
		FLIntFreeList_add(&testfreelist,
				  (struct FLInt){.myData = 4,
						 .next_free_index = SIZE_MAX}),
		4);
	ck_assert_int_eq(FLIntFreeList_get(&testfreelist, 4).myData, 4);
	ck_assert_int_eq(FLIntVector_size(&testfreelist.data), 6);
	ck_assert_int_eq(FLIntVector_capacity(&testfreelist.data), 6);

	// adding too much stuff to the free list. (element 5)
	ck_assert_int_eq(
		FLIntFreeList_add(&testfreelist,
				  (struct FLInt){.myData = 5,
						 .next_free_index = SIZE_MAX}),
		5);
	ck_assert_int_eq(FLIntFreeList_get(&testfreelist, 5).myData, 5);
	ck_assert_int_eq(FLIntVector_size(&testfreelist.data), 6);
	ck_assert_int_eq(FLIntVector_capacity(&testfreelist.data), 6);

	// testing the remove_at function. Removing the firstelement
	FLIntFreeList_remove_at(&testfreelist, 0);
	ck_assert_int_eq(FLIntFreeList_get(&testfreelist, 0).myData, 0);
	ck_assert_int_eq(FLIntFreeList_get(&testfreelist, 0).next_free_index,
			 6);

	// adding a new thing to replace that element
	FLIntFreeList_add(
		&testfreelist,
		(struct FLInt){.myData = 7, .next_free_index = SIZE_MAX});
	ck_assert_int_eq(FLIntFreeList_get(&testfreelist, 0).myData, 7);

	// more removing testing
	FLIntFreeList_remove_at(&testfreelist, 0);
	FLIntFreeList_remove_at(&testfreelist, 1);
	FLIntFreeList_remove_at(&testfreelist, 2);
	FLIntFreeList_remove_at(&testfreelist, 4);
	FLIntFreeList_add(
		&testfreelist,
		(struct FLInt){.myData = 100, .next_free_index = SIZE_MAX});
	ck_assert_int_eq(FLIntFreeList_get(&testfreelist, 4).myData, 100);

	FLIntFreeList_add(
		&testfreelist,
		(struct FLInt){.myData = 599, .next_free_index = SIZE_MAX});
	ck_assert_int_eq(FLIntFreeList_get(&testfreelist, 2).myData, 599);
}
END_TEST

START_TEST(free_list_indexing_test_like_cpt)
{
// macros to making adding, removing, and checking things a little more
// terse
#define addSizeMax(assertindex)                                                \
	ck_assert_int_eq(EFreeList_add(&testfreelist, (E){SIZE_MAX}),          \
			 assertindex)
#define removeAt(index)                                                        \
	if (EVector_size(&testfreelist.data) > index                           \
	    && EFreeList_get(&testfreelist, index).next_free_index             \
		       == SIZE_MAX)                                            \
	EFreeList_remove_at(&testfreelist, index)
#define isCurrFreeIndex(val) ck_assert_int_eq(testfreelist.cur_free_index, val)
#define isIndex(index, val)                                                    \
	ck_assert_int_eq(                                                      \
		EVector_get(&testfreelist.data, index).next_free_index, val)
	{

		struct EFreeList testfreelist;
		EFreeList_init(&testfreelist);
		EFreeList_reserve(&testfreelist, 10);

		isCurrFreeIndex(0);
		for (size_t i = 0; i < 10; ++i) {
			isIndex(i, i + 1);
		}
		// removing anywhere should keep it the same because no elements
		// are filled up
		for (size_t i = 0; i < 10000; ++i) {
			removeAt(i);
		}

		isCurrFreeIndex(0);
		for (size_t i = 0; i < 10; ++i) {
			isIndex(i, i + 1);
		}

		// adding a size max
		addSizeMax(0);
		isCurrFreeIndex(1);
		for (size_t i = 1; i < 10; ++i) {
			isIndex(i, i + 1);
		}

		// removig randomg stuff (should still be the same)
		for (size_t i = 1; i < 10000; ++i) {
			removeAt(i);
		}
		isIndex(0, SIZE_MAX);

		// removing the index 0
		removeAt(0);
		isCurrFreeIndex(0);
		for (size_t i = 0; i < 10; ++i) {
			isIndex(i, i + 1);
		}

		// -----------------------------------------
		//    Slightly more complicated scenario
		// -----------------------------------------
		/** 2 [M, M, 3, 4, 5 .. 10] add,add
		  0 [2, M, 3, 4, 5 .. 10] removeAt 0
		  1 [2, 0, 3, 4, 5 .. 10] removeAt 1
		  3 [M, M, M, 4, 5 .. 10] add, add, add
		  1 [M, 3, M, 4, 5 .. 10] removeAt 1
		*/
		addSizeMax(0);
		addSizeMax(1);
		isCurrFreeIndex(2);
		for (size_t i = 2; i < 10; ++i) {
			isIndex(i, i + 1);
		}

		removeAt(0);
		isCurrFreeIndex(0);
		isIndex(0, 2);
		for (size_t i = 2; i < 10; ++i) {
			isIndex(i, i + 1);
		}

		removeAt(1);
		isCurrFreeIndex(1);
		isIndex(0, 2);
		isIndex(1, 0);
		for (size_t i = 2; i < 10; ++i) {
			isIndex(i, i + 1);
		}

		addSizeMax(1);
		addSizeMax(0);
		addSizeMax(2);
		isCurrFreeIndex(3);
		for (size_t i = 4; i < 10; ++i) {
			isIndex(i, i + 1);
		}

		removeAt(1);
		isCurrFreeIndex(1);
		isIndex(0, SIZE_MAX);
		isIndex(1, 3);
		isIndex(2, SIZE_MAX);
		for (size_t i = 4; i < 10; ++i) {
			isIndex(i, i + 1);
		}
	}
#undef addToFreeList
#undef removeAt
#undef isCurrFreeIndex
#undef isIndex
#undef addSizeMax
}
END_TEST


static Suite *freelist_test_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Free List");

	// core test case
	tc_core = tcase_create("Core");

	// ADD MORE CASES TO TC_CORE HERE
	tcase_add_test(tc_core, freelist_test);
	tcase_add_test(tc_core, free_list_indexing_test_like_cpt);
	// tcase_add_test(tc_core, stack_test);


	suite_add_tcase(s, tc_core);

	return s;
}
