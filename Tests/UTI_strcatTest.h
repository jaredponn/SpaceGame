#pragma once
#include <check.h>
#include "Lib/Util.h"

START_TEST(UTI_strcatTest) {
        char *teststr0 = "yop";
        char *teststr1 = "poy";

        char *newstr = UTI_strcat(teststr0, teststr1);
        ck_assert_int_eq(strlen(newstr), 6);

        ck_assert_int_eq(newstr[0], 'y');
        ck_assert_int_eq(newstr[1], 'o');
        ck_assert_int_eq(newstr[2], 'p');
        ck_assert_int_eq(newstr[3], 'p');
        ck_assert_int_eq(newstr[4], 'o');
        ck_assert_int_eq(newstr[5], 'y');
        ck_assert_int_eq(newstr[6], '\0');
}
END_TEST

static Suite *UTI_strcatTestSuite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("UTI_strcat");

        // core test case
        tc_core = tcase_create("Core");

        // ADD MORE CASES TO TC_CORE HERE
        tcase_add_test(tc_core, UTI_strcatTest);
        // tcase_add_test(tc_core, stack_test);

        suite_add_tcase(s, tc_core);

        return s;
}
