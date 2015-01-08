#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

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

Node database(Node db);

void testDatabase() {
    Node db;
    Node result = database(db);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

Node newEntry(Node db);

void testNewEntry() {
    Node db;
    Node result = newEntry(db);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void query(Node db);

void testQuery() {
    Node db;
    query(db);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

Node readDatabase(char* filename);

void testReadDatabase() {
    char* filename = "someTestFile";
    char* expectKey = "Anna";
    char* expectValue = "26";
    Node result = readDatabase(filename);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result->key, expectKey);
    CU_ASSERT_STRING_EQUAL(result->value, expectValue);
}

void readline(char* dest, int n, FILE* source);

void testReadline() {
    char* dest;
    int n;
    FILE* source;
    readline(dest, n, source);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

Node removeEntry(Node db);

void testRemoveEntry() {
    Node db;
    Node result = removeEntry(db);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

Node updateEntry(Node db);

void testUpdateEntry() {
    Node db;
    Node result = updateEntry(db);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}



int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("db_test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testCheckArgumentFile", testCheckArgumentFile)) ||
            (NULL == CU_add_test(pSuite, "testChooseOp", testChooseOp)) ||
            (NULL == CU_add_test(pSuite, "testDatabase", testDatabase)) ||
            (NULL == CU_add_test(pSuite, "testNewEntry", testNewEntry)) ||
            (NULL == CU_add_test(pSuite, "testQuery", testQuery)) ||
            (NULL == CU_add_test(pSuite, "testReadDatabase", testReadDatabase)) ||
            (NULL == CU_add_test(pSuite, "testReadline", testReadline)) ||
            (NULL == CU_add_test(pSuite, "testRemoveEntry", testRemoveEntry)) ||
            (NULL == CU_add_test(pSuite, "testUpdateEntry", testUpdateEntry)) ||
            (NULL == CU_add_test(pSuite, "testWelcome", testWelcome))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
