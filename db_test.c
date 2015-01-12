#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "dbmod.h"
#include "dbmod.c"
#include "db.c"
/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

int checkArgumentFile(int argc, char* argv[]);

void testCheckArgumentFile() {
    int argc = 1;
    char* argv[] = {"./db"};
    int expected = 0;
    int result = checkArgumentFile(argc, argv);

    CU_ASSERT_EQUAL(result, expected);
}


Node readDatabase(char* filename);

void testReadDatabase() {
    char* filename = "SWE.db";
    char* expectKey = "Anna";
    char* expectValue = "26";
    Node result = readDatabase(filename);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT(strcmp(result->key, expectKey) == 0);
    CU_ASSERT(strcmp(result->value, expectValue) == 0);
}




int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }
    /* Add a suite to the registry */
    pSuite = CU_add_suite("db_test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testCheckArgumentFile", testCheckArgumentFile)) ||
	(NULL == CU_add_test(pSuite, "testReadDatabase", testReadDatabase))
	) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
