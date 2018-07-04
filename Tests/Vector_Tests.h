#include <check.h>
#include "Data_Structures.h"

START_TEST(vector_test_1) {
        struct i_Vector testvec;
        i_vector_init(&testvec);

        i_vector_reserve(&testvec, 3);

        // testing to see if it allocated properly
        ck_assert_int_eq(i_vector_capacity(&testvec), 3);  // should be 3
        ck_assert_int_eq(i_vector_size(&testvec), 0);

        // testing push_back
        i_vector_push_back(&testvec, 3);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 3);
        ck_assert_int_eq(i_vector_size(&testvec), 1);

        // testing push_back
        i_vector_push_back(&testvec, 4);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 3);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 4);
        ck_assert_int_eq(i_vector_size(&testvec), 2);

        // testing push_back
        i_vector_push_back(&testvec, 5);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 3);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 4);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 5);
        ck_assert_int_eq(i_vector_size(&testvec), 3);

        // testing delete
        i_vector_remove(&testvec, 0);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 4);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 5);
        ck_assert_int_eq(i_vector_size(&testvec), 2);

        // pushing back again
        i_vector_push_back(&testvec, 6);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 6);

        // testing the push back if the array is already full
        i_vector_push_back(&testvec, 7);
        ck_assert_int_eq(i_vector_get(&testvec, 3), 7);
        ck_assert_int_eq(i_vector_size(&testvec), 4);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        // reserving extra memory
        i_vector_reserve(&testvec, 100);

        ck_assert_int_eq(i_vector_size(&testvec), 4);
        ck_assert_int_eq(i_vector_capacity(&testvec), 100);

        // shrink it back to 4
        i_vector_reserve(&testvec, 4);
        ck_assert_int_eq(i_vector_size(&testvec), 4);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        i_vector_free(&testvec);
}
END_TEST

// testing pop_back
START_TEST(vector_test_2) {
        struct i_Vector testvec;
        i_vector_init(&testvec);

        // reservig 4 elements
        i_vector_reserve(&testvec, 4);
        ck_assert_int_eq(i_vector_size(&testvec), 0);

        // pushing 0,1,2,3 and ensuring they pushed properly
        i_vector_push_back(&testvec, 0);
        ck_assert_int_eq(i_vector_size(&testvec), 1);
        i_vector_push_back(&testvec, 1);
        ck_assert_int_eq(i_vector_size(&testvec), 2);
        i_vector_push_back(&testvec, 2);
        ck_assert_int_eq(i_vector_size(&testvec), 3);
        i_vector_push_back(&testvec, 3);
        ck_assert_int_eq(i_vector_size(&testvec), 4);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        // testing pop back
        ck_assert_int_eq(i_vector_pop_back(&testvec), 3);
        ck_assert_int_eq(i_vector_size(&testvec), 3);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        ck_assert_int_eq(i_vector_pop_back(&testvec), 2);
        ck_assert_int_eq(i_vector_size(&testvec), 2);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        ck_assert_int_eq(i_vector_pop_back(&testvec), 1);
        ck_assert_int_eq(i_vector_size(&testvec), 1);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        ck_assert_int_eq(i_vector_pop_back(&testvec), 0);
        ck_assert_int_eq(i_vector_size(&testvec), 0);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);
}
END_TEST

// testing the swap function
START_TEST(vector_test_3) {
        struct i_Vector testvec;
        i_vector_init(&testvec);

        // reservig 4 elements
        i_vector_reserve(&testvec, 4);
        ck_assert_int_eq(i_vector_size(&testvec), 0);

        // pushing 0,1,2,3 and ensuring they pushed properly
        i_vector_push_back(&testvec, 0);
        ck_assert_int_eq(i_vector_size(&testvec), 1);
        i_vector_push_back(&testvec, 1);
        ck_assert_int_eq(i_vector_size(&testvec), 2);
        i_vector_push_back(&testvec, 2);
        ck_assert_int_eq(i_vector_size(&testvec), 3);
        i_vector_push_back(&testvec, 3);
        ck_assert_int_eq(i_vector_size(&testvec), 4);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        // so we have a vector with [0, 1, 2, 3] now

        // testing swap
        // swapping index 0 with in)bbbdex 3, so we should have [3, 1, 2, 0]
        i_vector_swap(&testvec, 0, 3);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 3);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 1);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 2);
        ck_assert_int_eq(i_vector_get(&testvec, 3), 0);

        // switching index 0 with index 2, so we should now have [2, 1, 3, 0]
        i_vector_swap(&testvec, 0, 2);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 2);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 1);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 3);
        ck_assert_int_eq(i_vector_get(&testvec, 3), 0);

        // swapping the same index 0 and index 0. So we should have [2, 1, 3, 0]
        i_vector_swap(&testvec, 0, 0);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 2);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 1);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 3);
        ck_assert_int_eq(i_vector_get(&testvec, 3), 0);

        // using the common idiom of swapping an index (2) with the last
        // element, so we should have:
        //  [2, 1, 0, 3]
        i_vector_swap_back(&testvec, 2);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 2);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 1);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 0);
        ck_assert_int_eq(i_vector_get(&testvec, 3), 3);

        // testing swapping the last element (should be the same)
        // so we should have:
        //  [2, 1, 0, 3]
        i_vector_swap_back(&testvec, 3);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 2);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 1);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 0);
        ck_assert_int_eq(i_vector_get(&testvec, 3), 3);

        // testing swapping the 1 index  with the last
        // so we should have:
        //  [2, 3, 0, 1]
        i_vector_swap_back(&testvec, 1);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 2);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 3);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 0);
        ck_assert_int_eq(i_vector_get(&testvec, 3), 1);

        // Testing how it fares when the capacity is bigger than the size
        // we pop_back the last element off so we should have
        //  [2, 3, 0], the size should be 3, and the capacity should be 4
        ck_assert_int_eq(i_vector_pop_back(&testvec), 1);
        ck_assert_int_eq(i_vector_size(&testvec), 3);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        // and swapping the 0th index with the lsat again, so we should have
        // [0, 3, 2]
        i_vector_swap_back(&testvec, 0);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 0);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 3);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 2);

        // and swapping the 1th index with the lsat again, so we should have
        // [0, 2, 3]
        i_vector_swap_back(&testvec, 1);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 0);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 2);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 3);

        i_vector_free(&testvec);
}
END_TEST

static Suite *vector_test_suite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("Vector");

        // core test case
        tc_core = tcase_create("Core");

        // ADD MORE CASES TO TC_CORE HERE
        tcase_add_test(tc_core, vector_test_1);
        tcase_add_test(tc_core, vector_test_2);
        tcase_add_test(tc_core, vector_test_3);
        // tcase_add_test(tc_core, stack_test);

        suite_add_tcase(s, tc_core);

        return s;
}
