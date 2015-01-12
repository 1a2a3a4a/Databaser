CC = gcc 
FLAGS = -Wall -ggdb -std=c99

dbt: db.o dbmod.o 
	$(CC) $(FLAGS)  $^ -o  $@

dbl: db.o dbmod2.o 
	$(CC) $(FLAGS)  $^ -o  $@


%.o: %.c %.h
	$(CC) $(FLAGS) -c $<

db.o: db.c dbmod.h
	$(CC) $(FLAGS) -c  db.c 
.PHONY: runt

runt: dbt SWE.db 
	./dbt SWE.db

runl: db SWE.db 
	./dbl SWE.db



mem: dbt 
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all  ./db SWE.db

test: test_dbmod2 test_dbmod 

test_dbmod2: dbl
	$(CC) $(FLAGS) dbmod2_test.c    -o dbmod2_unittests -lcunit
	./dbmod2_unittests

test_dbmod:  dbt
	$(CC) $(FLAGS) dbmod_test.c    -o dbmod_unittests -lcunit
	./dbmod_unittests


clean: 
	rm -f *o d
