#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbmod.h"

typedef struct node{
  char *key;
  char *value;
  struct node *left;
  struct node *right;
} *Node;


Node createNode(char *key, char *value){
  Node treeNode = malloc(sizeof(struct node));
  treeNode->key = key;
  treeNode->value = value;
  treeNode->left = NULL;
  treeNode->right = NULL;
  return treeNode;
 
}

Node insertNode(Node treeNode, Node db){
  if (db == NULL){
    db = treeNode;
  }
  else if ((strcmp(db->key,treeNode->key)) < 0) {
    db->right = insertNode(treeNode, db->right);
  } 
  else if ((strcmp(db->key,treeNode->key)) > 0){
    db->left = insertNode(treeNode, db->left);
  }
  return db;
}

//preorder
void printDatabase(Node db) {
  Node cursor;
  cursor = db;
  if(cursor != NULL){
    puts(cursor->key);
    puts(cursor->value);
    printDatabase(cursor->left);   
    printDatabase(cursor->right);
    
  }
}

int search(Node db, char *inputkey) { // returns 1 if key exists else 0
  if (db == NULL){
    return 0;
  }
  else if ((strcmp((db->key), inputkey)) == 0) {
    return 1;
  }
  else if ((strcmp((db->key), inputkey)) > 0)  {
    return  search(db->left, inputkey);
  }
  else {
    return search(db->right, inputkey);
  }
}

char *queryValue(Node db, char *inputkey){
  if (db == NULL) {
    return NULL; 
  }
  else if ((strcmp(db->key,inputkey)) == 0) {
    
    return db->value;
  }
  else if ((strcmp(db->key, inputkey)) > 0){
    return queryValue(db->left, inputkey);
  }
  else {
    return queryValue(db->right, inputkey);
  }
}


Node updateValue(Node db, char *inputkey, char *inputvalue){
  if (db == NULL){
    return db;
  }
  else if ((strcmp(db->key, inputkey)) == 0) {
    free(db->value);
   
    //strcpy(db->value, (inputvalue));
    db->value = inputvalue;
    return db;
  }
  else if ((strcmp(db->key, inputkey)) < 0 ){
    return updateValue(db->right, inputkey, inputvalue);
  }
  else if ((strcmp(db->key, inputkey)) > 0){
    return updateValue(db->left, inputkey, inputvalue);
  }
  else 
    return db;
}

Node getSuccessor(Node db){
  while(db->right != NULL)
    db = db->right;
  return db;
}

Node deleteNode(Node db, char *inputkey){
  if (db == NULL){
    return db;
  }
  if ((strcmp(db->key, inputkey)) == 0){
    Node retval = NULL;
  
    if (db->left == NULL){
      retval = db->right;
      free(db);
      return retval;
    }
    else if (db->right == NULL){
      retval = db->right;
      free(db);
      return retval;
    }
    else {
      Node successor = getSuccessor(db->left);
      db->key = successor->key;
      db->left = deleteNode(db->left, successor->key);
    }
  }
  else if ((strcmp(db->key, inputkey)) > 0){
    db->left = deleteNode(db->left, inputkey);
  }
  else {
    db->right = deleteNode(db->right, inputkey);
  }
  return db;
}



void dbFree(Node db){
  if(db == NULL){
    return;
  }
  else {
    dbFree(db->right);
    dbFree(db->left);
    free(db->key);
    free(db->value);
    free(db);
  }
}
