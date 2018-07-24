#include <check.h>
#include <stdint.h>
#include "Data_Structures.h"

START_TEST(freelist_test) {
        struct FL_int_FreeList testfreelist;
        FL_int_freelist_init(&testfreelist);
        FL_int_freelist_reserve(&testfreelist, 4);

        // adding 0,1,2,3 to the freelist
        for (int i = 0; i < 4; ++i) {
                ck_assert_int_eq(
                    FL_int_freelist_add(
                        &testfreelist,
                        (struct FL_int){.myData = i,
                                        .next_free_index = SIZE_MAX}),
                    i);
        }

        // testing if 0,1,2,3 are really in the free list
        for (int i = 0; i < 4; ++i) {
                ck_assert_int_eq(FL_int_freelist_get(&testfreelist, i).myData,
                                 i);
        }

        // adding too much stuff to the free list. (elements 4)
        ck_assert_int_eq(
            FL_int_freelist_add(
                &testfreelist,
                (struct FL_int){.myData = 4, .next_free_index = SIZE_MAX}),
            4);
        ck_assert_int_eq(FL_int_freelist_get(&testfreelist, 4).myData, 4);
        ck_assert_int_eq(FL_int_vector_size(&testfreelist.data), 6);
        ck_assert_int_eq(FL_int_vector_capacity(&testfreelist.data), 6);

        // adding too much stuff to the free list. (element 5)
        ck_assert_int_eq(
            FL_int_freelist_add(
                &testfreelist,
                (struct FL_int){.myData = 5, .next_free_index = SIZE_MAX}),
            5);
        ck_assert_int_eq(FL_int_freelist_get(&testfreelist, 5).myData, 5);
        ck_assert_int_eq(FL_int_vector_size(&testfreelist.data), 6);
        ck_assert_int_eq(FL_int_vector_capacity(&testfreelist.data), 6);

        // testing the remove_at function. Removing the firstelement
        FL_int_freelist_remove_at(&testfreelist, 0);
        ck_assert_int_eq(FL_int_freelist_get(&testfreelist, 0).myData, 0);
        ck_assert_int_eq(FL_int_freelist_get(&testfreelist, 0).next_free_index,
                         6);

        // adding a new thing to replace that element
        FL_int_freelist_add(
            &testfreelist,
            (struct FL_int){.myData = 7, .next_free_index = SIZE_MAX});
        ck_assert_int_eq(FL_int_freelist_get(&testfreelist, 0).myData, 7);

        // more removing testing
        FL_int_freelist_remove_at(&testfreelist, 0);
        FL_int_freelist_remove_at(&testfreelist, 1);
        FL_int_freelist_remove_at(&testfreelist, 2);
        FL_int_freelist_remove_at(&testfreelist, 4);
        FL_int_freelist_add(
            &testfreelist,
            (struct FL_int){.myData = 100, .next_free_index = SIZE_MAX});
        ck_assert_int_eq(FL_int_freelist_get(&testfreelist, 4).myData, 100);

        FL_int_freelist_add(
            &testfreelist,
            (struct FL_int){.myData = 599, .next_free_index = SIZE_MAX});
        ck_assert_int_eq(FL_int_freelist_get(&testfreelist, 2).myData, 599);
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
