#include <check.h>
#include <stdlib.h>

#include "Stack_Tests.c"
#undef TYPE
#undef TYPED

#include "Vector_Tests.c"
#undef TYPE
#undef TYPED

int main(void) {
        int number_failed;
        Suite *s;
        SRunner *sr;

        s = vector_test_suite();
        sr = srunner_create(s);
        srunner_add_suite(sr, stack_test_suite());

        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
