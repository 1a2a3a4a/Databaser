#ifndef _DBMOD_H
#define _DBMOD_H

typedef struct node *Node;

/**
 * Creates a node with key and value
 * @param key the node's key value
 * @param value the nodes value
 * @return pointer to the node
 */

Node createNode(char *key, char *value);

/**
 * inserts node in db
 * @param db where node is inserted
 * @param node to be inserted in db
 * @return pointer to db
 */

Node insertNode(Node db, Node node);

/**
 * Prints the key and values in db
 *@param db pointer to db
 */

void printDatabase(Node db);

/**
 * 1 if inputkey exists in db else 0
 * @param db search in db
 * @param inputkey key to be searched for
 * @return 1 if inputkey exists in db else 0
 */
int search(Node db, char *inputkey);

/**
 * Queries the value inputkey corresponds to
 * @param db value in db to be queried
 * @param inputkey corresponding value of inputkey to be returned
 * @return inputkey's corresponding value
 */
char *queryValue(Node db, char *inputkey);
/**
 * Updates a value corresponding to an inputkey
 * @param db node in db corresponding to inputkey to be updated
 * @param inputkey corresponding value to be updated
 * @param inputvalue the new value to replace the old value
 * @return pointer to db
 */
Node updateValue(Node db, char *inputkey, char *inputvalue);
/**
 * Deletes inputkey's node
 * @param db node in db to be deleted
 * @param inputkey node corresponding to inputkey to be deleted
 * @return pointer to db
 */
Node deleteNode(Node db, char *inputkey);
/**
 * Frees the memory allocated in db
 * @param db to be freed
 */
void dbFree(Node db);
#endif
