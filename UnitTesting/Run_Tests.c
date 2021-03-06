#include <check.h>
#include <stdlib.h>

// Component test includes
#include "Src/tests/CPT_Appearance_Tests.h"
#include "Src/tests/CPT_Components_Tests.h"

// Lib tests includes
#include "Lib/tests/Freelist_Test.h"
#include "Lib/tests/PackedVector_Tests.h"
#include "Lib/tests/Stack_Tests.h"
#include "Lib/tests/UTI_strcatTest.h"
#include "Lib/tests/Vector_Tests.h"

// -----------------------------------------
//    Generic run test function
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
int cptEngineTests(Suite *s, SRunner *sr)
{
	s = cpt_engine_test_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	return srunner_ntests_failed(sr);
}

int specificCptTests(Suite *s, SRunner *sr)
{
	s = appearances_test_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	return srunner_ntests_failed(sr);
}

int libTests(Suite *s, SRunner *sr)
{
	// starts withe the vector test suite
	s = vector_test_suite();
	sr = srunner_create(s);

	// adds the rest of the test suites
	srunner_add_suite(sr, stack_test_suite());
	srunner_add_suite(sr, freelist_test_suite());
	srunner_add_suite(sr, UTI_strcatTestSuite());
	srunner_add_suite(sr, packedvector_test_suite());

	srunner_run_all(sr, CK_NORMAL);

	return srunner_ntests_failed(sr);
}
// -----------------------------------------
//    Main
// -----------------------------------------

int main(void)
{
	int number_failed = 0;

	number_failed += runTest(&libTests);
	number_failed += runTest(&cptEngineTests);
	number_failed += runTest(&specificCptTests);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
