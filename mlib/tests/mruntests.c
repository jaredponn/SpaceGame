#include <check.h>
#include <stdlib.h>

#include "mlib/mlib.h"
#include "mvectortests.h"


// -----------------------------------------
//    Generic run tests function
// -----------------------------------------

int runTest(int (*fp)(Suite *, SRunner *))
{
	int number_failed = 0;
	Suite *s = NULL;
	SRunner *sr = NULL;

	number_failed = (*fp)(s, sr);

	srunner_free(sr);

	return number_failed;
}

// -----------------------------------------
//    Test suites
// -----------------------------------------
int vector_tests(Suite *s, SRunner *sr)
{
	s = vector_test_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	return srunner_ntests_failed(sr);
}

int main(void)
{
	int number_failed = 0;

	number_failed += runTest(vector_tests);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
