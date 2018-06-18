#include <check.h>
#include "../Lib/FreeList/GenericFreeList.h"

START_TEST(freelist_test) {
        // creating the empty stack
}
END_TEST

static Suite *freelist_test_suite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("Stack");

        // core test case
        tc_core = tcase_create("Core");

        // ADD MORE CASES TO TC_CORE HERE
        tcase_add_test(tc_core, freelist_test);
        // tcase_add_test(tc_core, stack_test);

        suite_add_tcase(s, tc_core);

        return s;
}
