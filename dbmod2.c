#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dbmod.h"

typedef struct node {
  char *key;
  char *value;
  struct node *next;
} *Node;


Node createNode(char *key, char *value){
  Node newNode = malloc(sizeof(struct node));
  newNode->key = key;
  newNode->value = value;
  newNode->next = NULL;
  
  return newNode;
}

int search(Node db, char *inputkey){
  while(db != NULL){
    if(strcmp(db->key,inputkey) == 0){
      return 1;
    }
    else db = db->next;
  }
  return 0;

}


char * queryValue(Node db, char *inputkey){

  if ((strcmp(db->key, inputkey)) == 0){
    return db->value;
  }
  else 
    return queryValue(db->next, inputkey);
}

Node updateValue(Node db, char *inputkey, char *inputvalue){
  while(db != NULL){
    if((strcmp(db->key, inputkey) == 0)){
      free(db->value);
	db->value = inputvalue;
	return db;
      }
      else db = db->next;
  }
  return db;
}

Node insertNode(Node newnode, Node db){
  if (db == NULL){
    db = newnode;
  }
  else {
    newnode->next = db;
    db = newnode;
    
  }
  return db;
}

Node deleteNode(Node db, char *inputkey){
  Node prev = NULL;
  Node ret = db;
 
  while(db != NULL){
    if((strcmp(db->key, inputkey) == 0)){
      if(prev  == NULL){
	prev = db;
	free(prev);
	db = db->next;
	return db;
      }
      else prev->next = db->next;
      free(db);
    }
    prev = db;
    db = db->next;
  }
  return ret;
}
      

void printDatabase(Node db){
  while(db != NULL){
    puts(db->key);
    puts(db->value);
    db = db->next;
  }
}

void dbFree(Node db){
  if (db != NULL){
    if(db->next == NULL){
      free(db->key);
      free(db->value);
      free(db);
    }   
    dbFree(db->next);
    free(db->key);
    free(db->value);
    free(db);
  }
}

  
