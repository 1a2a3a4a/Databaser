#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "dbmod.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void testCreateNode() {
  char* key = "Anna";
  char* value = "10";
  Node test = createNode(key, value);
  CU_ASSERT(test != NULL);
  CU_ASSERT(strcmp(test->key, "Anna") == 0);
  CU_ASSERT(strcmp(test->value, "10") == 0);
  CU_ASSERT(test->left == NULL);
  CU_ASSERT(test->right == NULL);
  free(test);
}

void testDbFree() {
  char* key = "Anna";
  char* value = "10";
  Node db = createNode(key, value);
  insertNode(createNode(key,value), db);  
  dbFree(db);
  /*asserta om det är frigjort */
    
}

void testDeleteNode() {
  Node db = NULL;
  Node db2 = NULL;
  char* key = "Anna";
  char* value = "10";
  Node test = createNode(key, value);
  char* key2 = "David";
  char* value2 = "10";
  Node test2 = createNode(key2, value2);


  db2 =  insertNode(test, db);
  db =  insertNode(test2, db);

  DeleteNode(db, key2);

  CU_ASSERT(db == NULL);
  CU_ASSERT(db2 != NULL);
 
}

void testInsertNode() {
  Node db = NULL;
  char* key = "Anna";
  char* value = "10";
  Node test = createNode(key, value);
  db = insertNode(test, db);

  CU_ASSERT(db != NULL);
  CU_ASSERT(strcmp(db->key, "Anna") == 0);
  CU_ASSERT(strcmp(db->value, "10") == 0);
  CU_ASSERT(db->left == NULL);
  CU_ASSERT(db->right == NULL);


  dbFree(db);

}

/* hur testar man print funktioner???? */
void testPrintDatabase() {
  Node db;
  printDatabase(db);
  if (1 /*check result*/) {
    CU_ASSERT(1);
  }
}

void testQueryValue() {
  Node db = NULL;
  char* key = "Anna";
  char* value = "10";
  Node test = createNode(key, value);
  db = insertNode(test, db);

  char *test = queryValue(db, key);
  CU_ASSERT(test, value);

  dbFree(db);
}

void testSearch() {
  Node db = NULL;
  char* key = "Anna";
  char* value = "10";
  Node test = createNode(key, value);
  db = insertNode(test, db);

  int test = search(db, key);
  CU_ASSERT(1,test);

  dbFree(db);
}

void testUpdateValue() {

  Node db = NULL;
  char* key = "Anna";
  char* value = "10";
  Node test = createNode(key, value);
  db = insertNode(test, db);
  
  char* updateValue = "20";
  db =  updateValue(db, key, updateValue);
  CU_ASSERT(strcmp(db->value, updateValue));

  dbFree(db);

  
}



int main() {
  CU_pSuite pSuite = NULL;

  /* Initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* Add a suite to the registry */
  pSuite = CU_add_suite("dbmod_test", init_suite, clean_suite);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Add the tests to the suite */
  if ((NULL == CU_add_test(pSuite, "testCreateNode", testCreateNode)) ||
      (NULL == CU_add_test(pSuite, "testDbFree", testDbFree)) ||
      (NULL == CU_add_test(pSuite, "testDeleteNode", testDeleteNode)) ||
      (NULL == CU_add_test(pSuite, "testInsertNode", testInsertNode)) ||
      (NULL == CU_add_test(pSuite, "testPrintDatabase", testPrintDatabase)) ||
      (NULL == CU_add_test(pSuite, "testQueryValue", testQueryValue)) ||
      (NULL == CU_add_test(pSuite, "testSearch", testSearch)) ||
      (NULL == CU_add_test(pSuite, "testUpdateValue", testUpdateValue)) ||
      (NULL == CU_add_test(pSuite, "testGetSuccessor", testGetSuccessor))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
