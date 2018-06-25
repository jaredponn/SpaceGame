#include <check.h>
#include <stdlib.h>

#include "Lib/GenericFreeList.h"
#include "Lib/GenericStack.h"
#include "Lib/GenericVector.h"
// stack
STACK_DECLARE(int, i)
STACK_DEFINE(int, i)

STACK_DECLARE(size_t, size)
STACK_DEFINE(size_t, size)

// vector
VECTOR_DECLARE(int, i)
VECTOR_DEFINE(int, i)

// freelist
struct FL_int {
        int myData;
        size_t next_free_index;
};

VECTOR_DECLARE(struct FL_int, FL_int)
VECTOR_DEFINE(struct FL_int, FL_int)

FREELIST_DECLARE(struct FL_int, FL_int)
FREELIST_DEFINE(struct FL_int, FL_int)

#include "Freelist_Test.h"
#include "Stack_Tests.h"
#include "Vector_Tests.h"

int main(void) {
        int number_failed;
        Suite *s;
        SRunner *sr;

        s = vector_test_suite();
        sr = srunner_create(s);
        srunner_add_suite(sr, stack_test_suite());
        srunner_add_suite(sr, freelist_test_suite());

        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
