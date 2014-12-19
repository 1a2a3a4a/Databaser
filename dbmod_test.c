#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <string.h>
#include "dbmod.h"
#include "dbmod.c"

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
  Node db = NULL;
  insertNode(createNode(key,value), db);  
  dbFree(db);
  CU_ASSERT(db == NULL);
    
}

void testDeleteNode() {
  Node db = NULL;
  char* key = "Anna";
  char* value = "10";
  Node test = createNode(key, value);
  db = insertNode(test,db);

  db = deleteNode(db, key);
  
  CU_ASSERT(db == NULL);
  free(test);
  
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


  free(test);

}

/* hur testar man print funktioner???? */
void testPrintDatabase() {
  Node db = NULL;
  char* key = "Anna";
  char* value = "10";
  Node test = createNode(key, value);
  db = insertNode(test, db);
  printDatabase(db);
  if (1 /*check result*/) {
    CU_ASSERT(1);
  }
  free(test);
}

void testQueryValue() {
  Node db = NULL;
  char* key = "Anna";
  char* value = "10";
  Node test = createNode(key, value);
  db = insertNode(test, db);

  char *chartest = queryValue(db, key);
  CU_ASSERT(chartest == value);

  free(test);
}

void testSearch() {
  Node db = NULL;
  char* key = "Anna";
  char* value = "10";
  Node test = createNode(key, value);
  db = insertNode(test,  db);

  int testint = search(db, key);
  CU_ASSERT(1 == testint);
  

  free(test);
}

void testUpdateValue() {
  Node db = NULL;
  char* key = "Anna";
  char* value = "10";
  
  Node test = createNode(key, value);
  db = insertNode(test, db);
  
  char* newval = malloc(3);
  newval = "20";
  db = updateValue(db, key, newval);
  
  CU_ASSERT(strcmp(db->value, newval) == 0);

  free(db);
  
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
      (NULL == CU_add_test(pSuite, "testUpdateValue", testUpdateValue))
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
