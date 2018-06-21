#include <check.h>

START_TEST(freelist_test) {
        struct i_FreeList testfreelist;
        i_freelist_init(&testfreelist);
        i_freelist_reserve(&testfreelist, 4);

        // adding stuff to the freelist
        ck_assert_int_eq(i_freelist_add(&testfreelist, 0), 0);
        ck_assert_int_eq(i_freelist_add(&testfreelist, 1), 1);
        ck_assert_int_eq(i_freelist_add(&testfreelist, 2), 2);
        ck_assert_int_eq(i_freelist_add(&testfreelist, 3), 3);

        ck_assert_int_eq(i_freelist_get(&testfreelist, 0), 0);
        ck_assert_int_eq(i_freelist_get(&testfreelist, 1), 1);
        ck_assert_int_eq(i_freelist_get(&testfreelist, 2), 2);
        ck_assert_int_eq(i_freelist_get(&testfreelist, 3), 3);

        // adding too much to the freelist:
        ck_assert_int_eq(i_freelist_add(&testfreelist, 4), 4);
        ck_assert_int_eq(i_freelist_get(&testfreelist, 4), 4);
        ck_assert_int_eq(i_vector_size(&testfreelist.data), 5);
        ck_assert_int_eq(i_vector_capacity(&testfreelist.data), 6);
        i_freelist_add(&testfreelist, 5);
        ck_assert_int_eq(i_vector_capacity(&testfreelist.data), 6);

        // testing the removeat function
        i_freelist_removeat(&testfreelist, 0);
        ck_assert_int_eq(i_freelist_get(&testfreelist, 0), 0);
        i_freelist_add(&testfreelist, 7);
        ck_assert_int_eq(i_freelist_get(&testfreelist, 0), 7);

        // more removing testing
        i_freelist_removeat(&testfreelist, 0);
        i_freelist_removeat(&testfreelist, 1);
        i_freelist_removeat(&testfreelist, 2);
        i_freelist_removeat(&testfreelist, 4);
        i_freelist_add(&testfreelist, 100);
        ck_assert_int_eq(i_freelist_get(&testfreelist, 4), 100);

        i_freelist_add(&testfreelist, 599);
        ck_assert_int_eq(i_freelist_get(&testfreelist, 2), 599);
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
