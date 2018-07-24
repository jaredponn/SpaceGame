#include <check.h>
#include <stdint.h>
#include "Data_Structures.h"

START_TEST(freelist_test) {
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
            FLIntFreeList_add(
                &testfreelist,
                (struct FLInt){.myData = 4, .next_free_index = SIZE_MAX}),
            4);
        ck_assert_int_eq(FLIntFreeList_get(&testfreelist, 4).myData, 4);
        ck_assert_int_eq(FLIntVector_size(&testfreelist.data), 6);
        ck_assert_int_eq(FLIntVector_capacity(&testfreelist.data), 6);

        // adding too much stuff to the free list. (element 5)
        ck_assert_int_eq(
            FLIntFreeList_add(
                &testfreelist,
                (struct FLInt){.myData = 5, .next_free_index = SIZE_MAX}),
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

static Suite *freelist_test_suite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("Free List");

        // core test case
        tc_core = tcase_create("Core");

        // ADD MORE CASES TO TC_CORE HERE
        tcase_add_test(tc_core, freelist_test);
        // tcase_add_test(tc_core, stack_test);

        suite_add_tcase(s, tc_core);

        return s;
}
