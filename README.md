Authors: Tony Wang, Douglas Fröling

This is a database program. The database contains key and value pairs which
are read from a database file. The database file is written as "key\nvalue\n".
So one line where the key is read from and the next line is the key's value.
A key and a value may only be 127 characters long.


Necessary files:
db.c
dbmod.h
dbmod.c or dbmod2.c or dbmod3.c
Database file

Different dbmod.c files are used for different database structures. dbmod.c is run
initially without any changes. If you would like to use dbmod2.c or dbmod3.c open
the Makefile and change dbmod.o on line 4 to your file of choice. Example if you would
like to use dbmod2.c change dbmod.o to dbmod2.o.


How to run the program:

Write make in the buffer when are you are located in
the folder with all the files to compile the program. Then write make run with
the database file. Example, "make run database.db".

Within the databse program you can run different options. Press 1 to query 
a value of a key. 2 to update a keys value. 3 to create a new entry. 4 to remove
an entry and 5 to print out the database.




Program extensions:
Better ways to store the database.
More options for the database.


Achievments: A1, A2, D9, E10, G15, H20, I22, I23, K30, O42, R50, M37