#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dbmod.h"

/**
 * Stores one line from stream
 * @param dest where input from stream is stored
 * @param n number of bytes to be stored
 * @param stream to read from
 */


void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

/**
 * Stores keys and values into a database
 * 
 * Keys and Values are read from a file.
 * The file has to be written such as the key in line one then the key's value on the second line.
 * Example key1 \n val1 \n key2 \n val2 \n ...
 * @param filename The file to be read from
 * @return pointer to database
 */

Node readDatabase(char *filename) {
  printf("Loading database \"%s\"...\n\n", filename);
  FILE *database = fopen(filename, "r");
  char buffer1[128];
  char buffer2[128];
  Node db = NULL;
  while(!(feof(database))){ // Skapar ett träd av alla keys och values i databasen
    readline(buffer1, 128, database);
    readline(buffer2, 128, database);
    char *tempkey = malloc(sizeof(buffer1));
    char *tempvalue = malloc(sizeof(buffer2));
    strncpy(tempkey, buffer1, 128);
    strncpy(tempvalue, buffer2, 128);
    db = insertNode(createNode(tempkey,tempvalue),db);


  }
  fclose(database);
  return db;
}

/**
   Prints a representation of the database logo
 */

void welcome() {
  puts("Welcome to");
  puts(" ____    ____       ");
  puts("/\\  _`\\ /\\  _`\\     ");
  puts("\\ \\ \\/\\ \\ \\ \\L\\ \\   ");
  puts(" \\ \\ \\ \\ \\ \\  _ <\\ ");
  puts("  \\ \\ \\_\\ \\ \\ \\L\\ \\ ");
  puts("   \\ \\____/\\ \\____/ ");
  puts("    \\/___/  \\/___/  ");
  puts("");
}

/**
 * Checks if user input file when running program
 * @param argc number of inputs
 * @param array of inputs
 * @return 1 if more than one input else 0
 */

int checkArgumentFile(int argc, char *argv[]){
  // Kollar om man kör en fil eller inte
  if (argc < 2){ // Innehåller antalet argument som skrivs till programmet (t.ex. ./a.out eller ./db ger argc-värdet 1)
    puts("Usage: db [FILE]");
    return 0;
  }
  return 1;
}
/**
 * Prints the representation of the database options
 */
void chooseOp(){
  puts("Please choose an operation");
  puts("1. Query a key");
  puts("2. Update an entry");
  puts("3. New entry");
  puts("4. Remove entry");
  puts("5. Print database");
  puts("0. Exit database");
  printf("?");
}
/**
 * Query a value from a key in database
 * @param db pointer to database
 * @return pointer to database
 **/
void query(Node db){
  int found;
  char buffer2[128];
  printf("Enter key: ");
  readline(buffer2, 128, stdin);
  puts("Searching database...\n");
  // Hittat key eller inte
  found = search(db, buffer2);
  if (found == 1){
    puts("Found entry:");
    printf("key: %s\nvalue: %s\n\n",buffer2, queryValue(db, buffer2));
  }
  else if (found == 0){ // Om den inte hittar ett key
    printf("Could not find an entry matching key \"%s\"!\n", buffer2);
  }
}

/**
 * Updates a key's value in database
 * @param db pointer to database
 * @return pointer to database
 */

Node updateEntry(Node db){
  int found;
  char buffer2[128];
  char buffer3[128];
  printf("Enter key: ");
  readline(buffer2, 128, stdin);
  puts("Searching database...\n");
  found = search(db, buffer2);
  if(found == 0){
    printf("Could not find an entry matching key \"%s\"!\n", buffer2); 
  }else{
    puts("Matching entry found:");
    printf("Enter new value: ");
    readline(buffer3, 128, stdin);
    char* newvalue = malloc(sizeof(buffer3));
    strncpy(newvalue,buffer3, 128);
    db = updateValue(db, buffer2, newvalue);
    puts("Value inserted successfully!");
  }
  return db;
}

/**
 * Inputs a new entry in database
 * @param db pointer to database
 * @return pointer to database
 */

Node newEntry(Node db){
  char buffer[128];
  char buffer2[128];
  int found;
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database for duplicate keys...");
  found =  search(db, buffer);
  if (found == 1){
    printf("key \"%s\" already exists!\n", buffer);
  }
  else if(found == 0){ // Insert new node to the front of the db
    puts("Key is unique!\n");
    printf("Enter value: ");
    readline(buffer2, 128, stdin);
    char *tempkey = malloc(sizeof(tempkey));
    char *tempvalue = malloc(sizeof(tempvalue));
    strncpy(tempkey, buffer, 128);
    strncpy(tempvalue, buffer2, 128);
    db = insertNode(createNode(tempkey,tempvalue),db);
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", buffer,buffer2);
  }
  return db;
}

/**
 * Removes an entry in database if possible
 * @param db pointer to database
 * @return pointer to database
 */

Node removeEntry(Node db) {
  char buffer[128];
  int found;
  printf("Enter key: ");
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  found = search(db, buffer);
  if (found == 1){ 
    printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", buffer, queryValue(db, buffer));
    db = deleteNode(db, buffer);  
    return db;  
  }  
  if(found == 0){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
  return db;
}

/**
 * The database program
 * @param db pointer to database
 * @return pointer to database
 */


Node database(Node db){

  int choice = -1;
  while (choice !=0) {
    chooseOp(); // frågar om vilken operation
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
    switch(choice){
    case 1:
      query(db);
      break;  
    case 2:
      updateEntry(db);
      break;  
    case 3:
      db = newEntry(db);
      break;
    case 4:
      db = removeEntry(db);
      break;
    case 5:
      printDatabase(db);
      break;
    case 0:
      puts("Good Bye!");
      break;
    default:
      // Please try again
      puts("Could not parse choice! Please try again\n");
    }
    puts(" ");
  }
  return db;
}

/**
 * Driver function for the database program
 * @param argc number of inputs
 * @param argv array of inputs, the second input must be the database file
 */

int main(int argc, char *argv[]){
  
  if ((checkArgumentFile(argc,argv)) == 0) {
    return 0; // finns det bättre sätt att lösa?
  } // Anropar kolla om det är en fil i argumentet
  welcome(); // Anropar welcome för printning
  
  Node db = readDatabase(argv[1]);
  db = database(db);


  dbFree(db);
  return 0;
}
