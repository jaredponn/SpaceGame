#include <check.h>
#include <stdlib.h>

#include "Lib/Stack/IntStack.h"
#include "Lib/Vector/IntVector.h"

START_TEST(stack_test) {
        // creating the empty stack
        struct i_Stack testStack;
        i_stack_init(&testStack);
        ck_assert_int_eq(i_stack_size(&testStack), 0);  // should have size 0

        // pushing 2 to the top of the stack
        i_stack_push(&testStack, 2);
        ck_assert_int_eq(i_stack_size(&testStack), 1);  // should have size 1
        ck_assert_int_eq(i_stack_peek(&testStack), 2);  // top should be 2

        // pushing 3 to the top of the stack
        i_stack_push(&testStack, 3);
        ck_assert_int_eq(i_stack_size(&testStack), 2);
        ck_assert_int_eq(i_stack_peek(&testStack), 3);

        // popping from the stack
        ck_assert_int_eq(i_stack_pop(&testStack), 3);
        ck_assert_int_eq(i_stack_size(&testStack), 1);

        // popping from the stack
        ck_assert_int_eq(i_stack_pop(&testStack), 2);
        ck_assert_int_eq(i_stack_size(&testStack), 0);
}
END_TEST

START_TEST(vector_test) {
        // creating the empty stack
        struct Vector testvec;
        vector_init(&testvec);

        vector_reserve(&testvec, 3);

        // testing to see if it allocated properly
        ck_assert_int_eq(vector_capacity(&testvec), 3);  // should be 10
        ck_assert_int_eq(vector_size(&testvec), 0);

        // testing pushback
        vector_pushback(&testvec, 3);
        ck_assert_int_eq(vector_get(&testvec, 0), 3);
        ck_assert_int_eq(vector_size(&testvec), 1);

        // testing pushback
        vector_pushback(&testvec, 4);
        ck_assert_int_eq(vector_get(&testvec, 0), 3);
        ck_assert_int_eq(vector_get(&testvec, 1), 4);
        ck_assert_int_eq(vector_size(&testvec), 2);

        // testing pushback
        vector_pushback(&testvec, 5);
        ck_assert_int_eq(vector_get(&testvec, 0), 3);
        ck_assert_int_eq(vector_get(&testvec, 1), 4);
        ck_assert_int_eq(vector_get(&testvec, 2), 5);
        ck_assert_int_eq(vector_size(&testvec), 3);

        // testing delete
        vector_remove(&testvec, 0);
        ck_assert_int_eq(vector_get(&testvec, 0), 4);
        ck_assert_int_eq(vector_get(&testvec, 1), 5);
        ck_assert_int_eq(vector_size(&testvec), 2);

        // pushing back again
        vector_pushback(&testvec, 6);
        ck_assert_int_eq(vector_get(&testvec, 2), 6);

        // testing the push back if the array is already full
        vector_pushback(&testvec, 7);
        ck_assert_int_eq(vector_get(&testvec, 3), 7);
        ck_assert_int_eq(vector_size(&testvec), 4);
        ck_assert_int_eq(vector_capacity(&testvec), 4);

        // reserving extra memory
        vector_reserve(&testvec, 100);

        ck_assert_int_eq(vector_size(&testvec), 4);
        ck_assert_int_eq(vector_capacity(&testvec), 100);

        // shrink it back to 4
        vector_reserve(&testvec, 4);
        ck_assert_int_eq(vector_size(&testvec), 4);
        ck_assert_int_eq(vector_capacity(&testvec), 4);

        vector_free(&testvec);
}
END_TEST

static Suite *test_suite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("Stack");

        // core test case
        tc_core = tcase_create("Core");

        // ADD MORE CASES TO TC_CORE HERE
        tcase_add_test(tc_core, stack_test);
        tcase_add_test(tc_core, vector_test);
        // tcase_add_test(tc_core, stack_test);

        suite_add_tcase(s, tc_core);

        return s;
}

int main(void) {
        int number_failed;
        Suite *s;
        SRunner *sr;

        s = test_suite();
        sr = srunner_create(s);

        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
