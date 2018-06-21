#include <check.h>

START_TEST(vector_test_1) {
        struct i_Vector testvec;
        i_vector_init(&testvec);

        i_vector_reserve(&testvec, 3);

        // testing to see if it allocated properly
        ck_assert_int_eq(i_vector_capacity(&testvec), 3);  // should be 10
        ck_assert_int_eq(i_vector_size(&testvec), 0);

        // testing pushback
        i_vector_pushback(&testvec, 3);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 3);
        ck_assert_int_eq(i_vector_size(&testvec), 1);

        // testing pushback
        i_vector_pushback(&testvec, 4);
        ck_assert_int_eq(i_vector_get(&testvec, 0), 3);
        ck_assert_int_eq(i_vector_get(&testvec, 1), 4);
        ck_assert_int_eq(i_vector_size(&testvec), 2);

        // testing pushback
        i_vector_pushback(&testvec, 5);
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
        i_vector_pushback(&testvec, 6);
        ck_assert_int_eq(i_vector_get(&testvec, 2), 6);

        // testing the push back if the array is already full
        i_vector_pushback(&testvec, 7);
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

START_TEST(vector_test_2) {
        struct i_Vector testvec;
        i_vector_init(&testvec);

        // reservig 4 elements
        i_vector_reserve(&testvec, 4);
        ck_assert_int_eq(i_vector_size(&testvec), 0);

        // pushing 0,1,2,3 and ensuring they pushed properly
        i_vector_pushback(&testvec, 0);
        ck_assert_int_eq(i_vector_size(&testvec), 1);
        i_vector_pushback(&testvec, 1);
        ck_assert_int_eq(i_vector_size(&testvec), 2);
        i_vector_pushback(&testvec, 2);
        ck_assert_int_eq(i_vector_size(&testvec), 3);
        i_vector_pushback(&testvec, 3);
        ck_assert_int_eq(i_vector_size(&testvec), 4);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        // testing pop back
        ck_assert_int_eq(i_vector_popback(&testvec), 3);
        ck_assert_int_eq(i_vector_size(&testvec), 3);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        ck_assert_int_eq(i_vector_popback(&testvec), 2);
        ck_assert_int_eq(i_vector_size(&testvec), 2);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        ck_assert_int_eq(i_vector_popback(&testvec), 1);
        ck_assert_int_eq(i_vector_size(&testvec), 1);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);

        ck_assert_int_eq(i_vector_popback(&testvec), 0);
        ck_assert_int_eq(i_vector_size(&testvec), 0);
        ck_assert_int_eq(i_vector_capacity(&testvec), 4);
}
END_TEST

static Suite *vector_test_suite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("Stack");

        // core test case
        tc_core = tcase_create("Core");

        // ADD MORE CASES TO TC_CORE HERE
        tcase_add_test(tc_core, vector_test_1);
        tcase_add_test(tc_core, vector_test_2);
        // tcase_add_test(tc_core, stack_test);

        suite_add_tcase(s, tc_core);

        return s;
}
