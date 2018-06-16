#include <check.h>
#include <stdlib.h>

#include "Lib/Stack/IntStack.h"

START_TEST(stack_test) {
        // creating the empty stack
        struct i_Stack *testStack = i_stack_new();
        ck_assert_int_eq(i_stack_size(testStack), 0);  // should have size 0

        // pushing 2 to the top of the stack
        i_stack_push(testStack, 2);
        ck_assert_int_eq(i_stack_size(testStack), 1);  // should have size 1
        ck_assert_int_eq(i_stack_peek(testStack), 2);  // top should be 2

        // pushing 3 to the top of the stack
        i_stack_push(testStack, 3);
        ck_assert_int_eq(i_stack_size(testStack), 2);
        ck_assert_int_eq(i_stack_peek(testStack), 3);

        // popping from the stack
        ck_assert_int_eq(i_stack_pop(testStack), 3);
        ck_assert_int_eq(i_stack_size(testStack), 1);

        //
}
END_TEST

static Suite *stack_suite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("Stack");

        // core test case
        tc_core = tcase_create("Core");

        // ADD MORE CASES TO TC_CORE HERE
        tcase_add_test(tc_core, stack_test);
        // tcase_add_test(tc_core, stack_test);

        suite_add_tcase(s, tc_core);

        return s;
}

int main(void) {
        int number_failed;
        Suite *s;
        SRunner *sr;

        s = stack_suite();
        sr = srunner_create(s);

        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
