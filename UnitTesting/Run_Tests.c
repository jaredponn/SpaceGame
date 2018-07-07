#include <check.h>
#include <stdlib.h>

#include "Lib/tests/ComponentManager_Tests.h"
#include "Lib/tests/Freelist_Test.h"
#include "Lib/tests/Stack_Tests.h"
#include "Lib/tests/UTI_strcatTest.h"
#include "Lib/tests/Vector_Tests.h"

int libTests(void) {
        int number_failed;
        Suite* s;
        SRunner* sr;

        // starts withe the vector test suite
        s = vector_test_suite();
        sr = srunner_create(s);

        // adds the rest of the test suites
        srunner_add_suite(sr, stack_test_suite());
        srunner_add_suite(sr, freelist_test_suite());
        srunner_add_suite(sr, UTI_strcatTestSuite());
        srunner_add_suite(sr, componentmanager_test_suite());

        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);

        return number_failed;
}

int main(void) {
        int number_failed = 0;

        number_failed += libTests();

        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
